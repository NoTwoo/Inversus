#pragma once
#include "CBullet.h"

class CRotatingBullet : public CBullet
{

public:
	void SetAngle(const float& a_flAngle);
	void SetCenter();

public:
	virtual void Draw() override;
	void RotateBullet();

public:
	CRotatingBullet();

private:
	float m_flAngle;
	float m_flRadian;

};