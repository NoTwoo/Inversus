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
	const UINT& GetLife();
	void DecreaseLife();

public:
	virtual bool ChkCollision();

public:
	void Explode();
	const bool& GetDelete();
	const bool& GetExplosion();

public:
	CCharacter();
	virtual ~CCharacter() {};

protected:
	UINT  m_uLife;
	bool m_bDelete;

protected:
	bool m_bDrawExplosion;
	BYTE m_bytBSIZE;
};