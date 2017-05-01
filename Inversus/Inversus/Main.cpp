#include "Define.h"

#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")

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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// 윈도우 클래스 등록
	RegisterClassEx(&WndClass);
	// 윈도우 생성
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 1280, 800, NULL, (HMENU)NULL, hInstance, NULL);
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
void EnterInGameScene();

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// 메시지 처리하기
	switch (uMsg) {
	case WM_CREATE:
		GAMEMANAGER->Init(hWnd, g_hInst);
		EnterIntroScene();
		SetTimer(hWnd, 1, 150, TimerProc);
		
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

	for (CObject* d : GAMEMANAGER->GetList()){
		if (dynamic_cast<CPanel*>(d)) {
			CPanel* tempPanel = dynamic_cast<CPanel*>(d);
			tempPanel->Draw();
		}
		
		if (dynamic_cast<CPlainPanel*>(d)) {
			CPlainPanel* PlainPanel = dynamic_cast<CPlainPanel*>(d);
			if (PlainPanel->GetDrawObject()) PlainPanel->DrawObject();
			
		}

	}
	
}

void EnterIntroScene()
{
	RECT rect;
	LONG uY{500};
	STPenInfo stPenInfo;

	// Start of PlainPanel

	CObject* cTitle = new CPlainPanel;
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
	stPenInfo.color = RGB(255, 255, 255);
	stPenInfo.width = 2;
	pPTitle->SetObjectPenInfo(stPenInfo);

	// Set of String
	pPTitle->SetString("I N V E R S U S");
	stPenInfo.color = RGB(255, 255, 255);
	stPenInfo.width = TITLE_WIDTH;
	pPTitle->SetPenInfo(stPenInfo);
	GAMEMANAGER->GetList().push_back(cTitle);
	
	CObject* cTitleFirstLine = new CPlainPanel;
	cTitleFirstLine->SetPos(POINT{ 0, 400 });
	rect.left = cTitleFirstLine->GetPos().x; rect.right = 799;
	rect.top = cTitleFirstLine->GetPos().y; rect.bottom = rect.top + 4;
	cTitleFirstLine->SetRect(rect);
	cTitleFirstLine->SetColor(COLORREF(RGB(255, 255, 255)));
	GAMEMANAGER->GetList().push_back(cTitleFirstLine);

	CObject* cTitleSecondLine = new CPlainPanel;
	cTitleSecondLine->SetPos(POINT{ 0, 411 });
	rect.left = cTitleSecondLine->GetPos().x; rect.right = 896;
	rect.top = cTitleSecondLine->GetPos().y; rect.bottom = rect.top + 4;
	cTitleSecondLine->SetRect(rect);
	cTitleSecondLine->SetColor(COLORREF(RGB(255, 255, 255)));
	GAMEMANAGER->GetList().push_back(cTitleSecondLine);

	// End of PlainPanel

	cTitle = new CActivePanel;
	cTitle->SetPos(POINT{ 0, uY });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 50;
	cTitle->SetRect(rect);
	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	CActivePanel* pATitle = dynamic_cast<CActivePanel*>(cTitle);
	pATitle->SetString("N E W  G A M E");
	stPenInfo.color = RGB(255, 255, 255);
	stPenInfo.width = SMALL_TEXT_WIDTH;
	pATitle->SetPenInfo(stPenInfo);
	GAMEMANAGER->GetList().push_back(cTitle);
	uY += 70;
	
	cTitle = new CActivePanel;
	cTitle->SetPos(POINT{ 0, uY });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 50;
	cTitle->SetRect(rect);
	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	pATitle = dynamic_cast<CActivePanel*>(cTitle);
	pATitle->SetString("H E L P");
	pATitle->SetPenInfo(stPenInfo);
	GAMEMANAGER->GetList().push_back(cTitle);
	uY += 70;

	cTitle = new CActivePanel;
	cTitle->SetPos(POINT{ 0, uY });
	rect.left = cTitle->GetPos().x; rect.right = GAMEMANAGER->GetRect().right;
	rect.top = cTitle->GetPos().y; rect.bottom = rect.top + 50;
	cTitle->SetRect(rect);
	cTitle->SetColor(COLORREF(RGB(0, 0, 0)));
	pATitle = dynamic_cast<CActivePanel*>(cTitle);
	pATitle->SetString("E X I T");
	pATitle->SetPenInfo(stPenInfo);
	GAMEMANAGER->GetList().push_back(cTitle);

}

void EnterInGameScene()
{

}