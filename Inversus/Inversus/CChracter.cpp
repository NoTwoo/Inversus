#include "Define.h"

const UINT& CCharacter::GetLife() { return  m_uLife; }
void CCharacter::DecreaseLife() { m_uLife--; GAMEMANAGER->DeleteNPC(); }

bool CCharacter::ChkCollision(){ return false; }

void CCharacter::Explode()
{
	m_bDrawExplosion = true;

	for (CObject* d : GAMEMANAGER->GetGameList()) {
		if (dynamic_cast<CMap*>(d)) {
			CMap* cMap = dynamic_cast<CMap*>(d);

			if (sqrt(((m_pos.x - cMap->GetPos().x) * (m_pos.x - cMap->GetPos().x)) +
				((m_pos.y - cMap->GetPos().y) * ((m_pos.y - cMap->GetPos().y)))) < (CHARACTER_SIZE * 2)
				&& cMap->IsBlack()) {
				cMap->ChangeType();
				cMap->SetColor(RGB(255, 255, 255));
				GAMEMANAGER->IncreaseScore(KILL_POINT);
			}
		}
	}

	for (CObject* d : GAMEMANAGER->GetNPCList()) {
		if (dynamic_cast<CEnemy*>(d)) {
			CEnemy* cEnemy = dynamic_cast<CEnemy*>(d);

			if (sqrt(((m_pos.x - cEnemy->GetPos().x) * (m_pos.x - cEnemy->GetPos().x)) +
				((m_pos.y - cEnemy->GetPos().y) * ((m_pos.y - cEnemy->GetPos().y)))) < (CHARACTER_SIZE * 2)
				&& this != cEnemy && !cEnemy->GetExplosion()) {
				GAMEMANAGER->IncreaseScore(KILL_POINT);
				cEnemy->DecreaseLife();
			}
		}
	}
}

const bool& CCharacter::GetDelete() { return m_bDelete; }
const bool&  CCharacter::GetExplosion() { return m_bDrawExplosion; }

CCharacter::CCharacter() { m_uLife = 1; m_bDrawExplosion = false; m_bytBSIZE = BSIZE / 3; m_bDelete = false; }