// toy_build.cpp
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Builders.h"                 // OpBuilder, getI32Type, getFunctionType
#include "mlir/IR/BuiltinOps.h"               // ModuleOp
#include "mlir/Dialect/Func/IR/FuncOps.h"     // func::FuncOp, func::ReturnOp
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "llvm/Support/raw_ostream.h"         // llvm::outs

#define GET_OP_CLASSES
#include "toy_ops.h.inc"                       // toy::IdentityOp
#include "toy_dialect.h.inc"                   // toy::ToyDialect

#include "ToyPatterns.h"                        // populateToyPatterns

using namespace mlir;
using namespace toy;

int main() {
  // ── setup: the world + dialects + the builder ──
  MLIRContext ctx;
  ctx.loadDialect<toy::ToyDialect>();
  ctx.loadDialect<func::FuncDialect>();

  OpBuilder b(&ctx);
  Location loc = b.getUnknownLoc();            // "no source position" — you're building, not parsing

  // ── PHASE 1: BUILD the module in memory (YOUR construction goes here) ──
  //   1. create the module
  //   2. set insertion into module body
  //   3. build func.func @f (i32) -> i32
  //   4. addEntryBlock → get the argument (your input Value)
  //   5. set insertion into the block
  //   6. build toy.identity(arg)
  //   7. build func.return(identity result)

  // ── print what you built (confirm construction BEFORE eliding) ──
  //   module->print(llvm::outs());

  // ── PHASE 2: run the elide pattern (reuse rung 34) ──
  //   RewritePatternSet patterns(&ctx);
  //   populateToyPatterns(patterns);
  //   applyPatternsGreedily(*module, std::move(patterns));

  // ── print again (confirm elision) ──
  //   module->print(llvm::outs());

  return 0;
}