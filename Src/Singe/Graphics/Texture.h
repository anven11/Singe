#ifndef __TEXTURE_H__
#define __TEXTURE_H__

namespace Singe
{
	namespace Graphics
	{
		class Texture
		{
		public:

			///<summary>Konstruktor.</summary>
			Texture(void);

			///<summary>Destruktor.</summary>
			~Texture(void);

			///<summary>Skapa texturen utifr�n en fil.</summary>
			const HRESULT CreateFromFile(const std::wstring& filename);

			//
			// �tkomstmetoder.
			//

			///<summary>H�mta shaderresursvyn associerad med objektet.</summary>
			const CComPtr<ID3D11ShaderResourceView> GetD3DShaderResourceView(void) const
			{
				return m_pShaderResourceView;
			}

			///<summary>H�mta texturen associerad med objektet.</summary>
			const CComPtr<ID3D11Texture2D> GetD3DTexture2D(void) const
			{
				return m_pTexture2D;
			}

			///<summary>H�mta texturens bredd i pixlar.</summary>
			const UINT GetWidth(void) const
			{
				return m_width;
			}

			///<summary>H�mta texturens h�jd i pixlar.</summary>
			const UINT GetHeight(void) const
			{
				return m_height;
			}

			///<summary>H�mta texturens storlek i bytes.</summary>
			const UINT GetSize(void) const
			{
				return m_size;
			}

		private:
			static const GUID m_pixelFormatWIC; // Texturens WIC-pixelformat.
			static const DXGI_FORMAT m_pixelFormatDXGI; // Texturens DXGI-format.
			static const UINT m_pixelFormatBPP; // Pixelstorlek.

			CComPtr<ID3D11Texture2D>			m_pTexture2D;
			CComPtr<ID3D11ShaderResourceView>	m_pShaderResourceView;

			UINT m_width; // Texturens bredd i pixlar.
			UINT m_height; // Texturens h�jd i pixlar.
			UINT m_size; // Texturens storlek i bytes.
		};
	}
}

#endif // __TEXTURE_H__