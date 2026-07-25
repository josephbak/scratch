// RUN: toy-opt %s --canonicalize | FileCheck %s

// CHECK-LABEL: @fold_constant
// CHECK: arith.constant 9 : i32
// CHECK-NOT: toy.square
func.func @fold_constant() -> i32 {
  %c3 = arith.constant 3 : i32
  %r = toy.square %c3 : i32
  return %r : i32
}

// CHECK-LABEL: @no_fold_runtime
// CHECK: toy.square
func.func @no_fold_runtime(%x: i32) -> i32 {
  %r = toy.square %x : i32
  return %r : i32
}
