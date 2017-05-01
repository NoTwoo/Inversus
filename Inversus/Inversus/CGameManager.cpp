#include "CGameManager.h"
#include "Define.h"

CGameManager* CGameManager::m_Instance = NULL;

void CGameManager::ShowManual()
{
	KillTimer(m_hWnd, 1);
	m_bIsHelpOn = true;

	HBRUSH hBrush, hOldBrush;
	HPEN hPen, hOldPen;
	HFONT hFont, hOldFont;

	hBrush = CreateHatchBrush(HS_CROSS,RGB(178, 235, 244));
	hOldBrush = (HBRUSH)SelectObject(m_hdc, hBrush);

	hPen = CreatePen(BS_SOLID, 1, RGB(255,255,255));
	hOldPen = (HPEN)SelectObject(m_hdc, hPen);

	for (CObject* d : m_List) {
		if (dynamic_cast<CPlainPanel*>(d)) {
			CPlainPanel* PlainPanel = dynamic_cast<CPlainPanel*>(d);
			Rectangle(m_hdc, PlainPanel->GetRect().left, PlainPanel->GetRect().top, PlainPanel->GetRect().right, PlainPanel->GetRect().bottom);
			break;
		}
	}

	hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("±Ã¼­"));

	hOldFont = (HFONT)SelectObject(m_hdc, hFont);
	SetBkMode(m_hdc, TRANSPARENT);

	int y = 210;
	for (int i = 0; i < MAX_STR; ++i) {
		TextOut(m_hdc, 300, y, m_str[i].c_str(), m_str[i].length());
		y += 50;
	}

	SetBkMode(m_hdc, OPAQUE);

	SelectObject(m_hdc, hOldBrush);
	SelectObject(m_hdc, hOldPen);
	SelectObject(m_hdc, hOldFont);

	DeleteObject(hBrush);
	DeleteObject(hPen);
	DeleteObject(hFont);

}

const bool& CGameManager::IsHelpOn() { return m_bIsHelpOn; }
void CGameManager::SetHelpOn() { m_bIsHelpOn = false; }

void CGameManager::ClickProcess()
{
	for (CObject* d : m_List) {
		if (dynamic_cast<CActivePanel*>(d)) {
			CActivePanel* ActivePanel = dynamic_cast<CActivePanel*>(d);
			if (ActivePanel->ChkClick()) {
				switch (ActivePanel->GetType()) {
				case EType::NEW_GAME: break;
				case EType::HELP: ShowManual(); break;
				case EType::EXIT: PostQuitMessage(0); break;
				}
			}
		}
	}

}