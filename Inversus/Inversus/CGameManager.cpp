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
	for (int i = 0; i < MAX_STR - 2; ++i) {
		TextOut(m_hdc, 300, y, m_str[i].c_str(), m_str[i].length());
		y += 50;
	}

	TextOut(m_hdc, 0, 50, m_str[MAX_STR - 2].c_str(), m_str[MAX_STR - 2].length());
	TextOut(m_hdc, 300, 100, m_str[MAX_STR - 1].c_str(), m_str[MAX_STR - 1].length());
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
				case EType::NEW_GAME:
				if(m_PlayerList.size() != 0) m_PlayerList.clear(); 
				m_NPC_CREATE_TIME = CREATE_NEW_NPC_TIME;
				m_bIsInGame = true; EnterInGameScene(); InvalidateRect(m_hWnd, NULL, TRUE); break;
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

		CPlainPanel* pPanel = dynamic_cast<CPlainPanel*>(pObject);
		pPanel->SetLife();
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
	std::string str = "Score";
	pText2->SetString(str);

	m_GameList.push_back(pText);

	// Score Point
	pText = new CText;
	pText->SetPos(POINT{ BSIZE + BSIZE / 2, BSIZE});
	rect.left = pText->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = pText->GetPos().y; rect.bottom = rect.top + OBJECT_SIZE;
	pText->SetRect(rect);
	pText->SetColor(RGB(255, 255, 255));

	pText2 = dynamic_cast<CText*>(pText);
	stTextInfo.color = RGB(92, 209, 229);
	stTextInfo.width = SMALL_TEXT_WIDTH;
	pText2->SetTextInfo(stTextInfo);
	CString cstr;
	cstr.Format("%d", GAMEMANAGER->GetScore());
	pText2->SetString(cstr);

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
	pPlayer->Init();
	m_PlayerList.push_back(pCharacter);

	SetTimer(m_hWnd, CREATE_NEW_NPC, m_NPC_CREATE_TIME, NULL);
}

void  CGameManager::IncreaseScore(const UINT& a_uScore)
{
	m_uScore += a_uScore; 

	for (CObject* d : GAMEMANAGER->GetGameList()) {
		if (dynamic_cast<CText*>(d)) {
			CText* cText = dynamic_cast<CText*>(d);
			if (cText->GetString().size() == 0) {
				CString cstr;
				cstr.Format("%d", GAMEMANAGER->GetScore());
				cText->SetString(cstr);
			}
		}
	}
}

void CGameManager::CreateNewNPC()
{
	CObject* cEnemy = new CEnemy;
	cEnemy->SetPos(POINT{ rand() % (WINDOWS_SIZE_X - 100) + 100, rand() % (WINDOWS_SIZE_Y - 100) + 100});
	RECT rect;
	rect.left = cEnemy->GetPos().x; rect.right = rect.left + CHARACTER_SIZE;
	rect.top = cEnemy->GetPos().y; rect.bottom = rect.top + CHARACTER_SIZE;
	cEnemy->SetRect(rect);
	cEnemy->SetColor(RGB(rand() % 255, rand() % 255, rand() % 255));
	m_NPCList.push_back(cEnemy);

}

void CGameManager::DecreaseLife()
{
	if (m_GameList.size() > 0) {
		for (list<CObject*>::iterator itor = m_GameList.begin(); itor != m_GameList.end();) {
			if (dynamic_cast<CPlainPanel*>(*itor)) {
				CPlainPanel* cPanel = dynamic_cast<CPlainPanel*>(*itor);
				if (cPanel->IsLife()) { 
					for (auto d : m_PlayerList) {
						CCharacter* cCha = dynamic_cast<CCharacter*>(d);
						cCha->Explode();
					}
					itor = m_GameList.erase(itor); InvalidateRect(m_hWnd, NULL, TRUE); break;
				}
				else ++itor;
			}
			else ++itor;

		}

	}
}

void CGameManager::DeleteNPC()
{
	if (m_NPCList.size() > 0) {
		for (list<CObject*>::iterator itor = m_NPCList.begin(); itor != m_NPCList.end(); ++itor) {
			if (dynamic_cast<CEnemy*>(*itor)) {
				CEnemy* cEnemy = dynamic_cast<CEnemy*>(*itor);
				if (cEnemy->GetLife() != 1 && !cEnemy->GetDelete() && !cEnemy->GetExplosion()) { cEnemy->Explode(); }
				
			}

		}

	}

	if (m_NPCList.size() > 0) {
		for (list<CObject*>::iterator itor = m_NPCList.begin(); itor != m_NPCList.end();) {
			if (dynamic_cast<CEnemy*>(*itor)) {
				CEnemy* cEnemy = dynamic_cast<CEnemy*>(*itor);
				if (cEnemy->GetDelete()) {
					if (rand() % 2) {
						CObject* pBullet = new CBullet;
						pBullet->SetColor(cEnemy->GetColor());
						pBullet->SetPos(cEnemy->GetPos());
						pBullet->SetRect(cEnemy->GetRect());
						m_GameList.push_back(pBullet);
					}
					itor = m_NPCList.erase(itor); 
				}
				else  ++itor;

			}

		}

	}
}

void  CGameManager::SetInGame(bool const& a_bool)
{
	m_bIsInGame = a_bool;
	if (!m_bIsInGame) {
		KillTimer(m_hWnd, CREATE_NEW_NPC);
		m_GameList.clear();
		m_NPCList.clear();
		m_uScore = 0;
		InvalidateRect(m_hWnd, NULL, TRUE);

	}
}

void  CGameManager::SetNewNPCTime()
{
	if ((m_uScore % TIME_POINT) == 0 &&  m_uScore > 0 && m_NPC_CREATE_TIME >= TIME_DECREASE * 2) {

		KillTimer(m_hWnd, CREATE_NEW_NPC);
		m_NPC_CREATE_TIME -= TIME_DECREASE;
		SetTimer(m_hWnd, CREATE_NEW_NPC, m_NPC_CREATE_TIME, NULL);
	}

}

void CGameManager::DeleteItem()
{

	if (m_GameList.size() > 0) {
		for (list<CObject*>::iterator itor = m_GameList.begin(); itor != m_GameList.end();) {
			if (dynamic_cast<CBullet*>(*itor)) {
				CBullet* cBullet = dynamic_cast<CBullet*>(*itor);
				if (cBullet->GetDelete()){
					itor = m_GameList.erase(itor); break; 
				}
				else ++itor;

			}

			else ++itor;

		}

	}
}

const bool& CGameManager::Pause()
{
	m_bPause = !m_bPause;

	if (m_bPause) {
		KillTimer(m_hWnd, 1);
		KillTimer(m_hWnd, CREATE_NEW_NPC);
		return m_bPause;
	}

	SetTimer(m_hWnd, CREATE_NEW_NPC, m_NPC_CREATE_TIME, NULL);
	return m_bPause;
}


const bool& CGameManager::GetPause() { return m_bPause; }

void CGameManager::CheatProcess()
{
	if (m_MousePos.x >= 70 && m_MousePos.x <= 80 && m_MousePos.y >= 20 && m_MousePos.y <= 30) m_bIsInvincible = true;
}

const bool& CGameManager::GetInvincibility() { return  m_bIsInvincible; }