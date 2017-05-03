#include "Define.h"



void CRotatingBullet::SetAngle(const float& a_flAngle)
{
	m_flAngle = a_flAngle; 
	m_flRadian = m_flAngle * DR;
	m_pos.x = static_cast<LONG>((sin(m_flRadian) * (BSIZE / 2.5)) + m_CenterPos.x);
	m_pos.y = static_cast<LONG>((cos(m_flRadian) * (BSIZE / 2.5)) + m_CenterPos.y);
}

void CRotatingBullet::SetCenter()
{
	m_CenterPos.x = m_rect.left + ((m_rect.right - m_rect.left) / 2);
	m_CenterPos.y = m_rect.top + ((m_rect.bottom - m_rect.top) / 2);
}

void CRotatingBullet::Draw()
{
	HDC hdc = GetDC(GAMEMANAGER->getHWND());

	HBRUSH hBrush = CreateSolidBrush(m_color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	HPEN hPen = CreatePen(BS_SOLID, 1, m_color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	Ellipse(hdc, m_pos.x - SMALL_BULLET_SIZE, m_pos.y - SMALL_BULLET_SIZE, m_pos.x + SMALL_BULLET_SIZE, m_pos.y + SMALL_BULLET_SIZE);

	RotateBullet();

	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	ReleaseDC(GAMEMANAGER->getHWND(), hdc);

}

void CRotatingBullet::RotateBullet()
{
	if (m_flAngle < 360.0f) m_flAngle += (360.0f / MAX_BULLET) / 2;
	else m_flAngle = (360.0f / MAX_BULLET) / 2;

	m_flRadian = m_flAngle * DR;
	m_pos.x = static_cast<LONG>((sin(m_flRadian) * (BSIZE / 2.5)) + m_CenterPos.x);
	m_pos.y = static_cast<LONG>((cos(m_flRadian) * (BSIZE / 2.5)) + m_CenterPos.y);
}

CRotatingBullet::CRotatingBullet()
{

	m_flAngle = 0.0f;
	m_flRadian = 0.0f;

}