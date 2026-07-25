// RUN: toy-opt %s --toy-lower-to-arith | FileCheck %s

// CHECK-LABEL: @lower_square
// CHECK: arith.muli %arg0, %arg0 : i32
// CHECK-NOT: toy.square
func.func @lower_square(%x: i32) -> i32 {
  %r = toy.square %x : i32
  return %r : i32
}
