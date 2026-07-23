//===- ToyOps.td - Toy dialect ops -----------*- tablegen -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef TOY_OPS
#define TOY_OPS

include "Toy/ToyTypes.td"
include "mlir/Interfaces/InferTypeOpInterface.td"
include "mlir/Interfaces/SideEffectInterfaces.td"

def Toy_SquareOp : Toy_Op<"square", [Pure,
                                             SameOperandsAndResultType]> {
    let summary = "squares an integer.";
    let description = [{
        The `toy.square` operation squares an integer argument and returns the result.

        Example:

        ```mlir
        %0 = arith.constant 3 : i32
        // Apply the square operation to %0
        %1 = toy.square %0 : i32
        ```
    }];

    let arguments = (ins I32:$input);
    let results = (outs I32:$res);

    let assemblyFormat = [{
        $input attr-dict `:` type($input)
    }];
    
    let hasFolder = 1;
}
#endif // TOY_OPS
