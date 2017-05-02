#include "Define.h"

const std::string& CText::GetString() { return m_str; }
void CText::SetString(const std::string& a_str) { m_str = a_str; }

const STTextInfo& CText::GetPenInfo() { return m_stTextInfo; }
void CText::SetTextInfo(const STTextInfo& a_stPenInfo) { m_stTextInfo = a_stPenInfo; }

void CText::Draw()
{
	HDC hdc = GetDC(GAMEMANAGER->getHWND());
	HBRUSH hBrush, hOldBrush;
	HFONT hFont, hOldFont;

	hBrush = CreateSolidBrush(m_color);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	hFont = CreateFont(m_stTextInfo.width, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("±Ã¼­"));

	hOldFont = (HFONT)SelectObject(hdc, hFont);

	SetBkColor(hdc, m_color);
	SetTextColor(hdc, m_stTextInfo.color);
	DrawText(hdc, m_str.c_str(), m_str.length(), &m_rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldFont);
	DeleteObject(hBrush);
	DeleteObject(hFont);
	ReleaseDC(GAMEMANAGER->getHWND(), hdc);
}