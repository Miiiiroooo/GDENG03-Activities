struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR0;
    float3 color1 : COLOR1;
};

cbuffer ConstantData : register(b0)
{
    float m_angle;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return float4(lerp(input.color, input.color1, (sin(m_angle) + 1.0f) / 2.0f), 1.0f);
}