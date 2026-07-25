func.func @square_it(%x: i32) -> i32 {
  %r = toy.square %x : i32
  return %r : i32
}
