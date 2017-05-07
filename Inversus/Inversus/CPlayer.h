#pragma once

#include<vector>
#include "CCharacter.h"

class CPlayer : public CCharacter
{
public:
	virtual void Draw() override;

public:
	void Move(const EMove& a_eMove);
	virtual void Move() override {};
	void RePositionBullet();

public:
	virtual void Attack() override {};
	void Attack(const EAttack& a_eAttack);
	void Shoot(const EAttack& a_eAttack);
	void ReloadBullet();
public:
	bool ChkCollision(const EMove& a_eMove);
	bool ChkCollision();

public:
	void Init();
	void InitItem();

public:
	CPlayer();

private:
	std::vector<CObject*> m_vItemList;
	TRIVERTEX m_vert[2];
	GRADIENT_RECT m_grect;
	bool m_bShootAnimation;
};