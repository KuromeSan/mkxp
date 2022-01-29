void main(float2 position : POSITION,
          uniform float4x4 projMat,
          float4 out v_position : POSITION)
{
    v_position = mul(float4(position, 0, 1), projMat);
}
