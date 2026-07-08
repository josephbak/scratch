#include "mlir/IR/PatternMatch.h"                        // OpRewritePattern, PatternRewriter, RewritePatternSet
#include "mlir/Pass/Pass.h"                              // PassWrapper, OperationPass, signalPassFailure
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"  // applyPatternsGreedily
#include "ToyPatterns.h"
#include "mlir/Support/LogicalResult.h"   // re-exports LogicalResult/success into mlir if this version does


// the generated op — needs the same header-order care
#include "mlir/IR/Dialect.h"
#include "mlir/IR/OpImplementation.h"
#define GET_OP_CLASSES
#include "toy_ops.h.inc"                                 // toy::IdentityOp declaration

using namespace mlir;
using namespace toy;                                     // so IdentityOp resolves unqualified

// pattern
struct ElideIdentity : public OpRewritePattern<IdentityOp> {
  using OpRewritePattern<IdentityOp>::OpRewritePattern;

  LogicalResult matchAndRewrite(IdentityOp op, PatternRewriter &rewriter) const override {

    rewriter.replaceOp(op, op.getInput());
    return success();
  }
};

// populate function
void populateToyPatterns(RewritePatternSet &patterns) {
  // add ElideIdentity, forwarding the context
  patterns.add<ElideIdentity>(patterns.getContext());
}

// pass
struct ElideIdentityPass
    : public PassWrapper<ElideIdentityPass, OperationPass<>> {
  void runOnOperation() override {

    RewritePatternSet patterns(&getContext());// make a RewritePatternSet bound to the context
    populateToyPatterns(patterns); // populate it (call your populate fn)
    if (failed(applyPatternsGreedily(getOperation(), std::move(patterns)))) {
      signalPassFailure();
    } // apply it greedily over getOperation()
  }
};