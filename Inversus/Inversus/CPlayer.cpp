#include "Define.h"


void CPlayer::Draw()
{
	HDC hdc = GetDC(GAMEMANAGER->getHWND());
	HBRUSH hBrush, hOldBrush;

	hBrush = CreateSolidBrush(m_color);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	RoundRect(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, 10, 10);

	SelectObject(hdc, hOldBrush);
	DeleteObject(hBrush);
	ReleaseDC(GAMEMANAGER->getHWND(), hdc);

	for (auto d : m_vItemList) d->Draw();

}

void CPlayer::Move(const EMove& a_eMove)
{
	switch (a_eMove) {
	case EMove::UP: 
		if (ChkCollision(EMove::UP)) break;
		m_pos.y -= OBJECT_SIZE + INTERVAL;
		m_rect.top = m_pos.y; m_rect.bottom = m_rect.top + CHARACTER_SIZE;
		RePositionBullet();
		break;
	case EMove::DOWN:
		if (ChkCollision(EMove::DOWN)) break;
		m_pos.y += OBJECT_SIZE + INTERVAL;
		m_rect.top = m_pos.y; m_rect.bottom = m_rect.top + CHARACTER_SIZE;
		RePositionBullet();
		break;
	case EMove::LEFT:
		if (ChkCollision(EMove::LEFT)) break;
		m_pos.x -= OBJECT_SIZE + INTERVAL;
		m_rect.left = m_pos.x; m_rect.right = m_rect.left + CHARACTER_SIZE;
		RePositionBullet();
		break;
	case EMove::RIGHT: 
		if (ChkCollision(EMove::RIGHT)) break;
		m_pos.x += OBJECT_SIZE + INTERVAL;
		m_rect.left = m_pos.x; m_rect.right = m_rect.left + CHARACTER_SIZE;
		RePositionBullet();
		break;
	
	}
}

void CPlayer::Attack(const EAttack& a_eAttack)
{
	switch (a_eAttack) {
	case EAttack::UP_ATTACK: break;
	case EAttack::DOWN_ATTACK: break;
	case EAttack::LEFT_ATTACK: break;
	case EAttack::RIGHT_ATTACK: break;
	default: break;
	}

}

bool CPlayer::ChkCollision(const EMove& a_eMove)
{
	switch (a_eMove) {
	case EMove::UP:
		for (auto d : GAMEMANAGER->GetGameList()) {
			if (dynamic_cast<CMap*>(d)) {
				CMap* cMap = dynamic_cast<CMap*>(d);
				if (cMap->IsBlack()) {
					if ((m_rect.left / (OBJECT_SIZE + INTERVAL)) == cMap->GetRect().left / (OBJECT_SIZE + INTERVAL)
						&& (m_rect.top / (OBJECT_SIZE + INTERVAL)) - 1 == cMap->GetRect().top / (OBJECT_SIZE + INTERVAL))
						return true;
				}
			}
		}
		break;
	case EMove::DOWN:
		for (auto d : GAMEMANAGER->GetGameList()) {
			if (dynamic_cast<CMap*>(d)) {
				CMap* cMap = dynamic_cast<CMap*>(d);
				if (cMap->IsBlack()) {
					if ((m_rect.left / (OBJECT_SIZE + INTERVAL)) == cMap->GetRect().left / (OBJECT_SIZE + INTERVAL)
						&& (m_rect.top / (OBJECT_SIZE + INTERVAL)) + 1 == cMap->GetRect().top / (OBJECT_SIZE + INTERVAL))
						return true;
				}
			}
		}
		break;
	case EMove::LEFT:
		for (auto d : GAMEMANAGER->GetGameList()) {
			if (dynamic_cast<CMap*>(d)) {
				CMap* cMap = dynamic_cast<CMap*>(d);
				if (cMap->IsBlack()) {
					if ((m_rect.left / (OBJECT_SIZE + INTERVAL)) - 1 == cMap->GetRect().left / (OBJECT_SIZE + INTERVAL)
						&& (m_rect.top / (OBJECT_SIZE + INTERVAL)) == cMap->GetRect().top / (OBJECT_SIZE + INTERVAL))
						return true;
				}
			}
		}
		break;
	case EMove::RIGHT:
		for (auto d : GAMEMANAGER->GetGameList()) {
			if (dynamic_cast<CMap*>(d)) {
				CMap* cMap = dynamic_cast<CMap*>(d);
				if (cMap->IsBlack()) {
					if ((m_rect.left / (OBJECT_SIZE + INTERVAL)) + 1 == cMap->GetRect().left / (OBJECT_SIZE + INTERVAL)
						&& (m_rect.top / (OBJECT_SIZE + INTERVAL)) == cMap->GetRect().top / (OBJECT_SIZE + INTERVAL))
						return true;
				}
			}
		}
		break;
	}

	return false;
}

void CPlayer::RePositionBullet()
{
	for (auto d : m_vItemList) {
		d->SetRect(m_rect);
		CRotatingBullet* pRotatingBullet = dynamic_cast<CRotatingBullet*>(d);
		pRotatingBullet->SetCenter();
	}

}

void CPlayer::InitItem()
{
	

	float Angle = 0.0f;
	for (int i = 0; i < MAX_BULLET; ++i) {

		CObject* pBullet = new CRotatingBullet;

		pBullet->SetColor(RGB(255, 255, 255));
		pBullet->SetRect(m_rect);
		CRotatingBullet* pRotatingBullet = dynamic_cast<CRotatingBullet*>(pBullet);
		pRotatingBullet->SetCenter();

		pRotatingBullet->SetAngle(Angle);

		m_vItemList.push_back(pBullet);
		Angle += 360.0f / MAX_BULLET;
	}
}

CPlayer::CPlayer()
{
	m_bytLife = 3;

}