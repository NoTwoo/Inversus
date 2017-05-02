#pragma once

#include <Windows.h>
#include <string>

enum EItemType { Nothing, PlainBullet, SpecialBullet };

struct STItem
{
	EItemType eItemType;
	bool bIsAvailable;
	COLORREF color;

	STItem()
	{
		eItemType = Nothing;
		bIsAvailable = false;
		color = RGB(255, 255, 255);
	};

};

class CObject
{
public:
	CObject();
	virtual ~CObject() {};

	const COLORREF& GetColor();
	void SetColor(const COLORREF& a_color);

	POINT GetPos();
	void SetPos(POINT a_pos);

	const RECT& GetRect();
	void SetRect(const RECT& a_rect);

public:
	virtual void Draw() {};
protected:
	POINT m_pos;
	RECT m_rect;
	COLORREF m_color;
};
