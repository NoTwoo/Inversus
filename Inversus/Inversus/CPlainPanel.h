#pragma once

#include "CPanel.h"

class CPlainPanel : public CPanel
{
public:
	bool GetDrawObject();
	void SetDrawObject(const bool& a_bDrawObject);

public:
	void SetObjectPos(const POINT& a_pos);
	const POINT& GetObjectPos();

public:
	void SetObjectRect(const RECT& a_rect);

public:
	void SetObjectPenInfo(const STTextInfo& a_stPenInfo);

public:
	void RotateBullet();

public:
	void DrawObject();

public:
	CPlainPanel();

private:
	bool m_bDrawObject;
	POINT m_ObjectPos;
	RECT m_ObjectRect;
	STTextInfo m_stObjectPenInfo;
	POINT m_CenterPos;
	STRotatingBullet m_stRotatingBullet[4];
	float m_flDR;
};