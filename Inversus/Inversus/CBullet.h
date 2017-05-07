#pragma once
#include "CObject.h"

class CBullet : public CObject
{

public:
	virtual void ChkCollision();

public:
	virtual void Draw();

public:
	CBullet();

protected:
	POINT m_CenterPos;

};