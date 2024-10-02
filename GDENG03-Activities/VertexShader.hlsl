struct VS_INPUT
{
    float4 pos : POSITION0;
    float3 color : COLOR0;
    float4 pos1 : PP;
    float3 color1 : CC;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR0;
    float3 color1 : COLOR1;
};

cbuffer ConstantData : register(b0)
{
    float m_angle;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT vso;
    float3 newPos = lerp(input.pos, input.pos1, (sin(m_angle) + 1.0f) / 2.0f);
    vso.pos = float4(newPos, 1.0f);
    vso.color = input.color;
    vso.color1 = input.color1;
    return vso;
}