#pragma once

#include "CCharacter.h"

class CEnemy : public CCharacter
{
public:
	virtual void Draw();
	virtual void Attack() {};
public:
	virtual void Move();
};