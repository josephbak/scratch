func.func private @printI64(i64)
func.func private @printNewline()

func.func @main() {
  %c7 = arith.constant 7 : i32
  %sq = toy.square %c7 : i32
  %ext = arith.extsi %sq : i32 to i64
  call @printI64(%ext) : (i64) -> ()
  call @printNewline() : () -> ()
  return
}
