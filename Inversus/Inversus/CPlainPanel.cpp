#include "CPlainPanel.h"
#include "Define.h"

bool CPlainPanel::GetDrawObject() { return m_bDrawObject; }
void CPlainPanel::SetDrawObject(const bool& a_bDrawObject) { m_bDrawObject = a_bDrawObject; }

void CPlainPanel::SetObjectPos(const POINT& a_pos) { m_ObjectPos = a_pos; }
const POINT& CPlainPanel::GetObjectPos() { return m_ObjectPos; }

void CPlainPanel::SetObjectRect(const RECT& a_rect)
{
	m_ObjectRect = a_rect;
	m_CenterPos.x = m_ObjectRect.left + ((m_ObjectRect.right - m_ObjectRect.left) / 2);
	m_CenterPos.y = m_ObjectRect.top + ((m_ObjectRect.bottom - m_ObjectRect.top) / 2);


	float Angle = 0.0f;
	for (int i = 0; i < 4; ++i) {
		m_stRotatingBullet[i].angle = Angle;
		m_stRotatingBullet[i].r = m_stRotatingBullet[i].angle * m_flDR;
		m_stRotatingBullet[i].pos.x = (sin(m_stRotatingBullet[i].r) * BSIZE) + m_CenterPos.x;
		m_stRotatingBullet[i].pos.y = (cos(m_stRotatingBullet[i].r) * BSIZE) + m_CenterPos.y;
		Angle += 60.0f;
	}

}

void CPlainPanel::SetObjectPenInfo(const STPenInfo& a_stPenInfo) { m_stObjectPenInfo = a_stPenInfo; }

void CPlainPanel::RotateBullet()
{

	for (int i = 0; i < 4; ++i) {
		if (m_stRotatingBullet[i].angle < 360.0f) m_stRotatingBullet[i].angle += 30.0f;
		else m_stRotatingBullet[i].angle = 30.0f;

		m_stRotatingBullet[i].r = m_stRotatingBullet[i].angle * m_flDR;
		m_stRotatingBullet[i].pos.x = (sin(m_stRotatingBullet[i].r) * BSIZE) + m_CenterPos.x;
		m_stRotatingBullet[i].pos.y = (cos(m_stRotatingBullet[i].r) * BSIZE) + m_CenterPos.y;
	}


}

void CPlainPanel::DrawObject()
{

	HDC hdc = GetDC(GAMEMANAGER->getHWND());
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	hPen = CreatePen(BS_SOLID, m_stObjectPenInfo.width, m_stObjectPenInfo.color);
	hOldPen = (HPEN)SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(m_color);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	// Dice
	RoundRect(hdc, m_ObjectRect.left, m_ObjectRect.top, m_ObjectRect.right, m_ObjectRect.bottom, 20, 20);

	for (int i = 0; i < 4; ++i) {
		hBrush = CreateSolidBrush(m_stRotatingBullet[i].color);
		hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		hPen = CreatePen(BS_SOLID, m_stObjectPenInfo.width, m_stRotatingBullet[i].color);
		hOldPen = (HPEN)SelectObject(hdc, hPen);
		Ellipse(hdc, m_stRotatingBullet[i].pos.x - 10, m_stRotatingBullet[i].pos.y - 10, m_stRotatingBullet[i].pos.x + 10, m_stRotatingBullet[i].pos.y + 10);
	}

	// Roate 
	RotateBullet();

	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	ReleaseDC(GAMEMANAGER->getHWND(), hdc);

}

CPlainPanel::CPlainPanel()
{
	m_bDrawObject = false;
	ZeroMemory(&m_ObjectPos, sizeof(m_ObjectPos));
	ZeroMemory(&m_ObjectRect, sizeof(m_ObjectRect));
	ZeroMemory(&m_CenterPos, sizeof(m_CenterPos));
	m_flDR = PIE / 180;

	m_stRotatingBullet[0].color = RGB(178, 235, 244); // BLUE
	m_stRotatingBullet[1].color = RGB(255, 255, 255); // WHITE
	m_stRotatingBullet[2].color = RGB(255, 255, 255); // WHITE
	m_stRotatingBullet[3].color = RGB(189, 189, 189); // GRAY

}