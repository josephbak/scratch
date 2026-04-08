func.func @conv_resnet(%input: tensor<1x56x56x64xf32>,
                       %filter: tensor<3x3x64x64xf32>) -> tensor<1x54x54x64xf32> {
  %init = tensor.empty() : tensor<1x54x54x64xf32>
  %0 = linalg.conv_2d_nhwc_hwcf
    {dilations = dense<1> : tensor<2xi64>, strides = dense<1> : tensor<2xi64>}
    ins(%input, %filter : tensor<1x56x56x64xf32>, tensor<3x3x64x64xf32>)
    outs(%init : tensor<1x54x54x64xf32>) -> tensor<1x54x54x64xf32>
  return %0 : tensor<1x54x54x64xf32>
}
