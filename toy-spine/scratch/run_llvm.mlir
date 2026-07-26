module {
  llvm.func @printI64(i64) attributes {sym_visibility = "private"}
  llvm.func @printNewline() attributes {sym_visibility = "private"}
  llvm.func @main() {
    %0 = llvm.mlir.constant(49 : i64) : i64
    llvm.call @printI64(%0) : (i64) -> ()
    llvm.call @printNewline() : () -> ()
    llvm.return
  }
}

