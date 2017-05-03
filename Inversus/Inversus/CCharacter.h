#pragma once

#include "CObject.h"

enum EMove { UP, DOWN, LEFT, RIGHT };
enum EAttack { UP_ATTACK = 5, DOWN_ATTACK, LEFT_ATTACK, RIGHT_ATTACK};

class CCharacter : public CObject
{
public:
	virtual void Move() = 0;
	virtual void Attack() = 0;
public:
	const BYTE& GetLife();

public:
	virtual bool ChkCollision();

public:
	CCharacter();

protected:
	BYTE m_bytLife;
};