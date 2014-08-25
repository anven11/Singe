#ifndef __SPRITESHEET_H__
#define __SPRITESHEET_H__

/// <summary>Halvf�rdig.</summary>
class SpriteSheet
{
public:
	SpriteSheet(void);
	~SpriteSheet(void);

	HRESULT LoadFromFile(std::wstring filename, unsigned int spriteWidth, int spriteHeight);

	HRESULT SetFrame(unsigned int frame);

	const ID3D11ShaderResourceView* GetShaderResource(void) const
	{
		return m_pShaderResource;
	}

	const ID2D1Bitmap* GetD2DBitmap(void) const
	{
		return m_pD2DBitmap;
	}

private:
	ID3D11Texture2D* m_pD3DTexture2D;
	ID3D11ShaderResourceView* m_pShaderResource;
	ID2D1Bitmap1* m_pD2DBitmap;
	ID2D1RenderTarget* m_pD2DRenderTarget;

	UINT m_spriteWidth; // En enstaka bildrutas bredd.
	UINT m_spriteHeight; // En enstaka bildrutas h�jd.
	UINT m_spriteSheetWidth; // Hela arkets bredd.
	UINT m_spriteSheetHeight; // Hela arkets h�jd.
};

#endif // __SPRITESHEET_H__