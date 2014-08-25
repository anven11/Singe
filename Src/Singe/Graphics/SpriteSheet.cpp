#include <GameStd.h>

#include "Spritesheet.h"

#include <Singe\Graphics\Renderer.h>
#include <Singe\Utilities\Macros.h>

SpriteSheet::SpriteSheet(void)
{
	m_pD3DTexture2D = nullptr;
	m_pShaderResource = nullptr;
}

SpriteSheet::~SpriteSheet(void)
{
	SAFE_RELEASE(m_pD3DTexture2D);
	SAFE_RELEASE(m_pShaderResource);
}

HRESULT SpriteSheet::LoadFromFile(std::wstring filename, unsigned int spriteWidth, int spriteHeight)
{
	const Singe::Graphics::Renderer* pRenderer = Singe::Graphics::Renderer::Get();

	m_spriteWidth = spriteWidth;
	m_spriteHeight = spriteHeight;

	// Ladda texturen.
	IWICBitmapDecoder* pWICDecoder = nullptr;
	IWICBitmapFrameDecode* pWICSource = nullptr;
	IWICFormatConverter* pWICConverter = nullptr;

	HR(pRenderer->GetWICFactory()->CreateDecoderFromFilename(filename.c_str(), 0, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pWICDecoder));
	HR(pWICDecoder->GetFrame(0, &pWICSource));
	HR(pRenderer->GetWICFactory()->CreateFormatConverter(&pWICConverter));
	HR(pWICConverter->Initialize(pWICSource, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeMedianCut));
	HR(pRenderer->GetD2DImmediateContext()->CreateBitmapFromWicBitmap(pWICConverter, &m_pD2DBitmap));
	HR(pWICSource->GetSize(&m_spriteSheetWidth, &m_spriteSheetHeight));

	SAFE_RELEASE(pWICDecoder);
	SAFE_RELEASE(pWICSource);
	SAFE_RELEASE(pWICConverter);

	// Skapa D2D-texturen.
	D3D11_TEXTURE2D_DESC td = { };
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Width = m_spriteWidth;
	td.Height = m_spriteHeight;
	td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;

	HR(pRenderer->GetD3DDevice()->CreateTexture2D(&td, nullptr, &m_pD3DTexture2D));

	IDXGISurface1* pDXGISurface = nullptr;
	HR(m_pD3DTexture2D->QueryInterface(__uuidof(IDXGISurface1), (void**)&pDXGISurface));

	D2D1_RENDER_TARGET_PROPERTIES rtp = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);
	HR(pRenderer->GetD2DFactory()->CreateDxgiSurfaceRenderTarget(pDXGISurface, &rtp, &m_pD2DRenderTarget));

	this->SetFrame(0);

	return EXIT_SUCCESS;
}

HRESULT SpriteSheet::SetFrame(unsigned int frame)
{
	const Singe::Graphics::Renderer* pRenderer = Singe::Graphics::Renderer::Get();

	m_pD2DRenderTarget->DrawBitmap(m_pD2DBitmap);

	return EXIT_SUCCESS;
}