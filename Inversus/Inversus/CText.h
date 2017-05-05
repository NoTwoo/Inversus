#pragma once
#include "CObject.h"

class CText : public CObject
{
public:
	virtual void Draw() override;

public:
	const std::string& GetString();
	void SetString(const std::string& a_str);
	void SetString(const CString& a_cstr);
	const STTextInfo& GetPenInfo();
	void SetTextInfo(const STTextInfo& a_stTextInfo);

private:
	std::string m_str;
	CString m_cstr;
	STTextInfo m_stTextInfo;
};