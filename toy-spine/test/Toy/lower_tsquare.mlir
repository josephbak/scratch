// RUN: toy-opt %s --toy-lower-tsquare | FileCheck %s
// CHECK-LABEL: func.func @t
// CHECK-SAME: (%{{.*}}: i8) -> i8
func.func @t(%x: !toy.int<8>) -> !toy.int<8> {
  // CHECK: arith.muli %{{.*}}, %{{.*}} : i8
  // CHECK-NOT: toy.tsquare
  // CHECK-NOT: !toy.int
  %0 = toy.tsquare %x : !toy.int<8>
  return %0 : !toy.int<8>
}