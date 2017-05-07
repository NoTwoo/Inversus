#pragma once

#include <Windows.h>
#include <string>
#include <atlstr.h>
enum EItemType { Nothing, PlainBullet, SpecialBullet };

struct STTextInfo
{
	COLORREF color;
	BYTE width;

	STTextInfo()
	{
		ZeroMemory(&color, sizeof(color));
		width = 0;
	}
};


struct STRotatingBullet
{
	COLORREF color;
	POINT pos;
	float angle;
	float r;
	STRotatingBullet()
	{
		ZeroMemory(&color, sizeof(color));
		ZeroMemory(&pos, sizeof(pos));
		angle = 0.0f;
		r = 0.0f;
	}
};

class CObject
{
public:
	CObject();
	virtual ~CObject() {};

	const COLORREF& GetColor();
	void SetColor(const COLORREF& a_color);

	POINT GetPos() const;
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
