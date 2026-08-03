#include "Toy/ToyDialect.h"
#include "Toy/ToyOps.h"
#include "mlir/Dialect/Bufferization/IR/BufferizableOpInterface.h"

using namespace mlir;
using namespace mlir::bufferization;

namespace {
    struct TensorIdOpBufferization
        : BufferizableOpInterface::ExternalModel<TensorIdOpBufferization, toy::TensorIdOp> {

      bool bufferizesToMemoryRead(Operation *op, OpOperand &operand,
                                    const AnalysisState &state) const {
        return true;   // reads the input buffer
    }
      bool bufferizesToMemoryWrite(Operation *op, OpOperand &operand,
                                    const AnalysisState &state) const {
        return false;  // never stores into the input buffer
    }
      AliasingValueList getAliasingValues(Operation *op, OpOperand &operand,
                                            const AnalysisState &state) const {
        return {{op->getResult(0), BufferRelation::Equivalent}};
        }
      LogicalResult bufferize(Operation *op, RewriterBase &rewriter,
                                const BufferizationOptions &options,
                                BufferizationState &state) const {
        auto tensorIdOp = cast<toy::TensorIdOp>(op);
        FailureOr<Value> resultBuffer = getBuffer(rewriter, tensorIdOp.getInput(), options, state); // ← STEP 1: get input's buffer
        if (failed(resultBuffer))                     // ← failure-check
          return failure();

        replaceOpWithBufferizedValues(rewriter, op, *resultBuffer);  // ← STEP 2: replace
        return success();                             // ← STEP 3
    }
    };
} // namespace