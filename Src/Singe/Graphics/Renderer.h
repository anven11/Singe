#ifndef __RENDERER_H__
#define __RENDERER_H__

namespace Singe
{
	namespace Graphics
	{
		struct RendererSettings
		{
			// Fönstrets visningsläge.
			enum WindowMode
			{
				Windowed = 0,
				Fullscreen,
				Noborder,
			};

			enum AntiAliasing
			{
				None = 0, // Ingen.
				MSAA, // Multisampling.
				FXAA, // Ungefärlig anti-aliasing.
				SSAA, // Supersampling.
				CSAA, // Någon sorts anti-aliasing.
			};

			HWND hWnd;
			WindowMode windowMode;
			AntiAliasing antiAliasing;
			UINT msaaSampleCount;
			POINT resolution;
		};

		class Renderer
		{
		public:
			Renderer(void);
			~Renderer(void);

			HRESULT Reset(const RendererSettings& settings);

			static const Renderer* Get(void) 
			{
				return m_pRenderer;
			}

			// Direct3D-accessors.
			const CComPtr<ID3D11Device> GetD3DDevice(void) const
			{
				return m_pD3DDevice;
			}

			const CComPtr<ID3D11DeviceContext> GetD3DImmediateContext(void) const
			{
				return m_pD3DImmediateContext;
			}

			const CComPtr<ID3D11Texture2D> GetDepthStencilBuffer(void) const
			{
				return m_pDepthStencilBuffer;
			}

			const CComPtr<ID3D11RenderTargetView> GetRenderTargetView(void) const
			{
				return m_pRenderTargetView;
			}

			const CComPtr<ID3D11DepthStencilView> GetDepthStencilView(void) const
			{
				return m_pDepthStencilView;
			}

			const D3D11_VIEWPORT GetScreenViewport(void) const
			{
				return m_screenViewport;
			}

			// Direct2D-accessors.
			const CComPtr<ID2D1Factory1> GetD2DFactory(void) const
			{
				return m_pD2DFactory;
			}

			const CComPtr<ID2D1Device> GetD2DDevice(void) const
			{
				return m_pD2DDevice;
			}

			const CComPtr<ID2D1DeviceContext> GetD2DImmediateContext(void) const
			{
				return m_pD2DImmediateContext;
			}

			const CComPtr<ID2D1Bitmap1> GetD2DBackBuffer(void) const
			{
				return m_pD2DBackBuffer;
			}

			// DirectWrite-accessors.
			CComPtr<IDWriteFactory1> GetDWriteFactory(void) const
			{
				return m_pDWriteFactory;
			}

			// DXGI-accessors.
			CComPtr<IDXGISwapChain> GetSwapChain(void) const
			{
				return m_pSwapChain;
			}

			// WIC-accessors.
			CComPtr<IWICImagingFactory> GetWICFactory(void) const
			{
				return m_pWICFactory;
			}

		private:
			static Renderer* m_pRenderer;

			// Direct3D 11-komponenter.
			CComPtr<ID3D11Device> m_pD3DDevice;
			CComPtr<ID3D11DeviceContext> m_pD3DImmediateContext;
			CComPtr<ID3D11Texture2D> m_pDepthStencilBuffer;
			CComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
			CComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
			D3D11_VIEWPORT m_screenViewport;

			// Direct2D-komponenter.
			CComPtr<ID2D1Factory1> m_pD2DFactory;
			CComPtr<ID2D1Device> m_pD2DDevice;
			CComPtr<ID2D1DeviceContext> m_pD2DImmediateContext;
			CComPtr<ID2D1Bitmap1> m_pD2DBackBuffer;

			// DirectWrite-komponenter.
			CComPtr<IDWriteFactory1> m_pDWriteFactory;

			// DXGI-komponenter.
#if defined(_DEBUG)
			CComPtr<ID3D11Debug> m_pD3DDebug;
#endif
			CComPtr<IDXGISwapChain> m_pSwapChain;
			CComPtr<IDXGIDevice> m_pDXGIDevice;
			CComPtr<IDXGIAdapter> m_pDXGIAdapter;
			CComPtr<IDXGIFactory> m_pDXGIFactory;

			// WIC-komponenter.
			CComPtr<IWICImagingFactory> m_pWICFactory;
		};
	}
}

#endif // __RENDERER_H__