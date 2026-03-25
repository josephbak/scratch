func.func @matmul(%a: tensor<4x4xf32>, %b: tensor<4x4xf32>) -> tensor<4x4xf32> {
  %empty = tensor.empty() : tensor<4x4xf32>
  %result = linalg.matmul ins(%a, %b : tensor<4x4xf32>, tensor<4x4xf32>)
                          outs(%empty : tensor<4x4xf32>) -> tensor<4x4xf32>
  %relu = linalg.generic {
    indexing_maps = [affine_map<(d0,d1) -> (d0,d1)>,
                     affine_map<(d0,d1) -> (d0,d1)>],
    iterator_types = ["parallel", "parallel"]}
    ins(%result : tensor<4x4xf32>) outs(%empty : tensor<4x4xf32>) {
    ^bb0(%in: f32, %out: f32):
      %zero = arith.constant 0.0 : f32
      %r = arith.maximumf %in, %zero : f32
      linalg.yield %r : f32
    } -> tensor<4x4xf32>
  return %relu : tensor<4x4xf32>
}