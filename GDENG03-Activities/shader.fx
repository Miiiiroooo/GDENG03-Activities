struct VS_INPUT
{
    float3 pos : POSITION;
    float3 pos1 : POSITION1;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

cbuffer ConstantData : register(b0)
{
    float m_angle;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT vso;
    
    vso.pos = float4(lerp(input.pos, input.pos1, (sin(m_angle) + 1.0f) / 2.0f), 1.0f);
    vso.color = input.color;
    vso.color1 = input.color1;
    return vso;
}


struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
    float3 color1 : COLOR1;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return float4(lerp(input.color, input.color1, (sin(m_angle) + 1.0f) / 2.0f), 1.0f);
}