#pragma once

#include "CCharacter.h"
#include "CMap.h"

class CEnemy : public CCharacter
{
public:
	virtual void Draw();
	virtual void Attack() {};
	const bool& IsClose(const CMap* cMap) const;

public:
	virtual void Move();

};