#include "MeshRenderer.h"
#include "GameEngine/Meshes/CubeMesh.h"
#include "GameEngine/Meshes/SphereMesh.h"
#include "GameEngine/Meshes/QuadMesh.h"
#include "GameEngine/Meshes/CircleMesh.h"
#include "GameEngine/Meshes/PlaneMesh.h"
#include "GameEngine/Meshes/CylinderMesh.h"
#include "GameEngine/Meshes/ConeMesh.h"

#include "GameEngine/Graphics/Materials/UnlitColorMaterial.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>


MeshRenderer::MeshRenderer() : ARenderer("MeshRenderer")
{
	topologyType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

MeshRenderer::MeshRenderer(AMaterial* material) : ARenderer("MeshRenderer", material)
{
	topologyType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
}

MeshRenderer::~MeshRenderer()
{

}

void MeshRenderer::LoadPrimitive(EPrimitiveMeshTypes type, bool isRainbowed)
{
	AMesh<VUnlitColorData>* mesh = nullptr;

	switch (type)
	{
	case EPrimitiveMeshTypes::Cube:
		mesh = new CubeMesh<VUnlitColorData>(); 
		break;
	case EPrimitiveMeshTypes::Sphere:
		mesh = new SphereMesh<VUnlitColorData>();
		break;
	case EPrimitiveMeshTypes::Quad:
		mesh = new QuadMesh<VUnlitColorData>();
		break;
	case EPrimitiveMeshTypes::Circle:
		mesh = new CircleMesh<VUnlitColorData>();
		break;
	case EPrimitiveMeshTypes::Plane:
		mesh = new PlaneMesh<VUnlitColorData>();
		break;
	case EPrimitiveMeshTypes::Cylinder:
		mesh = new CylinderMesh<VUnlitColorData>();
		break;
	case EPrimitiveMeshTypes::Cone:
		mesh = new ConeMesh<VUnlitColorData>(); 
		break;
	default:
		break;
	}

	if (mesh == nullptr) return;

	InitRenderer();

	UnlitColorMaterial* unlit = (UnlitColorMaterial*)material;
	mesh->SetColor(unlit->GetColor());

	VertexBuffer<VUnlitColorData>* vb = mesh->CreateVertexBuffer(isRainbowed);
	vb->Init();
	vertexBuffer = vb;

	indexBuffer = mesh->CreateIndexBuffer();
	indexBuffer->Init();

	delete mesh;
}

void MeshRenderer::LoadNonPrimitive(std::string modelName, bool isRainbowed)
{
	Assimp::Importer imprtr; 
	const auto pModel = imprtr.ReadFile((STANDARD_MODEL_PATH + modelName), 
		aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | 
		aiProcess_OptimizeMeshes | aiProcess_ImproveCacheLocality | aiProcess_ValidateDataStructure | 
		aiProcess_FindInstances | aiProcess_PreTransformVertices | aiProcess_SortByPType | aiProcess_FindDegenerates);

	if (pModel == nullptr) { OutputDebugString(imprtr.GetErrorString()); return; } 

	if (isRainbowed) CreateNonPrimitiveColored(pModel);
	else CreateNonPrimitiveTextured(pModel);

	InitRenderer();
}

void MeshRenderer::CreateNonPrimitiveColored(const aiScene* model)
{
	std::vector<VUnlitColorData> vertices; 
	std::vector<unsigned short> indices; 
	for (int i = 0; i < model->mNumMeshes; i++) 
	{
		const auto pMesh = model->mMeshes[i]; 

		for (int j = 0; j < pMesh->mNumVertices; j++) 
		{
			VUnlitColorData v; 
			v.pos = Vector3(pMesh->mVertices[j].x, pMesh->mVertices[j].y, pMesh->mVertices[j].z); 
			v.vColor = Vector3(MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange()); 
			vertices.push_back(v); 
		}

		for (int j = 0; j < pMesh->mNumFaces; j++) 
		{
			for (int k = 0; k < pMesh->mFaces[j].mNumIndices; k++) 
			{
				indices.push_back(pMesh->mFaces[j].mIndices[k]); 
			}
		}
	}

	VertexBuffer<VUnlitColorData>* vb = new VertexBuffer<VUnlitColorData>(GraphicsEngine::GetInstance(), vertices); 
	vb->Init(); 
	vertexBuffer = vb; 

	indexBuffer = new IndexBuffer(GraphicsEngine::GetInstance(), indices); 
	indexBuffer->Init(); 
}

void MeshRenderer::CreateNonPrimitiveTextured(const aiScene* model)
{
	std::vector<VLitTextureData> vertices;
	std::vector<unsigned short> indices; 
	for (int i = 0; i < model->mNumMeshes; i++) 
	{ 
		const auto pMesh = model->mMeshes[i]; 

		for (int j = 0; j < pMesh->mNumVertices; j++) 
		{
			VLitTextureData v;
			v.pos = Vector3(pMesh->mVertices[j].x, pMesh->mVertices[j].y, pMesh->mVertices[j].z); 
			v.normals = pMesh->HasNormals() ? Vector3(pMesh->mNormals[j].x, pMesh->mNormals[j].y, pMesh->mNormals[j].z) : Vector3::Zero; 
			v.uv = pMesh->HasTextureCoords(0) ? Vector2(pMesh->mTextureCoords[0][j].x, pMesh->mTextureCoords[0][j].y) : Vector2::Zero;
			vertices.push_back(v); 
		}

		for (int j = 0; j < pMesh->mNumFaces; j++) 
		{
			for (int k = 0; k < pMesh->mFaces[j].mNumIndices; k++) 
			{
				indices.push_back(pMesh->mFaces[j].mIndices[k]); 
			}
		}
	}

	VertexBuffer<VLitTextureData>* vb = new VertexBuffer<VLitTextureData>(GraphicsEngine::GetInstance(), vertices);
	vb->Init(); 
	vertexBuffer = vb; 

	indexBuffer = new IndexBuffer(GraphicsEngine::GetInstance(), indices); 
	indexBuffer->Init(); 
}