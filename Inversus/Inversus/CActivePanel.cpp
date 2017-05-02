#include "Define.h"

void CActivePanel::ShowAnimation()
{
	if (GAMEMANAGER->GetMousePos().x >= m_rect.left && GAMEMANAGER->GetMousePos().x <= m_rect.right &&
		GAMEMANAGER->GetMousePos().y >= m_rect.top && GAMEMANAGER->GetMousePos().y <= m_rect.bottom) 
		m_color = RGB(76, 76, 76);

	else m_color = RGB(0, 0, 0);

}

void CActivePanel::SetType(const EType& a_type) { m_eType = a_type; }

const bool& CActivePanel::ChkClick()
{
	if (GAMEMANAGER->GetMousePos().x >= m_rect.left && GAMEMANAGER->GetMousePos().x <= m_rect.right &&
		GAMEMANAGER->GetMousePos().y >= m_rect.top && GAMEMANAGER->GetMousePos().y <= m_rect.bottom)
		return true;
	else return false;
}

const EType& CActivePanel::GetType() { return m_eType; }

CActivePanel::CActivePanel() { m_eType = EType::NOTHING; }