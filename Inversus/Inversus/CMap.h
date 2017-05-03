#pragma once

#include "CObject.h"

class CMap : public CObject
{
public:
	virtual void Draw() override;

public:
	void ChangeType();
	bool IsBlack();

public:
	CMap();

private:
	bool m_bIsBlack;

};