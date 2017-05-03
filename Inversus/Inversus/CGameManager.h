#pragma once

#include <list>
#include "CObject.h"

#define MAP_SIZE_X 19
#define MAP_SIZE_Y 13

#define MAX_STR 5

class CGameManager
{
public:
	static CGameManager* GetInstance()
	{
		if (m_Instance == nullptr) m_Instance = new CGameManager;
		return m_Instance;
	}

	void Init(HWND& a_hWnd, HINSTANCE& a_hInst)
	{
		m_hWnd = a_hWnd;
		m_hInst = a_hInst;

		m_hdc = GetDC(m_hWnd);

		GetClientRect(a_hWnd, &m_clntrt);
		
		ZeroMemory(&m_MousePos, sizeof(m_MousePos));
		m_bIsClicked = false;
		m_bIsHelpOn = false;

		m_str[0] = " W / S / A / D : MOVE";
		m_str[1] = " กๆ / ก็ / ก่ / ก้ : SHOOT";
		m_str[2] = " KEEP PUSHING ARROW KEY : CHARGING";
		m_str[3] = " P : PAUSE";
		m_str[4] = " ESC : EXIT";

		m_bIsInGame = false;
	}

	HWND getHWND() { return m_hWnd; }

	HINSTANCE GethInst() { return m_hInst; }
	void SetInst(HINSTANCE& a_hInst) { m_hInst = a_hInst; }

	RECT GetRect() { return m_clntrt; }
	void SetRect(RECT& a_rect) { m_clntrt = a_rect; }

	static bool Destroy()
	{
		if (m_Instance){ delete m_Instance; return true; }
		return false;
	}

	BYTE(*GetMap())[MAP_SIZE_X] { return m_bytMap; }
	
	UINT GetScore() { return m_uScore; }

	std::list<CObject*>& GetIntroList() { return m_IntroList; }

public:
	void SetMousePos(const POINT& a_pos) { m_MousePos = a_pos; }
	const POINT& GetMousePos() { return m_MousePos; }
	void ShowManual();
	void ClickProcess();
	const bool& IsHelpOn();
	void SetHelpOn();

public:
	const bool& IsInGame() { return m_bIsInGame; }
	void SetInGame(bool const& a_bool) { m_bIsInGame = a_bool; }
	void EnterInGameScene();
	std::list<CObject*>& GetGameList() { return m_GameList; }
	std::list<CObject*>& GetPlayerList() { return m_PlayerList; }
private:
	CGameManager() {};
	CGameManager(const CGameManager&) = delete;
	void operator=(const CGameManager&) = delete;

	static CGameManager* m_Instance;

private:
	BYTE m_bytMap[MAP_SIZE_Y][MAP_SIZE_X];
	UINT m_uScore;
	std::list<CObject*> m_IntroList;
	std::list<CObject*> m_GameList;
	std::list<CObject*> m_PlayerList;
private:
	HWND m_hWnd;
	HDC m_hdc;
	HINSTANCE m_hInst;
	RECT m_clntrt;

private:
	POINT m_MousePos;
	bool m_bIsClicked;
	bool m_bIsHelpOn;

private:
	std::string m_str[MAX_STR];

private:
	bool m_bIsInGame;
};

