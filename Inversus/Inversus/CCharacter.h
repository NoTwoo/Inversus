#pragma once

#include "CObject.h"

enum EMove { UP, DOWN, LEFT, RIGHT };

class CCharacter : public CObject
{
public:
	virtual void Move() = 0;

public:
	const BYTE& GetLife();

public:
	void ChkCollision();

public:
	CCharacter();

protected:
	BYTE m_bytLife;
};