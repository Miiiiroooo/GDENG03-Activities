#include "MeshRenderer.h"
#include "../../Meshes/CubeMesh.h"
#include "../../Meshes/QuadMesh.h"
#include "../../Meshes/PlaneMesh.h"
#include "../../Meshes/CircleMesh.h"


MeshRenderer::MeshRenderer() : ARenderer("MeshRenderer", L"DefaultShader")
{
	topologyType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

MeshRenderer::MeshRenderer(LPCWSTR shaderType) : ARenderer("MeshRenderer", shaderType)
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
		mesh = new CubeMesh<VertexData>(); 
		break;
	case EPrimitiveMeshTypes::Sphere:
		// add sphere here
		break;
	case EPrimitiveMeshTypes::Quad:
		mesh = new QuadMesh<VertexData>();
		break;
	case EPrimitiveMeshTypes::Circle:
		mesh = new CircleMesh<VertexData>();
		break;
	case EPrimitiveMeshTypes::Plane:
		mesh = new PlaneMesh<VertexData>();
		break;
	default:
		break;
	}

	if (mesh == nullptr) return;

	InitRenderer();

	VertexBuffer<VertexData>* vb = mesh->CreateVertexBuffer();
	vb->Init();
	buffersList.push_back(vb);

	indexBuffer = mesh->CreateIndexBuffer();
	indexBuffer->Init();

	delete mesh;
}

void MeshRenderer::LoadNonPrimitive(std::string fileName)
{

}




//void MeshRenderer::Temp()
//{
//	InitRenderer();
//
//	CubeMesh<VertexData>* mesh = new CubeMesh<VertexData>();
//
//	VertexBuffer<VertexData>* vb = mesh->WithColors(); 
//	vb->Init(); 
//	buffersList.push_back(vb); 
//
//	indexBuffer = mesh->CreateIndexBuffer(); 
//	indexBuffer->Init(); 
//
//	delete mesh;
//}