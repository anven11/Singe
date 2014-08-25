#ifndef __TEXTURERENDERTARGET_H__
#define __TEXTURERENDERTARGET_H__

namespace Singe
{
	namespace Graphics
	{
		class TextureRenderTarget
		{
		public:

			///<summary>Konstruktor.</summary>
			TextureRenderTarget(void);

			///<summary>Destruktor.</summary>
			~TextureRenderTarget(void);

			///<summary>Skapa texturen.</summary>
			///<param name="width">Texturens bredd i pixlar.</param>
			///<param name="height">Texturens höjd i pixlar.</param>
			const HRESULT Create(unsigned int width, unsigned int height);

			///<summary>Påbörja rendering till texturen.</summary>
			const void PreRender(void);

			///<summary>Avsluta rendering till texturen.</summary>
			const HRESULT PostRender(void);

			//
			// Åtkomstmetoder.
			//

			///<summary>Hämta render-targetet.</summary>
			const CComPtr<ID2D1RenderTarget> GetD2DRenderTarget(void) const
			{
				return m_pD2DRenderTarget;
			}

			///<summary>Hämta shaderresursvyn associerad med objektet.</summary>
			const CComPtr<ID3D11ShaderResourceView>	GetD3DShaderResourceView(void) const
			{
				return m_pD3DShaderResourceView;
			}

			///<summary>Hämta texturens bredd i pixlar.</summary>
			const UINT GetWidth(void) const
			{
				return m_width;
			}

			///<summary>Hämta texturens höjd i pixlar.</summary>
			const UINT GetHeight(void) const
			{
				return m_height;
			}

			///<summary>Hämta texturens storlek i bytes.</summary>
			const UINT GetSize(void) const
			{
				return m_size;
			}

		private:
			static const GUID m_pixelFormatWIC; // Texturens WIC-pixelformat.
			static const DXGI_FORMAT m_pixelFormatDXGI; // Texturens DXGI-format.
			static const UINT m_pixelFormatBPP; // Pixelstorlek.

			CComPtr<IDXGISurface>				m_pDXGISurface;
			CComPtr<ID3D11Texture2D>			m_pD3DTexture2D; // Direct3D-texturen.
			CComPtr<ID3D11ShaderResourceView>	m_pD3DShaderResourceView; // Shaderresursvyn.
			CComPtr<ID2D1RenderTarget>			m_pD2DRenderTarget; // Direct2D's render target.

			UINT m_width; // Texturens bredd i pixlar.
			UINT m_height; // Texturens höjd i pixlar.
			UINT m_size; // Texturens storlek i bytes.
			UINT m_pixelDataStride;
		};
	}
}

#endif // __TEXTURERENDERTARGET_H__