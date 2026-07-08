#include <utility>
#include "mlir/IR/MLIRContext.h"
#include "mlir/Parser/Parser.h"                 // parseSourceFile
#include "mlir/IR/AsmState.h"                   // ParserConfig (confirm)
#include "mlir/Dialect/Func/IR/FuncOps.h"       // func::FuncDialect (confirm path)
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "toy_dialect.h.inc"            // toy::ToyDialect
#include "ToyPatterns.h"  // + declaration of populateToyPatterns

int main(int argc, char **argv) {
    using namespace mlir;

    MLIRContext ctx;
    ctx.loadDialect<toy::ToyDialect>();          // register + load → parser can read toy.identity
    ctx.loadDialect<func::FuncDialect>();

  // 1. parse text → in-memory module
  //    OwningOpRef<ModuleOp> mod = parseSourceFile<ModuleOp>(<path>, &ctx);
  //    (or parseSourceString<ModuleOp>(<literal>, &ctx))
    ParserConfig config(&ctx);                    // config wraps the context
    OwningOpRef<ModuleOp> mod = parseSourceFile<ModuleOp>("test_elide.mlir", config);

    if (!mod) return 1;

  // 2. build + run the pattern set  (your Task-2 pieces)
    RewritePatternSet patterns(&ctx);
    populateToyPatterns(patterns);
    if (failed(applyPatternsGreedily(*mod, std::move(patterns))))
        return 1;

  // 3. print → text  → you SEE toy.identity gone
    mod->print(llvm::outs());
}