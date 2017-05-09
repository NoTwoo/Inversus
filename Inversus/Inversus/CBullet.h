#pragma once
#include "CObject.h"

class CBullet : public CObject
{

public:
	virtual void ChkCollision();

public:
	virtual void Draw();

public:
	void DeleteMe();
	const bool& GetDelete();

public:
	CBullet();

protected:
	POINT m_CenterPos;
	bool m_bDeleteMe;
};