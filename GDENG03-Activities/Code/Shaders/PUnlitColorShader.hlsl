struct PS_INPUT
{
    float4 position : SV_POSITION;
};

cbuffer UnlitColor : register(b2)
{
    float3 color;
};

float4 main(PS_INPUT input) : SV_TARGET
{
    return float4(color, 1.0f);
}