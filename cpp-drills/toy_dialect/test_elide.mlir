// test_elide.mlir
   func.func @f(%arg0: i32) -> i32 {
     %0 = "toy.identity"(%arg0) : (i32) -> i32
     return %0 : i32
   }