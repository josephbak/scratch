//===- ToyOps.cpp - Toy dialect ops ---------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "Toy/ToyOps.h"
#include "Toy/ToyDialect.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "llvm/ADT/APInt.h"

#define GET_OP_CLASSES
#include "Toy/ToyOps.cpp.inc"

using namespace mlir;
using namespace mlir::toy;

    OpFoldResult SquareOp::fold(SquareOp::FoldAdaptor adaptor) {
      // adaptor.getInput() gives the input operand as an Attribute:
      //   - a real Attribute if the operand is a compile-time constant
      //   - null (empty Attribute) if it's a runtime value
      // dyn_cast<IntegerAttr> tries to interpret it as an integer constant.
      // If the attr is null OR not an IntegerAttr, dyn_cast returns null,
      // the `if` fails, and we skip to "can't fold".
      auto input = llvm::dyn_cast_or_null<IntegerAttr>(adaptor.getInput());
      if (!input)
        return {};                        // not a constant -> nothing to fold

      // input.getValue() is an APInt (arbitrary-precision int) holding the
      // constant. We square it. APInt's operator* handles the width; for i32
      // this wraps on overflow, matching hardware 2's-complement i32 mul.
      llvm::APInt squared = input.getValue() * input.getValue();

      // Build a NEW IntegerAttr of the SAME type as the input, holding the
      // squared value. getType() here is the op's result type accessor;
      // input.getType() would work too (equal by SameOperandsAndResultType).
      // An IntegerAttr implicitly converts to OpFoldResult, so returning it
      // tells the framework "replace this op with this constant."
      return IntegerAttr::get(getType(), squared);
    }