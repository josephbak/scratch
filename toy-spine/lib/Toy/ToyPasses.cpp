//===- ToyPasses.cpp - Toy passes -----------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Rewrite/FrozenRewritePatternSet.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "Toy/ToyOps.h"

#include "Toy/ToyPasses.h"

namespace mlir::toy {
#define GEN_PASS_DEF_TOYSWITCHBARFOO
#include "Toy/ToyPasses.h.inc"

namespace {
class ToySwitchBarFooRewriter : public OpRewritePattern<func::FuncOp> {
public:
  using OpRewritePattern<func::FuncOp>::OpRewritePattern;
  LogicalResult matchAndRewrite(func::FuncOp op,
                                PatternRewriter &rewriter) const final {
    if (op.getSymName() == "bar") {
      rewriter.modifyOpInPlace(op, [&op]() { op.setSymName("foo"); });
      return success();
    }
    return failure();
  }
};

class ToySwitchBarFoo
    : public impl::ToySwitchBarFooBase<ToySwitchBarFoo> {
public:
  using impl::ToySwitchBarFooBase<ToySwitchBarFoo>::ToySwitchBarFooBase;
  void runOnOperation() final {
    RewritePatternSet patterns(&getContext());
    patterns.add<ToySwitchBarFooRewriter>(&getContext());
    FrozenRewritePatternSet patternSet(std::move(patterns));
    if (failed(applyPatternsGreedily(getOperation(), patternSet)))
      signalPassFailure();
  }
};
} // namespace

#define GEN_PASS_DEF_TOYLOWERTOARITH        // ties .cpp to the .td declaration
#include "Toy/ToyPasses.h.inc"

namespace {
class ToyLowerToArithRewriter : public OpRewritePattern<SquareOp> {
public:
  using OpRewritePattern<SquareOp>::OpRewritePattern;   // inherit constructors
  LogicalResult matchAndRewrite(SquareOp op, PatternRewriter &rewriter) const final {
    Value input = op.getInput();
    rewriter.replaceOpWithNewOp<arith::MulIOp>(op, input, input);
    return success();
  }
};

class ToyLowerToArith : public impl::ToyLowerToArithBase<ToyLowerToArith> {
public:
  using impl::ToyLowerToArithBase<ToyLowerToArith>::ToyLowerToArithBase;
  void runOnOperation() final {
    RewritePatternSet patterns(&getContext());
    patterns.add<ToyLowerToArithRewriter>(&getContext());
    FrozenRewritePatternSet patternSet(std::move(patterns));
    if (failed(applyPatternsGreedily(getOperation(), patternSet)))
      signalPassFailure();
  }
};
} // namespace

} // namespace mlir::toy
