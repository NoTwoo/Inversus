#include "Define.h"

const UINT& CCharacter::GetLife() { return  m_uLife; }
void CCharacter::DecreaseLife() { m_uLife--; GAMEMANAGER->DeleteNPC(); }

bool CCharacter::ChkCollision(){ return false; }



CCharacter::CCharacter(){ m_uLife = 1; }