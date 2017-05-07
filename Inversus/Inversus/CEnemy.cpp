#include "Define.h"

void CEnemy::Draw()
{
	HDC hdc = GetDC(GAMEMANAGER->getHWND());
	HBRUSH hBrush, hOldBrush;

	HPEN hPen, hOldPen;

	hBrush = CreateHatchBrush(HS_BDIAGONAL, m_color);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	hPen = CreatePen(BS_SOLID, static_cast<double>(0.1), m_color);
	hOldPen = (HPEN)SelectObject(hdc, hPen);


	SetBkMode(hdc, TRANSPARENT);
	RECT rect;
	memcpy(&rect, &m_rect, sizeof(m_rect));
	if (!m_bDrawExplosion) {
		// Draw Aura
		for (int y = 0; y < MAX_AURA_Y; ++y) {
			for (int x = 0; x < MAX_AURA_X; ++x) {
				Rectangle(hdc, (m_rect.left - CHARACTER_SIZE) + ((INTERVAL + CHARACTER_SIZE) * x),
					(m_rect.top - CHARACTER_SIZE) + ((INTERVAL + CHARACTER_SIZE) * y), m_rect.left + (CHARACTER_SIZE * x), m_rect.top + (CHARACTER_SIZE * y));

			}
		}
	}
	SetBkMode(hdc, OPAQUE);

	hBrush = CreateSolidBrush(m_color);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	if (!m_bDrawExplosion) {
		RoundRect(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, 10, 10);
		Move();
	}
	else {
		Ellipse(hdc, (m_pos.x + NPC_MOVE_POINT * 3) - m_bytBSIZE, (m_pos.y + NPC_MOVE_POINT * 3) - m_bytBSIZE,
			(m_pos.x + NPC_MOVE_POINT * 3) + m_bytBSIZE, (m_pos.y + NPC_MOVE_POINT * 3) + m_bytBSIZE);
		if (m_bytBSIZE < BSIZE) m_bytBSIZE += 5;
		else m_bDelete = true;
		
	}

	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, hOldPen);
	DeleteObject(hBrush);
	DeleteObject(hPen);
	ReleaseDC(GAMEMANAGER->getHWND(), hdc);


}

const bool& CEnemy::IsClose(const CMap* cMap) const
{
	if (sqrt(((m_pos.x - cMap->GetPos().x) *  (m_pos.x - cMap->GetPos().x)) +
		((m_pos.y - cMap->GetPos().y) *  (m_pos.y - cMap->GetPos().y)) < OBJECT_SIZE)
		) return true;

	return false;
}
void CEnemy::Move()
{
	for (CObject* d : GAMEMANAGER->GetGameList()) {
		if (dynamic_cast<CMap*>(d)) {
			CMap* cMap = dynamic_cast<CMap*>(d);
			if (!cMap->IsBlack() && IsClose(cMap)) {
				cMap->ChangeType();
				cMap->SetColor(RGB(0, 0, 0));
			}
		}
	}

	for (CObject* d : GAMEMANAGER->GetPlayerList()) {
		if (m_rect.left < d->GetRect().left) {
			m_pos.x += NPC_MOVE_POINT;
			m_rect.left += NPC_MOVE_POINT;
			m_rect.right = m_rect.left + CHARACTER_SIZE;
		}
		if (m_rect.left > d->GetRect().left) {
			m_pos.x -= NPC_MOVE_POINT;
			m_rect.left -= NPC_MOVE_POINT;
			m_rect.right = m_rect.left + CHARACTER_SIZE;
		}

		if (m_rect.top < d->GetRect().top) {
			m_pos.y += NPC_MOVE_POINT;
			m_rect.top += NPC_MOVE_POINT;
			m_rect.bottom = m_rect.top + CHARACTER_SIZE;
		}

		if (m_rect.top > d->GetRect().top) {
			m_pos.y -= NPC_MOVE_POINT;
			m_rect.top -= NPC_MOVE_POINT;
			m_rect.bottom = m_rect.top + CHARACTER_SIZE;
		}
	}

}



