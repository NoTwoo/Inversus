#pragma once
#include "CObject.h"

class CText : public CObject
{
public:
	virtual void Draw() override;

public:
	const std::string& GetString();
	void SetString(const std::string& a_str);
	const STTextInfo& GetPenInfo();
	void SetTextInfo(const STTextInfo& a_stTextInfo);

private:
	std::string m_str;
	STTextInfo m_stTextInfo;
};