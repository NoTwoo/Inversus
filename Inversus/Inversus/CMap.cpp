#include "Define.h"

void CMap::Draw() 
{
	HDC hdc = GetDC(GAMEMANAGER->getHWND());
	HBRUSH hBrush, hOldBrush;

	hBrush = CreateSolidBrush(m_color);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	FillRect(hdc, &m_rect, hBrush);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
	ReleaseDC(GAMEMANAGER->getHWND(), hdc);


}

void CMap::ChangeType() { m_bIsBlack = !m_bIsBlack;}
bool CMap::IsBlack() { return m_bIsBlack; }

CMap::CMap() { m_bIsBlack = true; }