#include "Define.h"
#include "resource.h"

//#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

HINSTANCE g_hInst;
LPCTSTR lpszClass = "INVERSUS";

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	// 윈도우 클래스 구조체 값 설정
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	// 윈도우 클래스 등록
	RegisterClassEx(&WndClass);
	// 윈도우 생성
	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPED | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX, 0, 0, 1280, 800, NULL, (HMENU)NULL, hInstance, NULL);
	// 윈도우 출력
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	// 이벤트 루프 처리
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

void EnterIntroScene();

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 메시지 처리하기
	switch (uMsg) {
	case WM_CREATE:
		GAMEMANAGER->Init(hWnd, g_hInst);
		EnterIntroScene();
		SetTimer(hWnd, 1, 50, TimerProc);
		srand((unsigned)time(NULL));
		break;
	case WM_TIMER:
		switch (wParam) {
		case CREATE_NEW_NPC:
			GAMEMANAGER->CreateNewNPC();
			break;
		}
		break;
	case WM_MOUSEMOVE:
		GAMEMANAGER->SetMousePos(POINT{ LOWORD(lParam), HIWORD(lParam) });
		break;
	case WM_LBUTTONDOWN:
		if (!GAMEMANAGER->IsInGame()) {
			if (GAMEMANAGER->IsHelpOn()) { SetTimer(hWnd, 1, 50, TimerProc); GAMEMANAGER->SetHelpOn(); }
			GAMEMANAGER->SetMousePos(POINT{ LOWORD(lParam), HIWORD(lParam) });
			GAMEMANAGER->ClickProcess();
		}
		break;
	case WM_RBUTTONDOWN:
		if (GAMEMANAGER->IsInGame()) {
			GAMEMANAGER->SetMousePos(POINT{ LOWORD(lParam), HIWORD(lParam) });
			GAMEMANAGER->CheatProcess();
		}
		break;
	case WM_CHAR:
		switch (wParam) {
		case 'p':
		case 'P':
			if(!GAMEMANAGER->Pause()) SetTimer(hWnd, 1, 50, TimerProc);
			break;
		case 'r':
		case 'R':
			if (!GAMEMANAGER->GetPause()) {
				for (CObject* d : GAMEMANAGER->GetPlayerList()) {
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(d);
					pPlayer->ReloadBullet();
				}
			}
			break;
		case 'w':
		case 'W':
			if (!GAMEMANAGER->GetPause()) {
				for (CObject* d : GAMEMANAGER->GetPlayerList()) {
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(d);
					pPlayer->Move(EMove::UP);
				}
			}
			break;
		case 's':
		case 'S':
			if (!GAMEMANAGER->GetPause()) {
				for (CObject* d : GAMEMANAGER->GetPlayerList()) {
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(d);
					pPlayer->Move(EMove::DOWN);
				}
			}
			break;

		case 'a':
		case 'A':
			if (!GAMEMANAGER->GetPause()) {
				for (CObject* d : GAMEMANAGER->GetPlayerList()) {
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(d);
					pPlayer->Move(EMove::LEFT);
				}
			}
			break;
		case 'd':
		case 'D':
			if (!GAMEMANAGER->GetPause()) {
				for (CObject* d : GAMEMANAGER->GetPlayerList()) {
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(d);
					pPlayer->Move(EMove::RIGHT);
				}
			}
			break;
		default:
			if (GAMEMANAGER->IsHelpOn()) { SetTimer(hWnd, 1, 150, TimerProc); GAMEMANAGER->SetHelpOn(); }
		}
		break;
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE: PostQuitMessage(0); break;
		case VK_UP:
			if (!GAMEMANAGER->GetPause()) {
				for (CObject* d : GAMEMANAGER->GetPlayerList()) {
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(d);
					pPlayer->Attack(EAttack::UP_ATTACK);
				}
			}
			break;
		case VK_DOWN:
			if (!GAMEMANAGER->GetPause()) {
				for (CObject* d : GAMEMANAGER->GetPlayerList()) {
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(d);
					pPlayer->Attack(EAttack::DOWN_ATTACK);
				}
			}
			break;
		case VK_LEFT:
			if (!GAMEMANAGER->GetPause()) {
				for (CObject* d : GAMEMANAGER->GetPlayerList()) {
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(d);
					pPlayer->Attack(EAttack::LEFT_ATTACK);
				}
			}
			break;
		case VK_RIGHT: 
			if (!GAMEMANAGER->GetPause()) {
				for (CObject* d : GAMEMANAGER->GetPlayerList()) {
					CPlayer* pPlayer = dynamic_cast<CPlayer*>(d);
					pPlayer->Attack(EAttack::RIGHT_ATTACK);
				}
			}
			break;
		}
		break;
	case WM_GETMINMAXINFO: {
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WINDOWS_SIZE_X;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WINDOWS_SIZE_Y;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WINDOWS_SIZE_X;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WINDOWS_SIZE_Y;
		return FALSE;
	}
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); // 위의 세 메시지 외의 나머지 메시지는 OS로
}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{

	if (!GAMEMANAGER->IsInGame()) {

		for (CObject* d : GAMEMANAGER->GetIntroList()) {
			if (dynamic_cast<CPanel*>(d)) {
				CPanel* tempPanel = dynamic_cast<CPanel*>(d);
				tempPanel->DrawWithText();
			}

			if (dynamic_cast<CPlainPanel*>(d)) {
				CPlainPanel* PlainPanel = dynamic_cast<CPlainPanel*>(d);
				if (PlainPanel->GetDrawObject()) PlainPanel->DrawObject();
			}

			if (dynamic_cast<CActivePanel*>(d)) {
				CActivePanel* ActivePanel = dynamic_cast<CActivePanel*>(d);
				ActivePanel->ShowAnimation();
			}
		}
	}

	else {
		
		for (CObject* d : GAMEMANAGER->GetGameList()) d->Draw();
		for (CObject* d : GAMEMANAGER->GetNPCList()) d->Draw();
		for (CObject* d : GAMEMANAGER->GetPlayerList()) d->Draw();
		GAMEMANAGER->DeleteNPC();
		GAMEMANAGER->DeleteItem();
		GAMEMANAGER->SetNewNPCTime();
		
	}

}

void EnterIntroScene()
{
	RECT rect;
	LONG uY{500};
	STTextInfo stTextInfo;

	// Start of PlainPanel

	CObject* cTitle  = new CPlainPanel;
	cTitle->SetPos(POINT{ 0,200 });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 250;
	cTitle->SetRect(rect);
	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	CPlainPanel* pPTitle = dynamic_cast<CPlainPanel*>(cTitle);

	// Set of Object to draw
	pPTitle->SetDrawObject(true);
	pPTitle->SetObjectPos(POINT{ 800,315 });
	rect.left = pPTitle->GetObjectPos().x; rect.right = rect.left + 100;
	rect.top = pPTitle->GetObjectPos().y; rect.bottom = rect.top + 100;
	pPTitle->SetObjectRect(rect);
	stTextInfo.color = RGB(255, 255, 255);
	stTextInfo.width = 2;
	pPTitle->SetObjectPenInfo(stTextInfo);

	// Set of String
	pPTitle->SetString("I N V E R S U S");
	stTextInfo.color = RGB(255, 255, 255);
	stTextInfo.width = TITLE_WIDTH;
	pPTitle->SetTextInfo(stTextInfo);
	GAMEMANAGER->GetIntroList().push_back(cTitle);
	
	CObject* cTitleFirstLine = new CPlainPanel;
	cTitleFirstLine->SetPos(POINT{ 0, 400 });
	rect.left = cTitleFirstLine->GetPos().x; rect.right = 799;
	rect.top = cTitleFirstLine->GetPos().y; rect.bottom = rect.top + 4;
	cTitleFirstLine->SetRect(rect);
	cTitleFirstLine->SetColor(COLORREF(RGB(255, 255, 255)));
	GAMEMANAGER->GetIntroList().push_back(cTitleFirstLine);

	CObject* cTitleSecondLine = new CPlainPanel;
	cTitleSecondLine->SetPos(POINT{ 0, 411 });
	rect.left = cTitleSecondLine->GetPos().x; rect.right = 896;
	rect.top = cTitleSecondLine->GetPos().y; rect.bottom = rect.top + 4;
	cTitleSecondLine->SetRect(rect);
	cTitleSecondLine->SetColor(COLORREF(RGB(255, 255, 255)));
	GAMEMANAGER->GetIntroList().push_back(cTitleSecondLine);

	// End of PlainPanel

	cTitle = new CActivePanel;
	cTitle->SetPos(POINT{ 0, uY });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 50;
	cTitle->SetRect(rect);

	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	CActivePanel* pATitle = dynamic_cast<CActivePanel*>(cTitle);
	pATitle->SetString("N E W  G A M E");
	stTextInfo.color = RGB(255, 255, 255);
	stTextInfo.width = SMALL_TEXT_WIDTH;
	pATitle->SetTextInfo(stTextInfo);
	pATitle->SetType(EType::NEW_GAME);
	GAMEMANAGER->GetIntroList().push_back(cTitle);
	uY += 70;
	
	cTitle = new CActivePanel;
	cTitle->SetPos(POINT{ 0, uY });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 50;
	cTitle->SetRect(rect);
	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	pATitle = dynamic_cast<CActivePanel*>(cTitle);
	pATitle->SetString("H E L P");
	pATitle->SetTextInfo(stTextInfo);
	pATitle->SetType(EType::HELP);
	GAMEMANAGER->GetIntroList().push_back(cTitle);
	uY += 70;

	cTitle = new CActivePanel;
	cTitle->SetPos(POINT{ 0, uY });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 50;
	cTitle->SetRect(rect);
	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	pATitle = dynamic_cast<CActivePanel*>(cTitle);
	pATitle->SetString("E X I T");
	pATitle->SetTextInfo(stTextInfo);
	pATitle->SetType(EType::EXIT);
	GAMEMANAGER->GetIntroList().push_back(cTitle);

}

