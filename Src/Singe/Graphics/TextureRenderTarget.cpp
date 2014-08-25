#include <SingeStd.h>

#include "TextureRenderTarget.h"

#include "Renderer.h"
#include "..\Utilities\Macros.h"

namespace Singe
{
	namespace Graphics
	{
		//
		// Konstanter.
		//

		const GUID TextureRenderTarget::m_pixelFormatWIC = GUID_WICPixelFormat32bppBGRA;
		const DXGI_FORMAT TextureRenderTarget::m_pixelFormatDXGI = DXGI_FORMAT_B8G8R8A8_UNORM;
		const UINT TextureRenderTarget::m_pixelFormatBPP = 32;

		TextureRenderTarget::TextureRenderTarget(void)
		{
		}

		TextureRenderTarget::~TextureRenderTarget(void)
		{
			// Fria resurser.
			m_pDXGISurface.Release();
			m_pD3DShaderResourceView.Release();
			m_pD3DTexture2D.Release();
			m_pD2DRenderTarget.Release();
		}

		const HRESULT TextureRenderTarget::Create(unsigned int width, unsigned int height)
		{
			// Direkta definitioner.
			m_width = width;
			m_height = height;

			const Graphics::Renderer* pRenderer = Graphics::Renderer::Get();

			D3D11_TEXTURE2D_DESC d3dTextureDesc;
			d3dTextureDesc.ArraySize = 1;
			d3dTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			d3dTextureDesc.CPUAccessFlags = 0;
			d3dTextureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			d3dTextureDesc.Width = width;
			d3dTextureDesc.Height = height;
			d3dTextureDesc.MipLevels = 1;
			d3dTextureDesc.MiscFlags = 0;
			d3dTextureDesc.SampleDesc.Count = 1;
			d3dTextureDesc.SampleDesc.Quality = 0;
			d3dTextureDesc.Usage = D3D11_USAGE_DEFAULT;

			HR(pRenderer->GetD3DDevice()->CreateTexture2D(&d3dTextureDesc, nullptr, &m_pD3DTexture2D));
			HR(m_pD3DTexture2D->QueryInterface(&m_pDXGISurface));

			D2D1_RENDER_TARGET_PROPERTIES d2drtp = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);

			HR(pRenderer->GetD2DFactory()->CreateDxgiSurfaceRenderTarget(m_pDXGISurface, &d2drtp, &m_pD2DRenderTarget));

			return S_OK;
		}

		const void TextureRenderTarget::PreRender(void)
		{
			m_pD2DRenderTarget->BeginDraw();
		}

		const HRESULT TextureRenderTarget::PostRender(void)
		{
			const Graphics::Renderer* pRenderer = Graphics::Renderer::Get();

			HR(m_pD2DRenderTarget->EndDraw());

			/*if (FAILED(m_pD2DRenderTarget->EndDraw()))
			{
				MessageBox(nullptr, L"Error rendering to TextureRenderTarget", L"Error!", MB_ICONERROR);
				return;
			}*/

			return S_OK;
		}
	}
}