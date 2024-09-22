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


VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT vso;
    vso.pos = float4(input.pos, 1.0f);
    vso.color = input.color;
    return vso;
}


struct PS_INPUT
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return float4(input.color, 1.0f);
}