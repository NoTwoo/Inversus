#pragma once

#include<vector>

#include "CCharacter.h"

class CPlayer : public CCharacter
{
public:
	void Move(const EMove& a_eMove);
	virtual void Move() override {};
public:
	CPlayer();

private:
	std::vector<STItem> m_vItemList;
	
};