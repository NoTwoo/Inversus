#pragma once

#include "CObject.h"

class CPanel : public CObject
{

public:
	void DrawWithText();
	virtual void Draw() override;

	const std::string& GetString();
	void SetString(const std::string& a_str);

	const STTextInfo& GetPenInfo();
	void SetTextInfo(const STTextInfo& a_stTextInfo);
private:
	std::string m_str;
	STTextInfo m_stTextInfo;
};