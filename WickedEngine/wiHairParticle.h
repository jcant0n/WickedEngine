#pragma once
#include "CommonInclude.h"
#include "wiGraphicsAPI.h"
#include "ShaderInterop.h"
#include "wiSPTree.h"


struct SkinnedVertex;
struct Mesh;
struct Object;
struct Material;
struct Camera;

class wiArchive;

class wiHairParticle
{
public:
	struct Patch
	{
		XMFLOAT4 posLen;
		UINT normalRand;
		UINT tangent;
	};
private:
	CBUFFER(ConstantBuffer, CBSLOT_OTHER_HAIRPARTICLE)
	{
		XMMATRIX mWorld;
		XMFLOAT3 color; float __pad0;
		float LOD0;
		float LOD1;
		float LOD2;
		float __pad1;
	};
	CBUFFER(BitonicSortConstantBuffer, 0)
	{
		UINT iLevel;
		UINT iLevelMask;
		UINT iWidth;
		UINT iHeight;
	};

	wiGraphicsTypes::GPUBuffer *cb;
	wiGraphicsTypes::GPUBuffer *particleBuffer;
	wiGraphicsTypes::GPUBuffer *ib;
	wiGraphicsTypes::GPUBuffer *ib_transposed;
	wiGraphicsTypes::GPUBuffer *drawargs;

	static wiGraphicsTypes::VertexShader *vs;
	static wiGraphicsTypes::PixelShader *ps[SHADERTYPE_COUNT];
	static wiGraphicsTypes::ComputeShader *cs_BITONICSORT;
	static wiGraphicsTypes::ComputeShader *cs_TRANSPOSE;
	static wiGraphicsTypes::GPUBuffer* cb_BITONIC;
	static wiGraphicsTypes::DepthStencilState *dss;
	static wiGraphicsTypes::RasterizerState *rs,*ncrs;
	static wiGraphicsTypes::BlendState *bs;
	static int LOD[3];
public:
	static void LoadShaders();

public:
	wiHairParticle();
	wiHairParticle(const std::string& newName, float newLen, int newCount
		, const std::string& newMat, Object* newObject, const std::string& densityGroup, const std::string& lengthGroup);
	wiHairParticle(const wiHairParticle& other);

	void CleanUp();

	void Generate();
	void ComputeCulling(Camera* camera, GRAPHICSTHREAD threadID);
	void Draw(Camera* camera, SHADERTYPE shaderType, GRAPHICSTHREAD threadID);

	static void CleanUpStatic();
	static void SetUpStatic();
	static void Settings(int lod0,int lod1,int lod2);

	float length;
	int count;
	std::string name, densityG, lenG, materialName;
	Material* material;
	XMFLOAT4X4 OriginalMatrix_Inverse;
	Object* object;
	size_t particleCount;

	void Serialize(wiArchive& archive);
};

