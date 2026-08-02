// RUN: toy-opt %s --toy-lower-to-arith | FileCheck %s
// RUN: toy-opt %s --toy-lower-to-arith-dialectconversion | FileCheck %s
// CHECK-LABEL: func.func @lower_square
func.func @lower_square(%arg0: i32) -> i32 {
  // CHECK: arith.muli
  // CHECK-NOT: toy.square
  %0 = toy.square %arg0 : i32
  return %0 : i32
}