func.func @matmul(%a: tensor<4x4xf32>, %b: tensor<4x4xf32>) -> tensor<4x4xf32> {
  %empty = tensor.empty() : tensor<4x4xf32>
  %result = linalg.matmul ins(%a, %b : tensor<4x4xf32>, tensor<4x4xf32>)
                          outs(%empty : tensor<4x4xf32>) -> tensor<4x4xf32>
  return %result : tensor<4x4xf32>
}
