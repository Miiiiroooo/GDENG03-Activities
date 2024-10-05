#include "MeshRenderer.h"
#include "../../Meshes/QuadMesh.h"


MeshRenderer::MeshRenderer() : ARenderer("MesehRenderer", L"DefaultShader")
{
	topologyType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

MeshRenderer::MeshRenderer(LPCWSTR shaderType) : ARenderer("MesehRenderer", shaderType)
{
	topologyType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::LoadPrimitive(EPrimitiveMeshTypes type)
{
	AMesh<VertexData>* mesh = nullptr;

	switch (type)
	{
	case EPrimitiveMeshTypes::Cube:
		// add cubue here
		break;
	case EPrimitiveMeshTypes::Sphere:
		// add sphere here
		break;
	case EPrimitiveMeshTypes::Quad:
		mesh = new QuadMesh<VertexData>();
		break;
	case EPrimitiveMeshTypes::Plane:
		// add plane here
		break;
	default:
		break;
	}

	if (mesh == nullptr) return;

	InitRenderer();

	VertexBuffer<VertexData>* vb = mesh->CreateVertexBuffer();
	vb->Init();
	bufferList.push_back(vb);

	indexBuffer = mesh->CreateIndexBuffer();
	indexBuffer->Init();

	delete mesh;
}

void MeshRenderer::LoadNonPrimitive(std::string fileName)
{

}




void MeshRenderer::Temp(const std::vector<DirectX::XMFLOAT3>& colorList)
{
	InitRenderer();

	QuadMesh<VertexData>* mesh = new QuadMesh<VertexData>(); 

	VertexBuffer<VertexData>* vb = mesh->Temp(colorList); 
	vb->Init(); 
	bufferList.push_back(vb); 

	indexBuffer = mesh->CreateIndexBuffer(); 
	indexBuffer->Init(); 

	delete mesh;
}

void MeshRenderer::TempAnimation(int animType)
{
	InitRenderer();

	QuadMesh<TempVertex>* mesh = new QuadMesh<TempVertex>();
	VertexBuffer<TempVertex>* vb = (animType == 1) ? mesh->TempAnimation() : mesh->TempAnimation2();
	vb->Init(); 
	bufferList.push_back(vb); 

	indexBuffer = (animType == 1) ? mesh->CreateIndexBuffer() : mesh->TempAnimation2Index();
	indexBuffer->Init(); 

	delete mesh; 
}