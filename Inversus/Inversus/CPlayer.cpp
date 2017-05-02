#include "Define.h"

void CPlayer::Move(const EMove& a_eMove)
{
	switch (a_eMove) {
	case EMove::UP: break;
	case EMove::DOWN: break;
	case EMove::LEFT: break;
	case EMove::RIGHT: break;
	}
}

CPlayer::CPlayer()
{
	m_bytLife = 3;

}