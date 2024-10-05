#include "ARenderer.h"
#include "../Transform.h"
#include "../../GameObjects/AGameObject.h"


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

	// Bind every buffer stored in this renderer
	for (auto& buffer : bufferList)
	{
		buffer->BindToPipeline();
	}

	indexBuffer->BindToPipeline();

	Transform* transform = owner->GetTransform();
	vConstantBuffer->SetConstants(transform->CreateTransformationMatrix());
	vConstantBuffer->BindToPipeline();

	// Set the topology type, then draw to the GPU
	GraphicsEngine::GetInstance()->GetDeviceContext()->IASetPrimitiveTopology(topologyType);
	GraphicsEngine::GetInstance()->GetDeviceContext()->DrawIndexed(indexBuffer->GetIndexCount(), 0u, 0u);
}

LPCWSTR ARenderer::GetShaderType()
{
	return shaderType;
}

void ARenderer::InitRenderer()
{
	vConstantBuffer = new VertexConstantBuffer<TMatrix>(GraphicsEngine::GetInstance(), 0u);
	vConstantBuffer->Init();
}