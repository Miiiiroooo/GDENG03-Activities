#include "ARenderer.h"
#include "Transform.h"
#include "AGameObject.h"


ARenderer::ARenderer(std::string compoonentName, LPCWSTR shaderType) : AComponent(compoonentName, EComponentTypes::Renderer), shaderType(shaderType)
{
	topologyType = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED; 
	indexBuffer = nullptr; 
}

ARenderer::~ARenderer()
{

}

bool ARenderer::Release()
{
	for (auto& buffer : bufferList)
	{
		buffer->Release();
	}

	if (indexBuffer)
	{
		indexBuffer->Release();
	}

	if (vConstantBuffer)
	{
		vConstantBuffer->Release();
	}

	return true;
}

void ARenderer::Perform()
{
	if (bufferList.size() == 0) return;

	for (auto& buffer : bufferList)
	{
		buffer->BindToPipeline();
	}
	indexBuffer->BindToPipeline();

	Transform* transform = owner->GetTransform();
	vConstantBuffer->SetConstants(transform->CreateTransformationMatrix());
	vConstantBuffer->BindToPipeline();

	GraphicsEngine::GetInstance()->GetDeviceContext()->IASetPrimitiveTopology(topologyType);
	GraphicsEngine::GetInstance()->GetDeviceContext()->DrawIndexed(indexBuffer->GetIndexCount(), 0u, 0u);
}

LPCWSTR ARenderer::GetShaderType()
{
	return shaderType;
}

void ARenderer::InitRenderer()
{
	vConstantBuffer = new VertexConstantBuffer<TMatrix>(GraphicsEngine::GetInstance());
	vConstantBuffer->Init();
}