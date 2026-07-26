// RUN: toy-opt %s | toy-opt | FileCheck %s

// test round-trip of the bare type
// CHECK-LABEL: func.func @t
// CHECK-SAME: !toy.int<8>
func.func @t(%x: !toy.int<8>) {
  return
}