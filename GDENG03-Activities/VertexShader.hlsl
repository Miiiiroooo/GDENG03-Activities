struct VS_INPUT
{
    float3 pos : POSITION;
    float3 color : COLOR;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
};

cbuffer TMatrix
{
    matrix transform;
};


VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT vso;
    vso.pos = mul(float4(input.pos, 1.0f), transform);
    vso.color = input.color;
    return vso;
}