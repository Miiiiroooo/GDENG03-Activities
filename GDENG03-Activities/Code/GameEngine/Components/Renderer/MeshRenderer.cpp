#include "MeshRenderer.h"
#include "GameEngine/Meshes/CubeMesh.h"
#include "GameEngine/Meshes/SphereMesh.h"
#include "GameEngine/Meshes/QuadMesh.h"
#include "GameEngine/Meshes/CircleMesh.h"
#include "GameEngine/Meshes/PlaneMesh.h"
#include "GameEngine/Meshes/CylinderMesh.h"
#include "GameEngine/Meshes/ConeMesh.h"


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
		mesh = new SphereMesh<VertexData>();
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
	case EPrimitiveMeshTypes::Cylinder:
		mesh = new CylinderMesh<VertexData>();
		break;
	case EPrimitiveMeshTypes::Cone:
		mesh = new ConeMesh<VertexData>(); 
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