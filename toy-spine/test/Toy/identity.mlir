// RUN: toy-opt %s | toy-opt | FileCheck %s

// CHECK-LABEL: func.func @t
func.func @t(%x: !toy.int<8>) -> !toy.int<8> {
  // CHECK: toy.identity %{{.*}} : !toy.int<8>
  %0 = toy.identity %x : !toy.int<8>
  return %0 : !toy.int<8>
}