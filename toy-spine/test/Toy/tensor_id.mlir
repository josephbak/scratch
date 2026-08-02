// RUN: toy-opt %s | toy-opt | FileCheck %s
// CHECK-LABEL: func.func @t
func.func @t(%a: tensor<4xi32>) -> tensor<4xi32> {
  // CHECK: toy.tensor_id %{{.*}} : tensor<4xi32>
  %r = toy.tensor_id %a : tensor<4xi32>
  return %r : tensor<4xi32>
}