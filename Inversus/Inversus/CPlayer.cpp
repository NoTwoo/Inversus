#include "Define.h"


void CPlayer::Draw()
{
	HDC hdc = GetDC(GAMEMANAGER->getHWND());
	HBRUSH hBrush, hOldBrush;

	hBrush = CreateSolidBrush(m_color);
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	RoundRect(hdc, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom, 10, 10);

	if (m_vItemList.size() > 0) {
		for (vector<CObject*>::iterator itor = m_vItemList.begin(); itor != m_vItemList.end();) {
			CRotatingBullet* cBullet = dynamic_cast<CRotatingBullet *>(*itor);
			if (cBullet->GetBulletAnimation().bShootAnimation) cBullet->DrawBurstingBullet();
			if (!cBullet->GetBulletAnimation().bShootAnimation && cBullet->GetBulletAnimation().bEndShootAnimation)
				itor = m_vItemList.erase(itor);
			else ++itor;

		}

	}

	if (ChkCollision()) {
		m_uLife--;
		GAMEMANAGER->DecreaseLife();
	}
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
	case EAttack::UP_ATTACK: Shoot(a_eAttack); break;
	case EAttack::DOWN_ATTACK: Shoot(a_eAttack); break;
	case EAttack::LEFT_ATTACK:  Shoot(a_eAttack); break;
	case EAttack::RIGHT_ATTACK: Shoot(a_eAttack); break;
	default: break;
	}

}

void CPlayer::Shoot(const EAttack& a_eAttack)
{
	if (m_vItemList.size() > 0) {
		for (vector<CObject*>::iterator itor = m_vItemList.begin(); itor != m_vItemList.end(); ++itor) {
			CRotatingBullet* cBullet = dynamic_cast<CRotatingBullet *>(*itor);
			if (!cBullet->GetBulletAnimation().bShootAnimation && !cBullet->GetBulletAnimation().bEndShootAnimation) {
				cBullet->OnBulletAnimation(a_eAttack);
				break;
			}
		}
		
	}
}

void CPlayer::ReloadBullet()
{

	if (m_vItemList.size() == 0) {
		float Angle = 0.0f;
		for (int i = m_vItemList.size(); i != MAX_BULLET; ++i) {

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

bool CPlayer::ChkCollision()
{

	for (auto d : GAMEMANAGER->GetNPCList()) {
		if (sqrt((((m_pos.x - d->GetPos().x) * (m_pos.x - d->GetPos().x)) +
			((m_pos.y - d->GetPos().y) * (m_pos.y - d->GetPos().y)))) < CHARACTER_SIZE / 2) return true;

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

	m_vert[0].x = m_rect.left;
	m_vert[0].y = m_rect.top + (CHARACTER_SIZE / 3) ;
	m_vert[1].x = m_rect.left + OBJECT_SIZE;
	m_vert[1].y = m_vert[0].y + (CHARACTER_SIZE / 3);

}

CPlayer::CPlayer()
{
	m_uLife = 3;

	// �׶��̼��� ������ǥ�� ����Ѵ�.
	m_vert[0].x = 0;
	m_vert[0].y = 0;

	// �׶��̼��� ���ۻ����� ����Ѵ�.
	m_vert[0].Red = 0xFFFF;
	m_vert[0].Green = 0xFFFF;
	m_vert[0].Blue = 0xFFFF;
	m_vert[0].Alpha = 0xFFFF;

	// �׶��̼��� ����ǥ�� ����Ѵ�.
	m_vert[1].x = 0;
	m_vert[1].y = 0;

	// �׶��̼��� ������ ����Ѵ�.
	m_vert[1].Red = 0x0000;
	m_vert[1].Green = 0x0000;
	m_vert[1].Blue = 0x0000;
	m_vert[1].Alpha = 0x0000;

	m_grect.UpperLeft = 0;
	m_grect.LowerRight = 1;

	m_bShootAnimation = false;

}