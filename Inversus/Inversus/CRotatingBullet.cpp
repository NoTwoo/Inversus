#include "Define.h"



void CRotatingBullet::SetAngle(const float& a_flAngle)
{
	m_flAngle = a_flAngle; 
	m_flRadian = m_flAngle * DR;
	m_pos.x = static_cast<LONG>((sin(m_flRadian) * (BSIZE / 2.5)) + m_CenterPos.x);
	m_pos.y = static_cast<LONG>((cos(m_flRadian) * (BSIZE / 2.5)) + m_CenterPos.y);
}
const float& CRotatingBullet::GetAngle() { return m_flAngle; }

void CRotatingBullet::SetCenter()
{
	m_CenterPos.x = m_rect.left + ((m_rect.right - m_rect.left) / 2);
	m_CenterPos.y = m_rect.top + ((m_rect.bottom - m_rect.top) / 2);
}

void CRotatingBullet::ChkCollision()
{
	for (CObject* d : GAMEMANAGER->GetGameList()) {
		if (dynamic_cast<CMap*>(d)) {
			CMap* cMap = dynamic_cast<CMap*>(d);

			if (m_stBulletAnimation.a_eAttack == EAttack::LEFT_ATTACK || m_stBulletAnimation.a_eAttack == EAttack::RIGHT_ATTACK) {
				if (sqrt(((m_stBulletAnimation.vert[1].x - cMap->GetPos().x)
					* (m_stBulletAnimation.vert[1].x - cMap->GetPos().x) +
					((m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - cMap->GetPos().y)
					* (
					(m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - cMap->GetPos().y))) < 28
					&& cMap->IsBlack()) {
					cMap->ChangeType();
					cMap->SetColor(RGB(255, 255, 255));

					GAMEMANAGER->IncreaseScore(KILL_POINT);

				}

				else if (sqrt(((m_stBulletAnimation.vert[0].x - cMap->GetPos().x)
					* (m_stBulletAnimation.vert[0].x - cMap->GetPos().x) +
					((m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - cMap->GetPos().y)
					* (
					(m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - cMap->GetPos().y))) < 28
					&& cMap->IsBlack()) {
					cMap->ChangeType();
					cMap->SetColor(RGB(255, 255, 255));
					GAMEMANAGER->IncreaseScore(KILL_POINT);
				}
			}

			else if (m_stBulletAnimation.a_eAttack == EAttack::UP_ATTACK) {

				if (sqrt(((m_stBulletAnimation.vert[1].x - cMap->GetPos().x)
					* (m_stBulletAnimation.vert[1].x - cMap->GetPos().x) +
					((m_stBulletAnimation.vert[0].y - (m_stBulletAnimation.vert[0].y - m_stBulletAnimation.vert[1].y)) - cMap->GetPos().y)
					* (
					(m_stBulletAnimation.vert[0].y - (m_stBulletAnimation.vert[0].y - m_stBulletAnimation.vert[1].y)) - cMap->GetPos().y))) < 25
					&& cMap->IsBlack()) {
					cMap->ChangeType();
					cMap->SetColor(RGB(255, 255, 255));
					GAMEMANAGER->IncreaseScore(KILL_POINT);
					
				}

				else if (sqrt(((m_stBulletAnimation.vert[1].x - cMap->GetPos().x)
					* (m_stBulletAnimation.vert[1].x - cMap->GetPos().x) +
					((m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - cMap->GetPos().y)
					* (
					(m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - cMap->GetPos().y))) < 25
					&& cMap->IsBlack()) {
					cMap->ChangeType();
					cMap->SetColor(RGB(255, 255, 255));
					GAMEMANAGER->IncreaseScore(KILL_POINT);
				}

			}
			else if (m_stBulletAnimation.a_eAttack == EAttack::DOWN_ATTACK) {
				if (sqrt(((m_stBulletAnimation.vert[1].x - cMap->GetPos().x)
					* (m_stBulletAnimation.vert[1].x - cMap->GetPos().x) +
					((m_stBulletAnimation.vert[0].y - (m_stBulletAnimation.vert[0].y - m_stBulletAnimation.vert[1].y)) - cMap->GetPos().y)
					* (
					(m_stBulletAnimation.vert[0].y - (m_stBulletAnimation.vert[0].y - m_stBulletAnimation.vert[1].y)) - cMap->GetPos().y))) < 28
					&& cMap->IsBlack()) {
					cMap->ChangeType();
					cMap->SetColor(RGB(255, 255, 255));
					GAMEMANAGER->IncreaseScore(KILL_POINT);
				}

				else if (sqrt(((m_stBulletAnimation.vert[1].x - cMap->GetPos().x)
					* (m_stBulletAnimation.vert[1].x - cMap->GetPos().x) +
					((m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - cMap->GetPos().y)
					* (
					(m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - cMap->GetPos().y))) < 28
					&& cMap->IsBlack()) {
					cMap->ChangeType();
					cMap->SetColor(RGB(255, 255, 255));
					GAMEMANAGER->IncreaseScore(KILL_POINT);

				}
			}
		}
	}

	for (auto d : GAMEMANAGER->GetNPCList()) {
		CEnemy* cEnemy = dynamic_cast<CEnemy*>(d);
		if (m_stBulletAnimation.a_eAttack == EAttack::LEFT_ATTACK || m_stBulletAnimation.a_eAttack == EAttack::RIGHT_ATTACK) {
				if (sqrt(((m_stBulletAnimation.vert[1].x - d->GetPos().x)
					* (m_stBulletAnimation.vert[1].x - d->GetPos().x) +
					((m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - d->GetPos().y)
					* (
					(m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - d->GetPos().y))) < 28
					) {
					cEnemy->DecreaseLife(); GAMEMANAGER->IncreaseScore(NPC_KILL_POINT); break;
				}
				else if (sqrt(((m_stBulletAnimation.vert[0].x - d->GetPos().x)
					* (m_stBulletAnimation.vert[0].x - d->GetPos().x) +
					((m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - d->GetPos().y)
					* (
					(m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - d->GetPos().y))) < 28
					) {
					cEnemy->DecreaseLife(); GAMEMANAGER->IncreaseScore(NPC_KILL_POINT); break;
				}
				
		}
		else if (m_stBulletAnimation.a_eAttack == EAttack::UP_ATTACK) {

			if (sqrt(((m_stBulletAnimation.vert[1].x - d->GetPos().x)
				* (m_stBulletAnimation.vert[1].x - d->GetPos().x) +
				((m_stBulletAnimation.vert[0].y - (m_stBulletAnimation.vert[0].y - m_stBulletAnimation.vert[1].y)) - d->GetPos().y)
				* (
				(m_stBulletAnimation.vert[0].y - (m_stBulletAnimation.vert[0].y - m_stBulletAnimation.vert[1].y)) - d->GetPos().y))) < 25
				) {
				cEnemy->DecreaseLife(); GAMEMANAGER->IncreaseScore(NPC_KILL_POINT); break;

			}

			else if (sqrt(((m_stBulletAnimation.vert[1].x - d->GetPos().x)
				* (m_stBulletAnimation.vert[1].x - d->GetPos().x) +
				((m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - d->GetPos().y)
				* (
				(m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - d->GetPos().y))) < 25
				) {
				cEnemy->DecreaseLife(); GAMEMANAGER->IncreaseScore(NPC_KILL_POINT); break;
			}

		}
		else if (m_stBulletAnimation.a_eAttack == EAttack::DOWN_ATTACK) {
			if (sqrt(((m_stBulletAnimation.vert[1].x - d->GetPos().x)
				* (m_stBulletAnimation.vert[1].x - d->GetPos().x) +
				((m_stBulletAnimation.vert[0].y - (m_stBulletAnimation.vert[0].y - m_stBulletAnimation.vert[1].y)) - d->GetPos().y)
				* (
				(m_stBulletAnimation.vert[0].y - (m_stBulletAnimation.vert[0].y - m_stBulletAnimation.vert[1].y)) - d->GetPos().y))) < 28
				) {
				cEnemy->DecreaseLife(); GAMEMANAGER->IncreaseScore(NPC_KILL_POINT); break;
			}

			else if (sqrt(((m_stBulletAnimation.vert[1].x - d->GetPos().x)
				* (m_stBulletAnimation.vert[1].x - d->GetPos().x) +
				((m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - d->GetPos().y)
				* (
				(m_stBulletAnimation.vert[1].y - (m_stBulletAnimation.vert[1].y - m_stBulletAnimation.vert[0].y)) - d->GetPos().y))) < 28
				) {
				cEnemy->DecreaseLife(); GAMEMANAGER->IncreaseScore(NPC_KILL_POINT); break;

			}
		}
	}
}

void CRotatingBullet::Draw()
{
	HDC hdc = GetDC(GAMEMANAGER->getHWND());

	HBRUSH hBrush = CreateSolidBrush(m_color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	HPEN hPen = CreatePen(BS_SOLID, 1, m_color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

	if(!m_stBulletAnimation.bShootAnimation)
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

void CRotatingBullet::OnBulletAnimation(const EAttack& a_eAttack)
{
	m_stBulletAnimation.bShootAnimation = true; 
	m_stBulletAnimation.a_eAttack = a_eAttack;

	if (a_eAttack == EAttack::LEFT_ATTACK || a_eAttack == EAttack::RIGHT_ATTACK) {
		m_stBulletAnimation.vert[0].x = m_rect.left;
		m_stBulletAnimation.vert[1].x = m_rect.left + 10;
		m_stBulletAnimation.vert[0].y = m_rect.top + 15;
		m_stBulletAnimation.vert[1].y = m_stBulletAnimation.vert[0].y + 10;
	}

	else if (a_eAttack == EAttack::UP_ATTACK || a_eAttack == EAttack::DOWN_ATTACK){
		m_stBulletAnimation.vert[0].x = m_rect.left + 25;
		m_stBulletAnimation.vert[1].x = m_rect.left + 15;
		m_stBulletAnimation.vert[0].y = m_rect.top + 15;
		m_stBulletAnimation.vert[1].y = m_stBulletAnimation.vert[0].y + 10;
	}

}

void CRotatingBullet::DrawBurstingBullet()
{
	HDC hdc = GetDC(GAMEMANAGER->getHWND());

	switch (m_stBulletAnimation.a_eAttack) {
	case EAttack::UP_ATTACK: 
		if (m_stBulletAnimation.vert[0].y > 0 && m_stBulletAnimation.bShootAnimation) {
			ChkCollision();
			// 그라데이션의 시작좌표를 명시한다.
			m_stBulletAnimation.vert[0].y -= BSIZE;
			// 그라데이션의 끝좌표를 명시한다.
			m_stBulletAnimation.vert[1].y = m_stBulletAnimation.vert[0].y - (OBJECT_SIZE * 2);

			if(m_stBulletAnimation.vert[1].y > 100)
			GradientFill(hdc, m_stBulletAnimation.vert, 2, &m_stBulletAnimation.rect, 1, GRADIENT_FILL_RECT_V);
		}

		else {
			m_stBulletAnimation.bShootAnimation = false;
			m_stBulletAnimation.bEndShootAnimation = true;
		}
		break;
	case EAttack::DOWN_ATTACK:
		if (m_stBulletAnimation.vert[1].y < WINDOWS_SIZE_Y && m_stBulletAnimation.bShootAnimation) {
			ChkCollision();
			// 그라데이션의 시작좌표를 명시한다.
			m_stBulletAnimation.vert[0].y += BSIZE;
			// 그라데이션의 끝좌표를 명시한다.
			m_stBulletAnimation.vert[1].y = m_stBulletAnimation.vert[0].y + (OBJECT_SIZE * 2);
			if (m_stBulletAnimation.vert[1].y < WINDOWS_SIZE_Y - 100)
			GradientFill(hdc, m_stBulletAnimation.vert, 2, &m_stBulletAnimation.rect, 1, GRADIENT_FILL_RECT_V);
		}

		else {
			m_stBulletAnimation.bShootAnimation = false;
			m_stBulletAnimation.bEndShootAnimation = true;
		}
		break;
	case EAttack::LEFT_ATTACK: 
		if (m_stBulletAnimation.vert[1].x > 0 &&  m_stBulletAnimation.bShootAnimation) {
			ChkCollision();
			// 그라데이션의 시작좌표를 명시한다.
			m_stBulletAnimation.vert[0].x -= BSIZE;
			// 그라데이션의 끝좌표를 명시한다.
			m_stBulletAnimation.vert[1].x = m_stBulletAnimation.vert[0].x - (OBJECT_SIZE * 2);
			if (m_stBulletAnimation.vert[1].x > 20)
			GradientFill(hdc, m_stBulletAnimation.vert, 2, &m_stBulletAnimation.rect, 1, GRADIENT_FILL_RECT_H);
		}

		else {
			m_stBulletAnimation.bShootAnimation = false;
			m_stBulletAnimation.bEndShootAnimation = true;
		}
		break;
	case EAttack::RIGHT_ATTACK:
		if (m_stBulletAnimation.vert[1].x < WINDOWS_SIZE_X &&  m_stBulletAnimation.bShootAnimation) {
			ChkCollision();
			// 그라데이션의 시작좌표를 명시한다.
			m_stBulletAnimation.vert[0].x += BSIZE;
			// 그라데이션의 끝좌표를 명시한다.
			m_stBulletAnimation.vert[1].x = m_stBulletAnimation.vert[0].x + (OBJECT_SIZE * 2);
			if (m_stBulletAnimation.vert[1].x < WINDOWS_SIZE_X - 20)
			GradientFill(hdc, m_stBulletAnimation.vert, 2, &m_stBulletAnimation.rect, 1, GRADIENT_FILL_RECT_H);
		}

		else {
			m_stBulletAnimation.bShootAnimation = false;
			m_stBulletAnimation.bEndShootAnimation = true;
		}
		break;
	default: break;
	}


	ReleaseDC(GAMEMANAGER->getHWND(), hdc);
}
const STBulletAnimation& CRotatingBullet::GetBulletAnimation() { return m_stBulletAnimation; }

CRotatingBullet::CRotatingBullet()
{

	m_flAngle = 0.0f;
	m_flRadian = 0.0f;

}