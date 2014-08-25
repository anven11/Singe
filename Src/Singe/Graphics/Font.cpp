#include <SingeStd.h>

#include "Font.h"

#include "Renderer.h"
#include "..\Utilities\Macros.h"

namespace Singe
{
	namespace Graphics
	{
		Font::Font(void)
		{
		}

		Font::~Font(void)
		{
		}

		const HRESULT Font::Create(ID2D1RenderTarget* pTarget, const std::wstring& fontName)
		{
			// Direkt-definitioner.
			m_pTarget = pTarget;

			const Renderer* pRenderer = Renderer::Get();

			// Skapa brushen.
			HR(m_pTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &m_pTextBrush));

			// Ladda fonten.
			HR(pRenderer->GetDWriteFactory()->CreateTextFormat(fontName.c_str(), nullptr, DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 24.0f, L"en-us", &m_pTextFormat));

			return S_OK;
		}

		const void Font::Draw(const std::wstring& text, D2D1_POINT_2F position, unsigned int fontSize, D2D1_COLOR_F color, TextAlignment alignment) const
		{
			const Renderer* pRenderer = Renderer::Get();

			// Skapa text layout.
			pRenderer->GetDWriteFactory()->CreateTextLayout(text.c_str(), text.length(), m_pTextFormat, pRenderer->GetScreenViewport().Width, pRenderer->GetScreenViewport().Height, (IDWriteTextLayout**)&m_pTextLayout);

			DWRITE_TEXT_RANGE tr;
			tr.startPosition = 0;
			tr.length = text.length();

			m_pTextLayout->SetFontSize(static_cast<float>(fontSize), tr);

			if (alignment == TextAlignment::Left)
				m_pTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING);
			else if (alignment == TextAlignment::Right)
				m_pTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_TRAILING);
			else 
				m_pTextLayout->SetTextAlignment(DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_CENTER);

			m_pTextBrush->SetColor(color);

			m_pTarget->DrawTextLayout(position, m_pTextLayout, m_pTextBrush);
		}

		const void Font::Draw(const std::string& text, D2D1_POINT_2F position, unsigned int fontSize, D2D1_COLOR_F color, TextAlignment alignment) const
		{

		}
	}
}
