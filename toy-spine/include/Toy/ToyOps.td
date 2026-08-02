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

def Toy_TSquareOp : Toy_Op<"tsquare", [Pure,
                                             SameOperandsAndResultType]> {
    let summary = "squares a toy type integer.";
    let description = [{
        The `toy.tsquare` operation squares a toy type integer argument and returns the result.

        Example:

        ```mlir
        %0 = toy.identity %x : !toy.int<8>
        %1 = toy.tsquare %0 : !toy.int<8>
        ```
    }];

    let arguments = (ins Toy_IntType:$input);
    let results = (outs Toy_IntType:$res);

    let assemblyFormat = [{
        $input attr-dict `:` qualified(type($input))
    }];
}

def Toy_IdentityOp : Toy_Op<"identity", [Pure,
                                             SameOperandsAndResultType]> {
    let summary = "returns its argument.";
    let description = [{
        The `toy.identity` operation returns its argument without modification.

        Example:

        ```mlir
        %0 = toy.identity %x : !toy.int<8>
        ```
    }];

    let arguments = (ins Toy_IntType:$input);
    let results = (outs Toy_IntType:$res);

    let assemblyFormat = [{
        $input attr-dict `:` qualified(type($input))
    }];
}

def Toy_TensorIdOp : Toy_Op<"tensor_id", [Pure, SameOperandsAndResultType]> {
    let arguments = (ins AnyRankedTensor:$input);
    let results   = (outs AnyRankedTensor:$res);
    let assemblyFormat = [{ $input attr-dict `:` type($input) }];
}

#endif // TOY_OPS

