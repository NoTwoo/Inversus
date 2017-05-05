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

	for (CObject* d : m_IntroList) {
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
	for (CObject* d : m_IntroList) {
		if (dynamic_cast<CActivePanel*>(d)) {
			CActivePanel* ActivePanel = dynamic_cast<CActivePanel*>(d);
			if (ActivePanel->ChkClick()) {
				switch (ActivePanel->GetType()) {
				case EType::NEW_GAME: m_bIsInGame = true; EnterInGameScene(); InvalidateRect(m_hWnd, NULL, TRUE); break;
				case EType::HELP: ShowManual(); break;
				case EType::EXIT: PostQuitMessage(0); break;
				}
			}
		}
	}

}

void CGameManager::EnterInGameScene()
{
	RECT rect;

	CObject* pMainFrame = new CPlainPanel;
	pMainFrame->SetPos(POINT{ 0,70 });
	rect.left = pMainFrame->GetPos().x; rect.right = m_clntrt.right;
	rect.top = pMainFrame->GetPos().y; rect.bottom = m_clntrt.bottom;
	pMainFrame->SetRect(rect);
	pMainFrame->SetColor(COLORREF(RGB(166, 166, 166)));

	m_GameList.push_back(pMainFrame);

	CObject* pCharacter = new CPlayer;
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pCharacter);

	LONG uXSize{}, uYSize{ 50 };

	for (int i = 0; i < pPlayer->GetLife() -1; ++i) {
		CObject* pObject = new CPlainPanel;
		pObject->SetPos(POINT{ m_clntrt.right / 2 + uXSize , 35 });
		rect.left = pObject->GetPos().x; rect.right = rect.left + BSIZE;
		rect.top = pObject->GetPos().y; rect.bottom = rect.top + BSIZE;
		pObject->SetRect(rect);
		pObject->SetColor(COLORREF(RGB(0, 0, 0)));

		m_GameList.push_back(pObject);

		uXSize += BSIZE + 20;
	}

	CObject* pText = new CText;
	pText->SetPos(POINT{ BSIZE,0 });
	rect.left = pText->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = pText->GetPos().y; rect.bottom = rect.top + OBJECT_SIZE;
	pText->SetRect(rect);
	pText->SetColor(RGB(255, 255, 255));

	CText* pText2 = dynamic_cast<CText*>(pText);
	STTextInfo stTextInfo;
	stTextInfo.color = RGB(0, 0, 0);
	stTextInfo.width = SMALL_TEXT_WIDTH;
	pText2->SetTextInfo(stTextInfo);
	pText2->SetString("Score");

	m_GameList.push_back(pText);


	// Map
	LONG lSizeX{}, lSizeY{};

	int nLeftEnd = ((OBJECT_SIZE + INTERVAL) * 8);
	int nRightEnd = ((OBJECT_SIZE + INTERVAL) * 12);
	bool bTriangle = true;

	for (int y = 0; y < MAP_SIZE_Y; ++y) {
		for (int x = 0; x < MAP_SIZE_X; ++x) {
			CObject* pMap = new CMap;

			pMap->SetPos(POINT{ BSIZE + lSizeX, 90 + lSizeY });
			rect.left = pMap->GetPos().x; rect.right = rect.left + OBJECT_SIZE;
			rect.top = pMap->GetPos().y; rect.bottom = rect.top + OBJECT_SIZE;
			pMap->SetRect(rect);
			if (rect.left >= nLeftEnd && rect.left < nRightEnd - OBJECT_SIZE && y > INTERVAL && y < 10) {
				pMap->SetColor(COLORREF(RGB(255, 255, 255)));
				CMap* pTempMap = dynamic_cast<CMap*>(pMap);
				pTempMap->ChangeType();
			}
			else pMap->SetColor(COLORREF(RGB(0, 0, 0)));
			m_GameList.push_back(pMap);
			lSizeX += OBJECT_SIZE + INTERVAL;
		}

		if (bTriangle && y > INTERVAL) {
			nLeftEnd -= OBJECT_SIZE;
			nRightEnd += OBJECT_SIZE;
		}
		else if(!bTriangle){
			nLeftEnd += OBJECT_SIZE;
			nRightEnd -= OBJECT_SIZE;
		}

		if (lSizeY == (OBJECT_SIZE + INTERVAL) * 5) {
			nLeftEnd += OBJECT_SIZE;
			nRightEnd -= OBJECT_SIZE;
		}
		if (lSizeY == (OBJECT_SIZE + INTERVAL) * 6) {
			nLeftEnd += OBJECT_SIZE;
			nRightEnd -= OBJECT_SIZE;
			bTriangle = false;

		}
		lSizeX = 0;
		lSizeY += OBJECT_SIZE + INTERVAL;
	}

	// Player
	pCharacter->SetPos(POINT{ ((MAP_SIZE_X / INTERVAL) * (OBJECT_SIZE + INTERVAL)) + (BSIZE + 5), ((MAP_SIZE_Y / INTERVAL) * (OBJECT_SIZE + INTERVAL)) + (90 + 5) });
	rect.left = pCharacter->GetPos().x; rect.right = rect.left + CHARACTER_SIZE;
	rect.top = pCharacter->GetPos().y; rect.bottom = rect.top + CHARACTER_SIZE;
	pCharacter->SetRect(rect);
	pCharacter->SetColor(RGB(0, 0, 0));
	pPlayer->InitItem();
	m_PlayerList.push_back(pCharacter);


}