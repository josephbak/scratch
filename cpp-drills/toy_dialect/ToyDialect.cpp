// ToyDialect.cpp — the HOST translation unit
#include "mlir/IR/Dialect.h"          // mlir::Dialect
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/OpImplementation.h" // op infra, MLIR_DECLARE/DEFINE_EXPLICIT_TYPE_ID
#include "mlir/IR/Builders.h"
#include "llvm/ADT/StringRef.h"

using namespace mlir;

#include "toy_dialect.h.inc"     // 1. provides context: declarations, includes, namespaces

#define GET_OP_CLASSES
#include "toy_ops.h.inc"

#define GET_OP_CLASSES            // ← RE-DEFINE it, the undef above killed it
#include "toy_ops.cpp.inc"        // 2. pastes op defs INTO this TU (now they have context)
// #undef GET_OP_CLASSES            // ← clear it before reusing the .inc with a different macro

#include "toy_dialect.cpp.inc"    // pastes dialect ctor/dtor bodies

void toy::ToyDialect::initialize() {
    addOperations<toy::IdentityOp>();
}