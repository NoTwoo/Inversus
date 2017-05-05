#pragma once
#include "CBullet.h"

struct STBulletAnimation
{
	TRIVERTEX vert[2];
	GRADIENT_RECT rect;
	bool bShootAnimation;
	bool bEndShootAnimation;
	EAttack a_eAttack;
	STBulletAnimation()
	{
		// 그라데이션의 시작좌표를 명시한다.
		vert[0].x = 0;
		vert[0].y = 0;

		// 그라데이션의 시작색상을 명시한다.
		vert[0].Red = 0xFFFF;
		vert[0].Green = 0xFFFF;
		vert[0].Blue = 0xFFFF;
		vert[0].Alpha = 0xFFFF;

		// 그라데이션의 끝좌표를 명시한다.
		vert[1].x = 0;
		vert[1].y = 0;

		// 그라데이션의 끝색상를 명시한다.
		vert[1].Red = 0x0000;
		vert[1].Green = 0x0000;
		vert[1].Blue = 0x0000;
		vert[1].Alpha = 0x0000;

		rect.UpperLeft = 0;
		rect.LowerRight = 1;

		bShootAnimation = false;
		bEndShootAnimation = false;
		a_eAttack = EAttack::RIGHT_ATTACK;
	}

};

class CRotatingBullet : public CBullet
{

public:
	void SetAngle(const float& a_flAngle);
	const float& GetAngle();
	void SetCenter();

public:
	virtual void ChkCollision();

public:
	virtual void Draw() override;
	void RotateBullet();
	void OnBulletAnimation(const EAttack& a_eAttack);
	void DrawBurstingBullet();
	const STBulletAnimation& GetBulletAnimation();

public:
	CRotatingBullet();

private:
	float m_flAngle;
	float m_flRadian;
	STBulletAnimation m_stBulletAnimation;
};