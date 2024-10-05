struct VS_INPUT
{
    float3 pos : POSITION;
    float3 color : COLOR;
    float3 pos1 : POSITION1;
    float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
    float4 pos : SV_POSITION;
    float3 color : COLOR0;
    float3 color1 : COLOR1;
};

cbuffer TMatrix : register(b0)
{
    matrix transform;
};

cbuffer TempConstant : register(b1)
{
    float m_angle;
};


VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT vso;
    
    float3 newVertPos = lerp(input.pos, input.pos1, (sin(m_angle) + 1.0f) / 2.0f);
    vso.pos = mul(float4(newVertPos, 1.0f), transform);
    //vso.pos = float4(newVertPos, 1.0f);
    vso.color = input.color;
    vso.color1 = input.color1;
    
    return vso;
}