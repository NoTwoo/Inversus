#include "Define.h"

void CBullet::ChkCollision() {};

void CBullet::Draw()
{
	HDC hdc = GetDC(GAMEMANAGER->getHWND());
	HBRUSH hBrush, hOldBrush;

	hBrush = CreateSolidBrush(m_color);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, (m_pos.x + NPC_MOVE_POINT * 3) - MEMIUM_BULLET_SIZE, (m_pos.y + NPC_MOVE_POINT * 3) - MEMIUM_BULLET_SIZE,
		(m_pos.x + NPC_MOVE_POINT * 3) + MEMIUM_BULLET_SIZE, (m_pos.y + NPC_MOVE_POINT * 3) + MEMIUM_BULLET_SIZE);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
	ReleaseDC(GAMEMANAGER->getHWND(), hdc);
}


void CBullet::DeleteMe() { m_bDeleteMe = true; }
const bool& CBullet::GetDelete() { return m_bDeleteMe; }

CBullet::CBullet()
{
	ZeroMemory(&m_CenterPos, sizeof(m_CenterPos));
	m_bDeleteMe = false;

}