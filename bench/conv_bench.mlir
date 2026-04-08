func.func @conv_2d_nhwc_hwcf(%input: tensor<1x225x225x3xf32>, %filter: tensor<3x3x3x32xf32>) -> tensor<1x112x112x32xf32> {
  %cst = arith.constant 0.0 : f32
  %init = tensor.empty() : tensor<1x112x112x32xf32>
  %fill = linalg.fill ins(%cst : f32) outs(%init : tensor<1x112x112x32xf32>) -> tensor<1x112x112x32xf32>
  %result = linalg.conv_2d_nhwc_hwcf {dilations = dense<1> : tensor<2xi64>, strides = dense<2> : tensor<2xi64>}
    ins(%input, %filter : tensor<1x225x225x3xf32>, tensor<3x3x3x32xf32>)
    outs(%fill : tensor<1x112x112x32xf32>) -> tensor<1x112x112x32xf32>
  return %result : tensor<1x112x112x32xf32>
}
