// RUN: toy-opt %s --one-shot-bufferize | FileCheck %s

// CHECK-LABEL: func.func @t
// CHECK-NOT: toy.tensor_id
// CHECK: memref.alloc
// CHECK: memref.copy
func.func @t(%a: tensor<4xi32>) -> tensor<4xi32> {
  %r = toy.tensor_id %a : tensor<4xi32>
  return %r : tensor<4xi32>
}