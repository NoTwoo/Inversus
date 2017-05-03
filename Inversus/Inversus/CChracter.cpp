#include "Define.h"

const BYTE& CCharacter::GetLife() { return m_bytLife; }

bool CCharacter::ChkCollision(){ return false; }



CCharacter::CCharacter()
{

	BYTE m_bytLife = 1;

}