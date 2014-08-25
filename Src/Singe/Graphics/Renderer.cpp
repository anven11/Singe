#include <SingeStd.h>

#include "Renderer.h"
#include "..\Utilities\Macros.h"

#include <initguid.h>
DEFINE_GUID(DXGI_DEBUG_ALL, 0xe48ae283, 0xda80, 0x490b, 0x87, 0xe6, 0x43, 0xe9, 0xa9, 0xcf, 0xda, 0x8);

namespace Singe
{
	namespace Graphics
	{
		Renderer* Renderer::m_pRenderer;

		Renderer::Renderer(void)
		{
			if (m_pRenderer)
			{
				MessageBox(nullptr, L"Du kan ju inte skapa flera renderare juee.", L"Error", MB_ICONEXCLAMATION);
				return;
			}

			m_pRenderer = this;
		}

		Renderer::~Renderer(void)
		{
			m_pDWriteFactory.Release();

			m_pD2DBackBuffer.Release();
			m_pD2DImmediateContext.Release();
			m_pD2DDevice.Release();
			m_pD2DFactory.Release();

			m_pD3DImmediateContext.Release();
			m_pD3DDevice.Release();

			m_pDXGIAdapter.Release();
			m_pDXGIDevice.Release();
			m_pDXGIFactory.Release();
		}

		HRESULT Renderer::Reset(const RendererSettings& settings)
		{
			//
			// Initiera Direct3D.
			//
			{
				UINT deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if defined(_DEBUG)
				deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

				// Skapa Direct3D-enheten.
				D3D_FEATURE_LEVEL featureLevel;
				HR(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, deviceFlags, nullptr, 0, D3D11_SDK_VERSION, &m_pD3DDevice, &featureLevel, &m_pD3DImmediateContext));

#if defined(_DEBUG)
				HR(m_pD3DDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&m_pD3DDebug)));
				HR(m_pD3DDebug->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY));
#endif

				if (featureLevel < D3D_FEATURE_LEVEL_11_0)
				{
					// Grafikkortet stödjer inte version 11.0.
					MessageBox(nullptr, L"Din dator stödjer inte Direct3D 11.0\nKöp en ny.", nullptr, MB_ICONERROR);
					return E_INVALIDARG;
				}

				DXGI_SAMPLE_DESC sampleDesc = { };
				if (settings.antiAliasing == RendererSettings::MSAA)
				{
					// Kolla vilken kvalité grafikkortet klarar av.
					UINT quality;
					HRESULT hr = m_pD3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, settings.msaaSampleCount, &quality);
					if (FAILED(hr) || quality == 0)
					{
						MessageBox(nullptr, L"För mycket anti-aliasing, noob.", nullptr, MB_ICONERROR);
						return E_INVALIDARG;
					}

					sampleDesc.Count = settings.msaaSampleCount;
					sampleDesc.Quality = quality - 1;
				}
				else
				{
					sampleDesc.Count = 1;
					sampleDesc.Quality = 0;
				}

				DXGI_SWAP_CHAIN_DESC sd = { };
				sd.BufferDesc.Width = settings.resolution.x;
				sd.BufferDesc.Height = settings.resolution.y;
				sd.BufferDesc.RefreshRate.Numerator = 60;
				sd.BufferDesc.RefreshRate.Denominator = 1;
				sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
				sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST;
				sd.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
				sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				sd.BufferCount = 1;
				sd.OutputWindow = settings.hWnd;
				sd.Windowed = settings.windowMode != RendererSettings::Fullscreen;
				sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
				sd.Flags = 0;
				sd.SampleDesc = sampleDesc;

				HR(m_pD3DDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&m_pDXGIDevice)));
				HR(m_pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&m_pDXGIAdapter)));
				HR(m_pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_pDXGIFactory)));

				HR(m_pDXGIFactory->CreateSwapChain(m_pD3DDevice, &sd, &m_pSwapChain));
				HR(m_pDXGIFactory->MakeWindowAssociation(settings.hWnd, DXGI_MWA_NO_ALT_ENTER)); // Avaktivera Alt+Enter.

				CComPtr<ID3D11Texture2D> pBackBufferTexture;
				HR(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBufferTexture)));
				HR(m_pD3DDevice->CreateRenderTargetView(pBackBufferTexture, nullptr, &m_pRenderTargetView));
				pBackBufferTexture = nullptr;

				// Skapa en djupschablon.
				D3D11_TEXTURE2D_DESC dsd;
				dsd.Width = settings.resolution.x;
				dsd.Height = settings.resolution.y;
				dsd.MipLevels = 1;
				dsd.ArraySize = 1;
				dsd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				dsd.Usage = D3D11_USAGE_DEFAULT;
				dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
				dsd.CPUAccessFlags = 0;
				dsd.MiscFlags = 0;
				dsd.SampleDesc = sampleDesc;

				HR(m_pD3DDevice->CreateTexture2D(&dsd, nullptr, &m_pDepthStencilBuffer));
				HR(m_pD3DDevice->CreateDepthStencilView(m_pDepthStencilBuffer, nullptr, &m_pDepthStencilView));

				if (!m_pRenderTargetView)
				{
					MessageBox(nullptr, L"Kunde inte skapa renderingsmålet.", nullptr, MB_ICONERROR);
					return E_POINTER;
				}

				if (!m_pDepthStencilBuffer)
				{
					MessageBox(nullptr, L"Kunde inte skapa djupschablonen.", nullptr, MB_ICONERROR);
					return E_POINTER;
				}


				{
					ID3D11RenderTargetView* p[1] = { m_pRenderTargetView };
					m_pD3DImmediateContext->OMSetRenderTargets(1, p, m_pDepthStencilView);
				}

				// Sätt fönstrets viewport.
				m_screenViewport.TopLeftX = 0;
				m_screenViewport.TopLeftY = 0;
				m_screenViewport.Width = static_cast<float>(settings.resolution.x);
				m_screenViewport.Height = static_cast<float>(settings.resolution.y);
				m_screenViewport.MinDepth = 0.0f;
				m_screenViewport.MaxDepth = 1.0f;
				m_pD3DImmediateContext->RSSetViewports(1, &m_screenViewport);
			}

			//
			// Initiera Direct2D.
			//
			{
				D2D1_FACTORY_TYPE factoryType = D2D1_FACTORY_TYPE_MULTI_THREADED;
				D2D1_FACTORY_OPTIONS factoryOptions = { };

#if defined(_DEBUG)
				factoryOptions.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#else
				factoryOptions.debugLevel = D2D1_DEBUG_LEVEL_NONE;
#endif

				HR(D2D1CreateFactory(factoryType, __uuidof(ID2D1Factory1), &factoryOptions, (void**)&m_pD2DFactory));
				HR(m_pD2DFactory->ReloadSystemMetrics());
				HR(m_pD2DFactory->CreateDevice(m_pDXGIDevice, &m_pD2DDevice));

				HR(m_pD2DDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_pD2DImmediateContext));

				float dpiX, dpiY;
				m_pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

				D2D1_BITMAP_PROPERTIES1 bp = { };
				bp.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, D2D1_ALPHA_MODE_IGNORE);
				bp.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
				bp.dpiX = dpiX;
				bp.dpiY = dpiY;

				CComPtr<IDXGISurface1> backBufferSurface;
				HR(m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1), reinterpret_cast<void**>(&backBufferSurface)));

				HR(m_pD2DImmediateContext->CreateBitmapFromDxgiSurface(backBufferSurface, bp, &m_pD2DBackBuffer));

				m_pD2DImmediateContext->SetTarget(m_pD2DBackBuffer);
				m_pD2DImmediateContext->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);
			}

			//
			// Initiera DirectWrite.
			//
			{
				HR(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory1), reinterpret_cast<IUnknown**>(&m_pDWriteFactory)));
			}

			//
			// Initiera WIC.
			//
			{
				CoInitialize(nullptr);
				HR(CoCreateInstance(CLSID_WICImagingFactory1, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (void**)&m_pWICFactory));
			}

			return EXIT_SUCCESS;
		}
	}
}