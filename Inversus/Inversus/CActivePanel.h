#pragma once

#include "CPanel.h"

enum EType { NOTHING, NEW_GAME, HELP, EXIT };
class CActivePanel : public CPanel
{
public:
	void ShowAnimation();
	void SetType(const EType& a_type);

public:
	const bool& ChkClick();
	const EType& GetType();

public:
	CActivePanel();

private:
	EType m_eType;
};