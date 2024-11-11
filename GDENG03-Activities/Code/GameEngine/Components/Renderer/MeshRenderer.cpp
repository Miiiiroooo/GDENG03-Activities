#include "MeshRenderer.h"
#include "GameEngine/Meshes/CubeMesh.h"
#include "GameEngine/Meshes/SphereMesh.h"
#include "GameEngine/Meshes/QuadMesh.h"
#include "GameEngine/Meshes/CircleMesh.h"
#include "GameEngine/Meshes/PlaneMesh.h"
#include "GameEngine/Meshes/CylinderMesh.h"
#include "GameEngine/Meshes/ConeMesh.h"

#include "GameEngine/Graphics/Materials/UnlitColorMaterial.h"


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
	tinyobj::attrib_t attributes;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> material;
	std::string warning, error;

	if (tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error, (STANDARD_MODEL_PATH + modelName).c_str()))
	{
		if (isRainbowed) CreateNonPrimitiveColored(attributes, shapes);
		else CreateNonPrimitiveTextured(attributes, shapes);

		InitRenderer();
	}
	else
	{
		std::string toPrint = "error loading obj file\nError: " + error + "\nWarning: " + warning + "\n";
		OutputDebugString(toPrint.c_str());
	}
}

void MeshRenderer::CreateNonPrimitiveColored(tinyobj::attrib_t& attributes, std::vector<tinyobj::shape_t>& shapes)
{
	std::vector<VUnlitColorData> vertices; 
	std::vector<unsigned short> indices; 
	std::unordered_map<std::string, int> vIndexTable; 
	int index = 0; 

	for (int i = 0; i < shapes[0].mesh.indices.size(); i++) 
	{
		tinyobj::index_t vData = shapes[0].mesh.indices[i]; 
		std::string indexStr = std::to_string(vData.vertex_index) + std::to_string(vData.normal_index) + std::to_string(vData.texcoord_index); 

		if (i == 0 || vIndexTable[indexStr] == 0) 
		{
			vIndexTable[indexStr] = index; 
			index++; 

			VUnlitColorData v;
			v.pos = Vector3(attributes.vertices[vData.vertex_index * 3 + 0], 
				attributes.vertices[vData.vertex_index * 3 + 1], 
				attributes.vertices[vData.vertex_index * 3 + 2]); 

			v.vColor = Vector3(MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange(), MathUtils::RandFloatWithRange());

			vertices.push_back(v);
		}

		indices.push_back(vIndexTable[indexStr]);
	}

	VertexBuffer<VUnlitColorData>* vb = new VertexBuffer<VUnlitColorData>(GraphicsEngine::GetInstance(), vertices); 
	vb->Init(); 
	vertexBuffer = vb;

	indexBuffer = new IndexBuffer(GraphicsEngine::GetInstance(), indices);
	indexBuffer->Init();
}

void MeshRenderer::CreateNonPrimitiveTextured(tinyobj::attrib_t& attributes, std::vector<tinyobj::shape_t>& shapes)
{
	std::vector<VLitTextureData> vertices;
	std::vector<unsigned short> indices; 
	std::unordered_map<std::string, int> vIndexTable; 
	int index = 0; 

	for (int i = 0; i < shapes[0].mesh.indices.size(); i++) 
	{
		tinyobj::index_t vData = shapes[0].mesh.indices[i]; 
		std::string indexStr = std::to_string(vData.vertex_index) + std::to_string(vData.normal_index) + std::to_string(vData.texcoord_index); 

		if (i == 0 || vIndexTable[indexStr] == 0) 
		{
			vIndexTable[indexStr] = index; 
			index++; 

			VLitTextureData v; 
			v.pos = Vector3(attributes.vertices[vData.vertex_index * 3 + 0], 
				attributes.vertices[vData.vertex_index * 3 + 1], 
				attributes.vertices[vData.vertex_index * 3 + 2]); 

			v.normals = Vector3(attributes.normals[vData.normal_index * 3 + 0], 
				attributes.normals[vData.normal_index * 3 + 1], 
				attributes.normals[vData.normal_index * 3 + 2]); 

			v.uv = Vector2(attributes.texcoords[vData.texcoord_index * 2 + 0], 
				attributes.texcoords[vData.texcoord_index * 2 + 1]); 

			vertices.push_back(v);
		}

		indices.push_back(vIndexTable[indexStr]); 
	}

	VertexBuffer<VLitTextureData>* vb = new VertexBuffer<VLitTextureData>(GraphicsEngine::GetInstance(), vertices);
	vb->Init();
	vertexBuffer = vb;

	indexBuffer = new IndexBuffer(GraphicsEngine::GetInstance(), indices);
	indexBuffer->Init();
}