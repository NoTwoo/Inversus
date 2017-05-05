#pragma once
#include "CObject.h"

class CBullet : public CObject
{

public:
	virtual void ChkCollision();

public:
	CBullet();

protected:
	POINT m_CenterPos;

};