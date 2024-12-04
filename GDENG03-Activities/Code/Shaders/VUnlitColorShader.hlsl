struct VS_INPUT
{
    float3 pos : POSITION;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
};

cbuffer TMatrix : register(b0)
{
    matrix transform;
};

cbuffer VPMatrix : register(b1)
{
    matrix view;
    matrix projection;
};


VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT vso;
    vso.pos = mul(mul(mul(float4(input.pos, 1.0f), transpose(transform)), transpose(view)), transpose(projection));
    return vso;
}