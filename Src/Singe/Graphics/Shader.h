#ifndef __SHADER_H__
#define __SHADER_H__

namespace Singe
{
	namespace Graphics
	{
		struct ConstantBufferDesc
		{
			UINT constantBufferSize; // Storleken på konstantbufferten.
		};

		struct ShaderDesc
		{
			UINT vertexDataStride; // Sorleken på vertexdatan.
			std::vector<D3D11_INPUT_ELEMENT_DESC> vertexElementDescs; // Beskrivningarna av vertexens element.
			std::vector<ConstantBufferDesc> constantBufferDescs; 
			D3D11_PRIMITIVE_TOPOLOGY primitiveTopology;
		};

		class Shader
		{
		public:
			Shader(void);
			~Shader(void);

			/// <summary>Rendera med effekten.</summary>
			void Apply(void);

			/// <summary>Kompilera shadern från en fil.</summary>
			/// <param name="shaderData">Informationen som beskriver hur shadern ska fungera.</param>
			/// <param name="filename">Filnamnet UTAN filändelse.</param>
			HRESULT CreateFromFile(const ShaderDesc& shaderData, const std::wstring& filename);

			/// <summary>Registrera geometri i minnet.</summary>
			/// <param name="vertices">En pekare till alla vertices som ska registreras.</param>
			/// <param name="vertexCount">Antalet vertices som ska registreras.</param>
			/// <param name="indices">En pekare till alla indexar som ska registreras.</param>
			/// <param name="indexCount">Antalet indexar som ska registreras.</param>
			HRESULT RegisterGeometry(const void* vertices, UINT vertexCount, const UINT* indices, UINT indexCount, UINT* vertexBufferOffset, UINT* indexBufferOffset);

			/// <summary>Uppdatera en konstantbuffert.</summary>
			/// <param name="index">Konstantbuffertens index. Buffertarna indexeras i den ordning som specifierade i ShaderDesc.</param>
			/// <param name="data">En pekare till konstantbuffertens data.</param>
			void UpdateConstantBuffer(unsigned int index, const void* data);

		private:
			ShaderDesc m_shaderDesc;

			CComPtr<ID3D11Buffer> m_pVertexBuffer; // Använd en D3D11_USAGE_DEFAULT-buffert för att kunna läsa snabbt.
			CComPtr<ID3D11Buffer> m_pVertexBufferStaging; // Använd en D3D11_USAGE_STAGING-buffert för att kunna skriva snabbt.

			CComPtr<ID3D11Buffer> m_pIndexBuffer;
			CComPtr<ID3D11Buffer> m_pIndexBufferStaging;

			unsigned char* m_pVertexData;
			std::vector<UINT> m_indexData;

			UINT m_vertexBufferOffset;
			UINT m_indexBufferOffset;

			UINT m_constantBufferCount;
			ID3D11Buffer** m_pConstantBuffers;

			CComPtr<ID3D11InputLayout> m_pInputLayout; // Shaderns input layout.
			CComPtr<ID3D11VertexShader> m_pVS; // Vertex shader.
			CComPtr<ID3D11PixelShader> m_pPS; // Pixel shader.
		};
	}
}

#endif // __SHADER_H__