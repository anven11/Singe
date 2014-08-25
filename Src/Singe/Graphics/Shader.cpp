#include <SingeStd.h>

#include "Shader.h"

#include "..\Geometry\Vec3.h"
#include "..\Geometry\Vec4.h"
#include "Renderer.h"

#include "..\Utilities\String.h"
#include "..\Utilities\Macros.h"
#include "..\Utilities\FileSystem.h"
#include "..\Utilities\Math.h"

namespace Singe
{
	namespace Graphics
	{
		//
		// Konstruktor.
		//
		Shader::Shader(void)
		{
			m_vertexBufferOffset = 0;
			m_indexBufferOffset = 0;
			m_constantBufferCount = 0;
		}

		//
		// Destruktor.
		//
		Shader::~Shader(void)
		{
			SAFE_DELETE(m_pVertexData);

			m_pVS.Release();
			m_pPS.Release();

			m_pVertexBuffer.Release();
			m_pIndexBuffer.Release();
		}

		void Shader::Apply(void)
		{
			const Renderer* pRenderer = Renderer::Get();

			if (m_pVS) // Vertex shader.
			{
				pRenderer->GetD3DImmediateContext()->VSSetShader(m_pVS, nullptr, 0);
				pRenderer->GetD3DImmediateContext()->VSSetConstantBuffers(0, m_constantBufferCount, m_pConstantBuffers);
			}

			if (m_pPS) // Pixel shader.
			{
				pRenderer->GetD3DImmediateContext()->PSSetShader(m_pPS, nullptr, 0);
				pRenderer->GetD3DImmediateContext()->PSSetConstantBuffers(0, m_constantBufferCount, m_pConstantBuffers);
			}

			if (m_pInputLayout) // Input layout.
			{
				pRenderer->GetD3DImmediateContext()->IASetInputLayout(m_pInputLayout);
			}

			UINT strides[1] = { m_shaderDesc.vertexDataStride };
			UINT offsets[1] = { 0 };
			ID3D11Buffer* p[1] = { m_pVertexBuffer };
			pRenderer->GetD3DImmediateContext()->IASetVertexBuffers(0, 1, p, strides, offsets);
			pRenderer->GetD3DImmediateContext()->IASetIndexBuffer(m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
			pRenderer->GetD3DImmediateContext()->IASetPrimitiveTopology(m_shaderDesc.primitiveTopology);
		}

		HRESULT Shader::CreateFromFile(const ShaderDesc& shaderDesc, const std::wstring& filename)
		{
			m_shaderDesc = shaderDesc;

			std::wstring filename_sourceCode = filename + L".hlsl";
			std::wstring filename_byteCode = filename + L".csa";

			UINT compilerFlags = 0;
		#if defined(_DEBUG)
			compilerFlags |= D3DCOMPILE_DEBUG;
		#endif

			const Renderer* pRenderer = Renderer::Get();

			// Ladda källkoden.
			std::ifstream file(filename_sourceCode);
			if (!file.is_open())
			{
				MessageBox(nullptr, L"Could not open shader file.", nullptr, MB_ICONERROR);
				return EXIT_FAILURE;
			}

			std::string buffer, data;
			while (std::getline(file, buffer)) data += buffer + "\n";
			file.close();

			//MessageBoxA(nullptr, data.c_str(), nullptr, MB_ICONINFORMATION);

			//
			// Kompilera vertex-shadern.
			//
			CComPtr<ID3DBlob> pVSBlob = nullptr;
			//if (!FileSystem::FileExists("AmbientOcclusion\\Shader.vs"))
			if (true)
			{
				std::cout << "Compiling vertex shader..." << std::endl;

				// Kompilera vertex-shadern.
				CComPtr<ID3DBlob> pErrors = nullptr;
				HRESULT hr = D3DCompile2(data.c_str(), data.length(), nullptr, nullptr, nullptr, "VS", "vs_5_0", compilerFlags, 0, 0, nullptr, 0, &pVSBlob, &pErrors);
				if (pErrors)
				{
					std::stringstream ss;
					ss << "Shader errors:\n\n";
					ss << (const char*)pErrors->GetBufferPointer();
					MessageBoxA(nullptr, ss.str().c_str(), nullptr, MB_ICONERROR);
					return EXIT_FAILURE;
				}

				if (pVSBlob == nullptr)
				{
					MessageBox(nullptr, L"Could not compile vertex shader. Dunno why.", nullptr, MB_ICONERROR);
					return EXIT_FAILURE;
				}

				// Spara maskinkoden till en fil så vi slipper kompilera om och om och om och om och om och om och om och om igen.
				D3DWriteBlobToFile(pVSBlob, L"AmbientOcclusion\\Shader.vs", TRUE);

				CComPtr<ID3DBlob> pVSDebugInfo = nullptr;
				D3DGetDebugInfo(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &pVSDebugInfo);
				if (pVSDebugInfo)
				{
					std::cout << "Vertex shader debug info:" << std::endl << (const char*)pVSDebugInfo->GetBufferPointer() << std::endl;
				}
			}
			else
			{
				std::cout << "Loading vertex shader from file..." << std::endl;

				// Ladda maskinkoden till blobben.
				D3DReadFileToBlob(L"AmbientOcclusion\\Shader.vs", &pVSBlob);
			}

			// Skapa vertex-shadern.
			HR(pRenderer->GetD3DDevice()->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVS));

			// Skapa input-layouten.
			HRESULT hr = pRenderer->GetD3DDevice()->CreateInputLayout(&m_shaderDesc.vertexElementDescs[0], (UINT)m_shaderDesc.vertexElementDescs.size(), pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pInputLayout);
			if (hr == E_INVALIDARG)
			{
				MessageBox(nullptr, L"Din vertex-layout ser inte ut som den gör i shaderfilen.", nullptr, MB_ICONERROR);
				return hr;
			}

			HR(hr);

			//
			// Kompilera pixel-shadern.
			//
			CComPtr<ID3DBlob> pPSBlob = nullptr;
			//if (!FileSystem::FileExists("AmbientOcclusion\\Shader.ps"))
			if (true)
			{
				std::cout << "Compiling pixel shader..." << std::endl;

				CComPtr<ID3DBlob> pErrors = nullptr;
				HRESULT hr = D3DCompile2(data.c_str(), data.length(), nullptr, nullptr, nullptr, "PS", "ps_5_0", compilerFlags, 0, 0, nullptr, 0, &pPSBlob, &pErrors);
				if (pErrors)
				{
					std::stringstream ss;
					ss << "Shader errors:\n\n";
					ss << (const char*)pErrors->GetBufferPointer();
					MessageBoxA(nullptr, ss.str().c_str(), nullptr, MB_ICONERROR);
					return EXIT_FAILURE;
				}

				if (pPSBlob == nullptr)
				{
					MessageBox(nullptr, L"Could not compile pixel shader. Dunno why.", nullptr, MB_ICONERROR);
					return EXIT_FAILURE;
				}

				// Spara maskinkoden till en fil så vi slipper kompilera om och om igen.
				D3DWriteBlobToFile(pPSBlob, L"AmbientOcclusion\\Shader.ps", TRUE);

				CComPtr<ID3DBlob> pPSDebugInfo = nullptr;
				D3DGetDebugInfo(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), &pPSDebugInfo);
				if (pPSDebugInfo)
				{
					std::cout << "Pixel shader debug info:" << std::endl << (const char*)pPSDebugInfo->GetBufferPointer() << std::endl;
					pPSDebugInfo = nullptr;
				}
			}
			else
			{
				std::cout << "Loading pixel shader from file..." << std::endl;

				// Ladda maskinkoden till blobben.
				D3DReadFileToBlob(L"AmbientOcclusion\\Shader.ps", &pPSBlob);
			}

			HR(pRenderer->GetD3DDevice()->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPS)); // Skapa pixel-shadern.
			pPSBlob = nullptr;

			// Skapa konstantbuffertarna.
			m_constantBufferCount = (UINT)m_shaderDesc.constantBufferDescs.size();
			m_pConstantBuffers = new ID3D11Buffer*[m_constantBufferCount];

			for (unsigned int i = 0; i < m_constantBufferCount; i++)
			{
				D3D11_BUFFER_DESC cbd = { };
				cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				cbd.ByteWidth = Singe::Math::RoundUp(m_shaderDesc.constantBufferDescs[i].constantBufferSize, 16);
				cbd.Usage = D3D11_USAGE_DYNAMIC;

				HR(pRenderer->GetD3DDevice()->CreateBuffer(&cbd, nullptr, &m_pConstantBuffers[i]));

				D3D11_MAPPED_SUBRESOURCE ms = { };
				HR(pRenderer->GetD3DImmediateContext()->Map(m_pConstantBuffers[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &ms));
				pRenderer->GetD3DImmediateContext()->Unmap(m_pConstantBuffers[i], 0);
			}

			static const unsigned int MAX_VERTICES = 10000;
			static const unsigned int MAX_INDICES = 10000;

			m_pVertexData = new unsigned char[MAX_VERTICES * m_shaderDesc.vertexDataStride];

			// Skapa vertexbufferten.
			D3D11_BUFFER_DESC vbd = { };
			vbd.Usage = D3D11_USAGE_DEFAULT;
			vbd.ByteWidth = sizeof(m_shaderDesc.vertexDataStride) * MAX_VERTICES;
			vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			HR(pRenderer->GetD3DDevice()->CreateBuffer(&vbd, nullptr, &m_pVertexBuffer));

			// Skapa den sekundära vertexbufferten.
			D3D11_BUFFER_DESC vbsd = { };
			vbsd.Usage = D3D11_USAGE_STAGING;
			vbsd.ByteWidth = sizeof(m_shaderDesc.vertexDataStride) * MAX_VERTICES;
			vbsd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

			HR(pRenderer->GetD3DDevice()->CreateBuffer(&vbsd, nullptr, &m_pVertexBufferStaging));

			// Skapa indexbufferten.
			D3D11_BUFFER_DESC ibd = { };
			ibd.Usage = D3D11_USAGE_DEFAULT;
			ibd.ByteWidth = sizeof(UINT) * MAX_INDICES;
			ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;

			HR(pRenderer->GetD3DDevice()->CreateBuffer(&ibd, nullptr, &m_pIndexBuffer));

			// Skapa den sekundära indexbufferten.
			D3D11_BUFFER_DESC ibsd = { };
			ibsd.Usage = D3D11_USAGE_STAGING;
			ibsd.ByteWidth = sizeof(UINT) * MAX_VERTICES;
			ibsd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;

			HR(pRenderer->GetD3DDevice()->CreateBuffer(&ibsd, nullptr, &m_pIndexBufferStaging));

			return EXIT_SUCCESS;
		}

		HRESULT Shader::RegisterGeometry(const void* vertices, UINT vertexCount, const UINT* indices, UINT indexCount, UINT* vertexBufferOffset, UINT* indexBufferOffset)
		{
			const Renderer* pRenderer = Renderer::Get();

			if (vertices && vertexCount > 0)
			{
				UINT vertexDataSize = vertexCount * m_shaderDesc.vertexDataStride;
				memcpy(&m_pVertexData[m_vertexBufferOffset], vertices, vertexDataSize);

				// Skriv till den sekundära vertexbufferten.
				D3D11_MAPPED_SUBRESOURCE ms = { };
				HR(pRenderer->GetD3DImmediateContext()->Map(m_pVertexBufferStaging, 0, D3D11_MAP_WRITE, 0, &ms));
				memcpy(ms.pData, m_pVertexData, m_vertexBufferOffset + vertexDataSize);
				pRenderer->GetD3DImmediateContext()->Unmap(m_pVertexBufferStaging, 0);

				// Kopiera till den primära bufferten.
				pRenderer->GetD3DImmediateContext()->CopyResource(m_pVertexBuffer, m_pVertexBufferStaging);
		
				if (vertexBufferOffset)
					(*vertexBufferOffset) = m_vertexBufferOffset / m_shaderDesc.vertexDataStride;

				m_vertexBufferOffset += vertexDataSize;
			}

			if (indices && indexCount > 0)
			{
				if (indexBufferOffset)
					(*indexBufferOffset) = (UINT)m_indexData.size();

				for (UINT i = 0; i < indexCount; i++)
				{
					m_indexData.push_back(indices[i]);
				}

				// Skriv till den sekundära indexbufferten.
				D3D11_MAPPED_SUBRESOURCE ms = { };
				HR(pRenderer->GetD3DImmediateContext()->Map(m_pIndexBufferStaging, 0, D3D11_MAP_WRITE, 0, &ms));
				memcpy(ms.pData, &m_indexData[0], m_indexData.size() * sizeof(UINT));
				pRenderer->GetD3DImmediateContext()->Unmap(m_pIndexBufferStaging, 0);

				// Kopiera till den primära bufferten.
				pRenderer->GetD3DImmediateContext()->CopyResource(m_pIndexBuffer, m_pIndexBufferStaging);
			}

			return S_OK;
		}

		void Shader::UpdateConstantBuffer(unsigned int index, const void* data)
		{
			if (index >= m_constantBufferCount)
			{
				MessageBox(NULL, L"Invalid constant buffer index.", NULL, MB_ICONEXCLAMATION);
				return;
			}

			const Renderer* pRenderer = Renderer::Get();

			// Skriv till konstantbufferten.
			D3D11_MAPPED_SUBRESOURCE ms = { };
			if (SUCCEEDED(pRenderer->GetD3DImmediateContext()->Map(m_pConstantBuffers[index], 0, D3D11_MAP_WRITE_DISCARD, 0, &ms)))
			{
				memcpy(ms.pData, data, m_shaderDesc.constantBufferDescs[index].constantBufferSize);
				pRenderer->GetD3DImmediateContext()->Unmap(m_pConstantBuffers[index], 0);
			}
		}
	}
}