#ifndef _GRAPHICSRESOURCE_H_
#define _GRAPHICSRESOURCE_H_

#include "CommonInclude.h"
#include "wiGraphicsDescriptors.h"

#include <vector>

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11GeometryShader;
struct ID3D11DomainShader;
struct ID3D11HullShader;
struct ID3D11ComputeShader;
struct ID3D11SamplerState;
struct ID3D11ShaderResourceView;
struct ID3D11UnorderedAccessView;
struct ID3D11Buffer;
struct ID3D11InputLayout;
struct ID3D11BlendState;
struct ID3D11DepthStencilState;
struct ID3D11RasterizerState;
struct ID3D11RasterizerState2;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11Texture1D;
struct ID3D11Texture2D;
struct ID3D11Texture3D;
struct ID3D11Query;
struct ID3D11Predicate;

namespace wiGraphicsTypes
{
	class GraphicsDevice_DX11;

	class VertexShader
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11VertexShader*		resource_DX11;
	public:
		VertexShader();
		~VertexShader();

		bool IsValid() { return resource_DX11 != nullptr; }
	};

	class PixelShader
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11PixelShader*		resource_DX11;
	public:
		PixelShader();
		~PixelShader();

		bool IsValid() { return resource_DX11 != nullptr; }
	};

	class GeometryShader
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11GeometryShader*	resource_DX11;
	public:
		GeometryShader();
		~GeometryShader();

		bool IsValid() { return resource_DX11 != nullptr; }
	};

	class HullShader
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11HullShader*		resource_DX11;
	public:
		HullShader();
		~HullShader();

		bool IsValid() { return resource_DX11 != nullptr; }
	};

	class DomainShader
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11DomainShader*		resource_DX11;
	public:
		DomainShader();
		~DomainShader();

		bool IsValid() { return resource_DX11 != nullptr; }
	};

	class ComputeShader
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11ComputeShader*	resource_DX11;
	public:
		ComputeShader();
		~ComputeShader();

		bool IsValid() { return resource_DX11 != nullptr; }
	};

	class Sampler
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11SamplerState*	resource_DX11;
		SamplerDesc desc;
	public:
		Sampler();
		~Sampler();

		bool IsValid() { return resource_DX11 != nullptr; }
		SamplerDesc GetDesc() { return desc; }
	};

	class GPUResource
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11ShaderResourceView*			SRV_DX11;					// main resource SRV
		std::vector<ID3D11ShaderResourceView*>	additionalSRVs_DX11;		// can be used for sub-resources if requested

	protected:
		GPUResource();
		virtual ~GPUResource();
	};

	class GPUUnorderedResource
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11UnorderedAccessView*			UAV_DX11;					// main resource UAV
		std::vector<ID3D11UnorderedAccessView*>	additionalUAVs_DX11;		// can be used for sub-resources if requested

	protected:
		GPUUnorderedResource();
		virtual ~GPUUnorderedResource();
	};

	class GPUBuffer : public GPUResource, public GPUUnorderedResource
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11Buffer*		resource_DX11;
		GPUBufferDesc desc;
	public:
		GPUBuffer();
		virtual ~GPUBuffer();

		bool IsValid() { return resource_DX11 != nullptr; }
		GPUBufferDesc GetDesc() { return desc; }
	};

	class GPURingBuffer : public GPUBuffer
	{
		friend class GraphicsDevice_DX11;
	private:
		size_t byteOffset;
		uint64_t residentFrame;
	public:
		GPURingBuffer() : byteOffset(0), residentFrame(0) {}
		virtual ~GPURingBuffer() {}

		// The next appending to buffer will start at this offset
		size_t GetByteOffset() { return byteOffset; }
	};

	class VertexLayout
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11InputLayout*	resource_DX11;
	public:
		VertexLayout();
		~VertexLayout();

		bool IsValid() { return resource_DX11 != nullptr; }
	};

	class BlendState
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11BlendState*	resource_DX11;
		BlendStateDesc desc;
	public:
		BlendState();
		~BlendState();

		bool IsValid() { return resource_DX11 != nullptr; }
		BlendStateDesc GetDesc() { return desc; }
	};

	class DepthStencilState
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11DepthStencilState*	resource_DX11;
		DepthStencilStateDesc desc;
	public:
		DepthStencilState();
		~DepthStencilState();

		bool IsValid() { return resource_DX11 != nullptr; }
		DepthStencilStateDesc GetDesc() { return desc; }
	};

	class RasterizerState
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11RasterizerState*	resource_DX11;
		RasterizerStateDesc desc;
	public:
		RasterizerState();
		~RasterizerState();

		bool IsValid() { return resource_DX11 != nullptr; }
		RasterizerStateDesc GetDesc() { return desc; }
	};

	struct VertexShaderInfo {
		VertexShader* vertexShader;
		VertexLayout* vertexLayout;

		VertexShaderInfo();
		~VertexShaderInfo();
	};

	class Texture : public GPUResource, public GPUUnorderedResource
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11RenderTargetView*				RTV_DX11;
		std::vector<ID3D11RenderTargetView*>		additionalRTVs_DX11;
		bool								independentRTVArraySlices;
		bool								independentRTVCubemapFaces;
		bool								independentSRVMIPs;
		bool								independentUAVMIPs;
	public:

		Texture();
		virtual ~Texture();

		// if true, then each array slice will get a unique rendertarget
		void RequestIndepententRenderTargetArraySlices(bool value);
		// if true, then each face of the cubemap will get a unique rendertarget
		void RequestIndepententRenderTargetCubemapFaces(bool value);
		// if true, then each miplevel will get unique shader resource
		void RequestIndepententShaderResourcesForMIPs(bool value);
		// if true, then each miplevel will get unique unordered access resource
		void RequestIndepententUnorderedAccessResourcesForMIPs(bool value);
	};

	class Texture1D : public Texture
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11Texture1D*			texture1D_DX11;
		Texture1DDesc				desc;
	public:
		Texture1D();
		virtual ~Texture1D();

		Texture1DDesc GetDesc() const { return desc; }
	};

	class Texture2D : public Texture
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11DepthStencilView*				DSV_DX11;
		std::vector<ID3D11DepthStencilView*>		additionalDSVs_DX11;
		ID3D11Texture2D*					texture2D_DX11;
		Texture2DDesc						desc;
	public:
		Texture2D();
		virtual ~Texture2D();

		Texture2DDesc GetDesc() const { return desc; }
	};

	class Texture3D : public Texture
	{
		friend class GraphicsDevice_DX11;
	private:
		ID3D11Texture3D*			texture3D_DX11;
		Texture3DDesc				desc;
	public:
		Texture3D();
		virtual ~Texture3D();

		Texture3DDesc GetDesc() const { return desc; }
	};




	class GPUQuery
	{
		friend class GraphicsDevice_DX11;
	private:
		std::vector<ID3D11Query*>		resource_DX11;
		std::vector<int>					active;
		GPUQueryDesc				desc;
		int							async_frameshift;
	public:
		GPUQuery();
		virtual ~GPUQuery();

		bool IsValid() { return resource_DX11[0] != nullptr; }
		GPUQueryDesc GetDesc() { return desc; }

		BOOL	result_passed;
		UINT64	result_passed_sample_count;
		UINT64	result_timestamp;
		UINT64	result_timestamp_frequency;
		BOOL	result_disjoint;
	};
}

#endif // _GRAPHICSRESOURCE_H_
