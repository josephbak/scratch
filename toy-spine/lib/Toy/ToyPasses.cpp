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
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Dialect/Func/Transforms/FuncConversions.h"
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
class ToyLowerToArithRewriter : public OpRewritePattern<SquareOp> { // pattern
public:
  using OpRewritePattern<SquareOp>::OpRewritePattern;   // inherit constructors
  LogicalResult matchAndRewrite(SquareOp op, PatternRewriter &rewriter) const final {
    Value input = op.getInput();
    rewriter.replaceOpWithNewOp<arith::MulIOp>(op, input, input);
    return success();
  }
};

class ToyLowerToArith : public impl::ToyLowerToArithBase<ToyLowerToArith> { // pass
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
  
#define GEN_PASS_DEF_TOYLOWERTOARITHDIALECTCONVERSION
#include "Toy/ToyPasses.h.inc"

namespace {
class SquareOpLowering : public OpConversionPattern<SquareOp> {
public:
  using OpConversionPattern<SquareOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(SquareOp op, OpAdaptor adaptor,
                ConversionPatternRewriter &rewriter) const override {
    // Value input = op.getInput();
    Value input = adaptor.getInput();
    rewriter.replaceOpWithNewOp<arith::MulIOp>(op, input, input);
    return success();
  }
};

class ToyLowerToArithDialectConversion : public impl::ToyLowerToArithDialectConversionBase<ToyLowerToArithDialectConversion> {
public:
  using impl::ToyLowerToArithDialectConversionBase<ToyLowerToArithDialectConversion>::ToyLowerToArithDialectConversionBase;
  void runOnOperation() override {
      ConversionTarget target(getContext());   // <- the new concept
      target.addLegalDialect<arith::ArithDialect, func::FuncDialect>();
      target.addIllegalDialect<ToyDialect>();

      RewritePatternSet patterns(&getContext());
      patterns.add<SquareOpLowering>(&getContext());

      if (failed(applyPartialConversion(getOperation(), target,
                                        std::move(patterns))))   // <- driver, not applyPatternsGreedily
        signalPassFailure();
    }
};
} // namespace
  
#define GEN_PASS_DEF_TOYTSQUARELOWERTOARITH
#include "Toy/ToyPasses.h.inc"

namespace {
class TSquareOpLowering : public OpConversionPattern<TSquareOp> {
public:
  using OpConversionPattern<TSquareOp>::OpConversionPattern;
  LogicalResult matchAndRewrite(TSquareOp op, OpAdaptor adaptor,
                ConversionPatternRewriter &rewriter) const override {
    Value input = adaptor.getInput();
    rewriter.replaceOpWithNewOp<arith::MulIOp>(op, input, input);
    return success();
  }
};

class ToyTSquareLowerToArith : public impl::ToyTSquareLowerToArithBase<ToyTSquareLowerToArith> {
public:
  using impl::ToyTSquareLowerToArithBase<ToyTSquareLowerToArith>::ToyTSquareLowerToArithBase;
  void runOnOperation() override {
    
      TypeConverter converter;
      converter.addConversion([](Type t) { return t; });              // identity fallback
      converter.addConversion([](IntType t) -> Type {                 // !toy.int<W> -> iW
      return IntegerType::get(t.getContext(), t.getWidth());});

      ConversionTarget target(getContext());
      target.addLegalDialect<arith::ArithDialect, func::FuncDialect>();
      // target.addIllegalDialect<ToyDialect>();
      target.addIllegalOp<TSquareOp>();
      
      target.addDynamicallyLegalOp<func::FuncOp>([&](func::FuncOp op) {
        return converter.isSignatureLegal(op.getFunctionType());
      });
      target.addDynamicallyLegalOp<func::ReturnOp>([&](func::ReturnOp op) {
        return isLegalForReturnOpTypeConversionPattern(op, converter);
      });

      RewritePatternSet patterns(&getContext());
      patterns.add<TSquareOpLowering>(converter, &getContext());
      populateFunctionOpInterfaceTypeConversionPattern<func::FuncOp>(patterns, converter);
      populateReturnOpTypeConversionPattern(patterns, converter);
      
      if (failed(applyPartialConversion(getOperation(), target, std::move(patterns))))
          signalPassFailure();
    }
};
} // namespace

} // namespace mlir::toy