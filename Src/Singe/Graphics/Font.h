#ifndef __FONT_H__
#define __FONT_H__

namespace Singe
{
	namespace Graphics
	{
		enum TextAlignment
		{
			Left = 0, 
			Right, 
			Center, 
		};

		class Font
		{
		public:
			Font(void);
			~Font(void);

			const HRESULT Create(ID2D1RenderTarget* pTarget, const std::wstring& fontName);

			const void Draw(const std::wstring& text, D2D1_POINT_2F position, unsigned int fontSize, D2D1_COLOR_F color, TextAlignment alignment = TextAlignment::Left) const;
			const void Draw(const std::string& text, D2D1_POINT_2F position, unsigned int fontSize, D2D1_COLOR_F color, TextAlignment alignment = TextAlignment::Left) const;

		private:
			CComPtr<ID2D1SolidColorBrush> m_pTextBrush;
			CComPtr<IDWriteTextFormat> m_pTextFormat;
			CComPtr<IDWriteTextLayout> m_pTextLayout;
			CComPtr<ID2D1RenderTarget> m_pTarget;
		};
	}
}

#endif // __FONT_H__