//===- ToyPasses.td - Toy dialect passes -------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef TOY_PASS
#define TOY_PASS

include "mlir/Pass/PassBase.td"

def ToySwitchBarFoo: Pass<"toy-switch-bar-foo", "::mlir::ModuleOp"> {
  let summary = "Switches the name of a FuncOp named `bar` to `foo` and folds.";
  let description = [{
    Switches the name of a FuncOp named `bar` to `foo` and folds.
    ```
    func.func @bar() {
      return
    }
    // Gets transformed to:
    func.func @foo() {
      return
    }
    ```
  }];
}

def ToyLowerToArith : Pass<"toy-lower-to-arith", "func::FuncOp"> {
  let summary = "Lower toy dialect to arith dialect.";
  let dependentDialects = ["::mlir::arith::ArithDialect"];
  let description = [{
    Lowers the toy dialect to the arith dialect.
  }];
}

#endif // TOY_PASS
