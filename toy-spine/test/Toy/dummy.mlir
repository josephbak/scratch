// RUN: toy-opt %s | toy-opt | FileCheck %s

module {
    // CHECK-LABEL: func @square()
    func.func @square() {
        %0 = arith.constant 1 : i32
        // CHECK: %{{.*}} = toy.square %{{.*}} : i32
        %res = toy.square %0 : i32
        return
    }
}