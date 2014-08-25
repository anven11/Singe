#include <SingeStd.h>

#include "Texture.h"

#include "Renderer.h"
#include "..\Utilities\FileSystem.h"
#include "..\Utilities\Macros.h"

namespace Singe
{
	namespace Graphics
	{
		//
		// Konstanter.
		//

		const GUID Texture::m_pixelFormatWIC =			GUID_WICPixelFormat32bppBGRA;
		const DXGI_FORMAT Texture::m_pixelFormatDXGI =	DXGI_FORMAT_B8G8R8A8_UNORM;
		const UINT Texture::m_pixelFormatBPP =			32;

		Texture::Texture(void)
		{
		}

		Texture::~Texture(void)
		{
			m_pShaderResourceView.Release();
			m_pTexture2D.Release();
		}

		const HRESULT Texture::CreateFromFile(const std::wstring& filename)
		{
			if (!Singe::Utilities::FileSystem::FileExists(filename))
			{
				std::wcout << L"Could not find texture: " << filename << std::endl;
				return CreateFromFile(L"Assets\\Textures\\Missing.png");
			}

			const Graphics::Renderer* pRenderer = Graphics::Renderer::Get();

			// Ladda texturen.
			CComPtr<IWICBitmapDecoder> pWICDecoder;
			CComPtr<IWICBitmapFrameDecode> pWICFrame;
			CComPtr<IWICFormatConverter> pWICConverter;

			HR(pRenderer->GetWICFactory()->CreateDecoderFromFilename(filename.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pWICDecoder));
			HR(pWICDecoder->GetFrame(0, &pWICFrame));

			// Konvertera bilden till det angivna formatet.
			HR(pRenderer->GetWICFactory()->CreateFormatConverter(&pWICConverter));
			HR(pWICConverter->Initialize(pWICFrame, m_pixelFormatWIC, WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeMedianCut));

			// Hämta texturens upplösning.
			HR(pWICFrame->GetSize(&m_width, &m_height));

			// Kopiera bitmappens pixlar till en array.
			UINT pixelDataStride = (m_width * m_pixelFormatBPP + 7) / 8;
			m_size = pixelDataStride * m_height;
			auto pPixelData = std::unique_ptr<BYTE>(new BYTE[m_size]);
			HR(pWICFrame->CopyPixels(nullptr, pixelDataStride, m_size, pPixelData.get()));

			// Skapa D3D-texturen.
			D3D11_TEXTURE2D_DESC textureDesc = { };
			textureDesc.Width = m_width;
			textureDesc.Height = m_height;
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = m_pixelFormatDXGI;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA textureData = { };
			textureData.pSysMem = pPixelData.get();
			textureData.SysMemPitch = pixelDataStride;
			textureData.SysMemSlicePitch = m_size;

			HR(pRenderer->GetD3DDevice()->CreateTexture2D(&textureDesc, &textureData, &m_pTexture2D));

			// Skapa shaderresursvyn.
			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = { };
			srvDesc.Format = textureDesc.Format;
			srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MipLevels = textureDesc.MipLevels;

			HR(pRenderer->GetD3DDevice()->CreateShaderResourceView(m_pTexture2D, &srvDesc, &m_pShaderResourceView));

			pPixelData.release();

			return S_OK;
		}
	}
}