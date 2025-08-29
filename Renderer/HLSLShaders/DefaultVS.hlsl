cbuffer worldBuffer : register(b0)
{
    matrix worldMatrix;
}

cbuffer cameraBuffer : register(b1)
{
    matrix viewMatrix;
    matrix projectionMatrix;
};

struct VertexInput
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

PixelInput main(VertexInput input)
{
    PixelInput output;
    
    float4 pos = float4(input.position, 1);
    pos = mul(pos, worldMatrix);
    pos = mul(pos, viewMatrix);
    pos = mul(pos, projectionMatrix);
    
    output.position = pos; /*float4(input.position, 1);*/
    output.color = input.color;
    
    return output;
}