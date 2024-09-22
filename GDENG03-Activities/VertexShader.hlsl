struct VS_OUTPUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};


VS_OUTPUT main(float4 pos : POSITION, float4 color : COLOR)
{
    VS_OUTPUT vso;
    vso.pos = pos;
    vso.color = color;
    return vso;
}