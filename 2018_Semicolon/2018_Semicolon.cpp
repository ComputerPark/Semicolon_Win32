// 2018_Semicolon.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
// The Hell Begins

#include "stdafx.h"
#include "2018_Semicolon.h"


#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif

// 전역 변수:
HINSTANCE hInst;                     // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];       // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.
HWND g_hWnd;
Jet Player;
Jet Enemy[MAX_ENEMY];
Bullet PBullet[MAXBULLET];
bool canFire;
double speed = 0;
HWND hWndConsole;
unsigned long long int score = 0;
Bullet EBullet[MAXEBULLET];
bool enemysprite = false;
int tmpx[100], tmpy[100];
int tmprnd1[100], tmprnd2[100], tmprnd3[100];
HANDLE hThread_BG;
HCURSOR hCursor;
bool levelclearhack = false;
bool gamestarted = false;
bool active_tmp_1 = false;
bool initparam = false;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                           _In_opt_                           HINSTANCE hPrevInstance,
                           _In_                           LPWSTR lpCmdLine,
                           _In_                           int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY2018SEMICOLON, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow)) {
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2018SEMICOLON));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0)) {
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

//2018 = 이런 씨..

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2018SEMICOLON));
	wcex.hCursor = nullptr;
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY2018SEMICOLON);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


	if (!hWnd) {
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


//배경 난수 콜백
LRESULT CALLBACK BGTimerProc_RND(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime) {

	for (int i = 0; i < 100; i++) {
		tmpx[i] = rand() % WIN_X_SIZE;
		tmpy[i] = rand() % WIN_Y_SIZE;

		tmprnd1[i] = rand() % 256;
		tmprnd2[i] = rand() % 256;
		tmprnd3[i] = rand() % 256;
	}


	//Sleep(300);
	/*밑에 안돌아감*/
	//TODO: 밑에 수정
	for (int i = 0; i < 100; i++) {
		tmpy[i] += 10;
		if (tmpy[i] > WIN_Y_SIZE) {
			tmpy[i] -= WIN_Y_SIZE;
		}
	}

	return 0;
}

DWORD WINAPI DIVEMOVEThread(LPVOID prc) {

	int i = (int)prc;
	
	std::cout << i << "!";
	Sound_Play(S_EN_DIVE);
	int tmp = Enemy[i].y;
	for (; Enemy[i].y < Player.y;) {
		Enemy[i].y += 5;
		Sleep(10);
	}
	
	for (; Enemy[i].y != tmp; Enemy[i].y--) {
		Sleep(5);
	}
	

	return 0;
}

DWORD WINAPI DIVEControlThread(LPVOID prc) {

	for (;;) {
		for (int i = 0; i < MAX_ENEMY; i++) {
			if (Enemy[i].Live == 0)
				continue;
			//이런 개 새... switch문안에 for문안에 if문안에 if문안에 for문안에 if문안에 if문안데 if문안에 goto문 What The Fuck!!
			if (Percentage(PERCOFENEMYDIVE)) {
				for (int j = 0; j < MAX_ENEMY; j++) {
					if (Enemy[j].Live > 0) {
						//살아있는 적 중
						if (Enemy[j].y > Enemy[i].y) {
							//나보다 앞에 있는 적 중에
							if (Enemy[j].x <= Enemy[i].x + 20 && Enemy[j].x >= Enemy[i].x - 20) {
								//내앞에 적이 있다면
								goto NOFIRE;
							}
						}
					}


				}
				CloseHandle(CreateThread(nullptr, 0, DIVEMOVEThread, (LPVOID)i, 0, nullptr));
				//break;	//<-사용하면 한번에 한개씩
			NOFIRE:
				continue;

			}
		}
		Sleep(5000);
	}


	return 0;
}


//배경 그리기 쓰레드
DWORD WINAPI BGThread(LPVOID prc) {
	HDC hdc = GetDC(g_hWnd);
	for (;;) {
		for (int i = 0; i < 100; i++) {

			// ReSharper disable once CppUnreachableCode
			if (BGDOTTYPE == 1) {
				//큰 알록달록 점
				SetPixel(hdc, tmpx[i], tmpy[i],
				         RGB(tmprnd1[i], tmprnd2[i], tmprnd3[i]));
				SetPixel(hdc, tmpx[i] + 1, tmpy[i] + 1,
				         RGB(tmprnd1[i], tmprnd2[i], tmprnd3[i]));
				SetPixel(hdc, tmpx[i] + 1, tmpy[i],
				         RGB(tmprnd1[i], tmprnd2[i], tmprnd3[i]));
				SetPixel(hdc, tmpx[i], tmpy[i] + 1,
				         RGB(tmprnd1[i], tmprnd2[i], tmprnd3[i]));

			}
			if (BGDOTTYPE == 2) {
				//큰 흰 점
				SetPixel(hdc, tmpx[i], tmpy[i],
				         RGB(tmprnd1[i], tmprnd1[i], tmprnd1[i]));
				SetPixel(hdc, tmpx[i] + 1, tmpy[i] + 1,
				         RGB(tmprnd1[i], tmprnd1[i], tmprnd1[i]));
				SetPixel(hdc, tmpx[i] + 1, tmpy[i],
				         RGB(tmprnd1[i], tmprnd1[i], tmprnd1[i]));
				SetPixel(hdc, tmpx[i], tmpy[i] + 1,
				         RGB(tmprnd1[i], tmprnd1[i], tmprnd1[i]));
			}
			else if (BGDOTTYPE == 3) {
				//작은 rgb 점
				SetPixel(hdc, tmpx[i], tmpy[i],
				         RGB(tmprnd1[i], tmprnd2[i], tmprnd3[i]));

			}
			else if (BGDOTTYPE == 4) {
				//작은 rgb 점
				SetPixel(hdc, tmpx[i], tmpy[i],
				         RGB(tmprnd1[i], tmprnd1[i], tmprnd1[i]));

			}


		}
		Sleep(1);
	}

	// ReSharper disable once CppUnreachableCode
	ReleaseDC(g_hWnd, hdc);

}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	g_hWnd = hWnd;
	switch (message) {
	case WM_CREATE : {
		hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
		SetCursor(hCursor);


		MoveWindow(hWnd, 10, 10, WIN_X_SIZE, WIN_Y_SIZE, TRUE);
		hWndConsole = GetConsoleWindow();
		SetConsoleTitle((LPCWSTR)L"디버그 콘솔");
		system("color 0A");
		ShowWindow(hWndConsole, SW_HIDE);
		SetTimer(hWnd, TM_NEWFRM, (int)(((float)1 / (float)FRAMEPERSEC) * (float)1000), nullptr);

		SetTimer(hWnd, TM_DRAWBGSTAR, 300, (TIMERPROC)BGTimerProc_RND);
		//CloseHandle(CreateThread(NULL, 0, BGThread_RND, NULL, 0, NULL));

		hThread_BG = CreateThread(nullptr, 0, BGThread, nullptr, 0, nullptr);


	}
	break;
	case WM_SETCURSOR :
		if (LOWORD(lParam) == HTCLIENT) {
			SetCursor(hCursor);
			return TRUE;
		}
		break;

	case WM_GETMINMAXINFO :


		((MINMAXINFO *)lParam)->ptMaxTrackSize.x = WIN_X_SIZE;

		((MINMAXINFO *)lParam)->ptMaxTrackSize.y = WIN_Y_SIZE;

		((MINMAXINFO *)lParam)->ptMinTrackSize.x = WIN_X_SIZE;

		((MINMAXINFO *)lParam)->ptMinTrackSize.y = WIN_Y_SIZE;

		return FALSE;
	case WM_COMMAND : {
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId) {
		case IDM_ABOUT :
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT :
			DestroyWindow(hWnd);
			break;
		case ID_32778 :
			ShowWindow(hWndConsole, SW_SHOWNORMAL);
			break;


		case ID_32779 :
			MoveWindow(hWnd, 10, 10, WIN_X_SIZE, WIN_Y_SIZE, TRUE);
			break;
		case ID_32781 :
			Player.Live = 9999;
			break;
		case ID_32782 :
			levelclearhack = true;
			break;

		case BTN_PAUSE : {
			HWND hBtn = GetDlgItem(hWnd, BTN_PAUSE); // 1. 버튼의 핸들을 구함
			EnableWindow(hBtn, FALSE);               // 2. 핸들에 활성화(TRUE)/비활성화(FALSE) 값을 줌
			ShowWindow(hBtn, SW_HIDE);
			HWND hBtn2 = GetDlgItem(hWnd, BTN_RESUME); // 1. 버튼의 핸들을 구함
			EnableWindow(hBtn2, TRUE);                 // 2. 핸들에 활성화(TRUE)/비활성화(FALSE) 값을 줌
			ShowWindow(hBtn2, SW_SHOW);
			std::cout << "Game Paused";
			KillTimer(hWnd, TM_CTRL);
			KillTimer(hWnd, TM_NEWFRM);
			KillTimer(hWnd, TM_ENEMYCTRL);
			KillTimer(hWnd, TM_ENMFIRE);
			TerminateThread(hThread_BG, 5);
			TerminateThread(DIVEMOVEThread, 5);
			TerminateThread(DIVEControlThread, 5);
			SetFocus(nullptr);

		}
		break;
		case BTN_RESUME : {
			hThread_BG = CreateThread(nullptr, 0, BGThread, nullptr, 0, nullptr);
			hThread_BG = CreateThread(nullptr, 0, DIVEControlThread, nullptr, 0, nullptr);

			HWND hBtn = GetDlgItem(hWnd, BTN_RESUME); // 1. 버튼의 핸들을 구함
			EnableWindow(hBtn, FALSE);                // 2. 핸들에 활성화(TRUE)/비활성화(FALSE) 값을 줌
			ShowWindow(hBtn, SW_HIDE);
			HWND hBtn2 = GetDlgItem(hWnd, BTN_PAUSE); // 1. 버튼의 핸들을 구함
			EnableWindow(hBtn2, TRUE);                // 2. 핸들에 활성화(TRUE)/비활성화(FALSE) 값을 줌
			ShowWindow(hBtn2, SW_SHOW);

			std::cout << "Game Paused";
			SetTimer(hWnd, TM_CTRL, (int)(((float)1 / (float)CTRLPERSEC) * (float)1000), (TIMERPROC)Control);
			SetTimer(hWnd, TM_NEWFRM, (int)(((float)1 / (float)FRAMEPERSEC) * (float)1000), nullptr);
			SetTimer(hWnd, TM_ENEMYCTRL, ENEMYCTRLTMRDELAY, nullptr);
			SetTimer(hWnd, TM_ENMFIRE, (int)(((float)1 / (float)ENMFIREPERSEC) * (float)1000), nullptr);
			SetFocus(nullptr);

		}
		break;
		default :
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT : {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps); //ok
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

		hdc = BeginPaint(hWnd, &ps);


		if (gamestarted) {
			DrawScreen(hWnd);
			std::wstring str_score = (std::wstring)L"SCORE: ";
			//str_score += std::to_wstring(score);

			std::wstring str_health = (std::wstring)L" HEALTH: ";
			//str_health += std::to_wstring(Player.Live);

			std::wstring str_level = (std::wstring)L"LEVEL ";
			str_level += std::to_wstring(Player.level);

			HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Press Start 2P"));
			HDC hMemDC = GetDC(hWnd);

			SetTextColor(hMemDC, RGB(255, 255, 255));
			SetBkColor(hMemDC, RGB(0, 0, 0));
			SelectObject(hMemDC, hFont);
			TextOut(hMemDC, 80, 05, str_level.c_str(), str_level.length());


			SetTextColor(hMemDC, RGB(255, 0, 0));
			SetBkColor(hMemDC, RGB(0, 0, 0));
			SelectObject(hMemDC, hFont);
			TextOut(hMemDC, WIN_X_SIZE - 800, 05, str_health.c_str(), str_health.length());

			SetTextColor(hMemDC, RGB(255, 255, 255));
			SetBkColor(hMemDC, RGB(0, 0, 0));
			SelectObject(hMemDC, hFont);
			TextOut(hMemDC, WIN_X_SIZE - 560, 05, std::to_wstring(Player.Live).c_str(),
			        std::to_wstring(Player.Live).length());


			SetTextColor(hMemDC, RGB(0, 255, 0));
			SetBkColor(hMemDC, RGB(0, 0, 0));
			SelectObject(hMemDC, hFont);
			TextOut(hMemDC, WIN_X_SIZE - 400, 05, str_score.c_str(), str_score.length());

			SetTextColor(hMemDC, RGB(255, 255, 255));
			SetBkColor(hMemDC, RGB(0, 0, 0));
			SelectObject(hMemDC, hFont);
			TextOut(hMemDC, WIN_X_SIZE - 220, 05, std::to_wstring(score).c_str(), std::to_wstring(score).length());

			for (int i = 50; i < 100; i++) {
				for (int j = 50; j < 100; j++) {
					SetPixelV(hdc, i, j, RGB(255, 255, 255));

				}
			}
			ReleaseDC(hWnd, hMemDC);

		}
		else {

			HFONT hFont_segoe = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Segoe UI"));
			HDC hMemDC = GetDC(hWnd);

			HDC drawDC = GetDC(g_hWnd);
			HDC hMemDC1 = CreateCompatibleDC(drawDC);


			HBITMAP Title = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP18));


			SelectObject(hMemDC1, HBITMAP(Title));	//비트맵 연결
			BitBlt(drawDC, 380, 128, WIN_X_SIZE + 256, WIN_Y_SIZE - 128, hMemDC1, 0, 0, SRCCOPY);

			SetTextColor(hMemDC, RGB(255, 0, 255));
			SetBkColor(hMemDC, RGB(0, 0, 0));
			SelectObject(hMemDC, hFont_segoe);
			std::wstring str_level = (std::wstring)L"Press Space Key...";
			
			FMOD_Channel_IsPlaying(channel, &IsPlaying);
			if(IsPlaying) {
				str_level = (std::wstring)L"Starting...";
			}
			TextOut(hMemDC, WIN_X_SIZE / 2 - 100, WIN_Y_SIZE / 2 + 100, str_level.c_str(), str_level.length());


			if ((GetAsyncKeyState(32) & 0x8000) && !active_tmp_1) {
				SoundInit();
				Sound_Play(S_START);

				Rectangle(hdc, 0, 0, WIN_X_SIZE, WIN_Y_SIZE);
				SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
				FMOD_Channel_IsPlaying(channel, &IsPlaying);
				active_tmp_1 = true;
				std::cout << active_tmp_1;
				
			}
			FMOD_Channel_IsPlaying(channel, &IsPlaying);

			if(!IsPlaying && active_tmp_1) {
				Sound_Play(S_LEVEL);
				KillTimer(hWnd, TM_NEWFRM);
				
				HBRUSH MyBrush = (HBRUSH)GetStockObject(GRAY_BRUSH);
				HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
				Rectangle(hdc, 0, 0, WIN_X_SIZE, WIN_Y_SIZE);
				SelectObject(hdc, OldBrush);
				


				HFONT hFont_segoe = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Press Start 2P"));
				HDC hMemDC = GetDC(hWnd);
				SetTextColor(hMemDC, RGB(255, 0, 0));
				SetBkColor(hMemDC, RGB(0, 0, 0));
				SelectObject(hMemDC, hFont_segoe);
				std::wstring str_level = (std::wstring)L"Level 1";
				TextOut(hMemDC, WIN_X_SIZE / 2 - 100, WIN_Y_SIZE / 2 + 100, str_level.c_str(), str_level.length());
				Sleep(1000);

				CreateWindow((LPCWSTR)L"button", (LPCWSTR)L"▐ ▌", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, WIN_X_SIZE -
					100, 20, 50, 50, hWnd, (HMENU)BTN_PAUSE, hInst, NULL);
				CreateWindow((LPCWSTR)L"button", (LPCWSTR)L"▶", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, WIN_X_SIZE - 100,
					20, 50, 50, hWnd, (HMENU)BTN_RESUME, hInst, NULL);
				HWND hBtn = GetDlgItem(hWnd, BTN_RESUME); // 1. 버튼의 핸들을 구함
				EnableWindow(hBtn, FALSE);
				ShowWindow(hBtn, SW_HIDE);
				Player.level = 1;
				for (int i = 0; i < MAX_ENEMY; i++) {
					//TODO: Init 함수 만들어 버리기
					Enemy[i].x = 0;
					Enemy[i].y = 0;
					Enemy[i].Live = 0;
					Enemy[i].level = 0;
				}
				for (int i = 0; i < MAXEBULLET; i++) {
					EBullet[i].x = 0;
					EBullet[i].y = 0;
					EBullet[i].isUsed = 0;
				}
				//Sound_Play(S_BGM);
				Player.Live = 3;
				Player.x = WIN_X_SIZE / 2 + 50;
				Player.y = WIN_Y_SIZE - 150;
				for (int i = 0; i < MAXBULLET; i++)
					PBullet[i].isUsed = 0;
				SetTimer(hWnd, TM_CTRL, (int)(((float)1 / (float)CTRLPERSEC) * (float)1000), (TIMERPROC)Control);
				SetTimer(hWnd, TM_ENEMYCTRL, ENEMYCTRLTMRDELAY, nullptr);

				SetTimer(hWnd, TM_FIRECTRL, BULLETDELAY, nullptr);
				SetTimer(hWnd, TM_ENMFIRE, (int)(((float)1 / (float)ENMFIREPERSEC) * (float)1000), nullptr);

				CloseHandle(CreateThread(nullptr, 0, DIVEControlThread, nullptr, 0, nullptr));
				for (int i = 500; i < WIN_X_SIZE - 500; i += 50) {
					spawnEnemy(i, 60, 3);
				}
				for (int i = 440; i < WIN_X_SIZE - 440; i += 50) {
					spawnEnemy(i, 100, 2);
				}
				for (int i = 440; i < WIN_X_SIZE - 440; i += 50) {
					spawnEnemy(i, 140, 2);
				}
				for (int i = 340; i < WIN_X_SIZE - 340; i += 50) {
					spawnEnemy(i, 180, 1);
				}
				for (int i = 340; i < WIN_X_SIZE - 340; i += 50) {
					spawnEnemy(i, 220, 1);
				}
				//spawnEnemy();

				srand(int(time(nullptr)));
				//SetFocus(nullptr);

				std::cout << "wtf";
				gamestarted = true;
			}
		}

		if(gamestarted && initparam == false) {

			HBRUSH MyBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
			HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
			Rectangle(hdc, 0, 0, WIN_X_SIZE, WIN_Y_SIZE);
			SelectObject(hdc, OldBrush);



			HFONT hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Press Start 2P"));
			HDC hMemDC = GetDC(hWnd);
			SetTextColor(hMemDC, RGB(255, 0, 0));
			SetBkColor(hMemDC, RGB(0, 0, 0));
			SelectObject(hMemDC, hFont);
			std::wstring str_level = (std::wstring)L"Level 1";
			TextOut(hMemDC, WIN_X_SIZE / 2 - 100, WIN_Y_SIZE / 2 + 100, str_level.c_str(), str_level.length());
			Sleep(1000);
			initparam = true;
			SetTimer(hWnd, TM_NEWFRM, (int)(((float)1 / (float)FRAMEPERSEC) * (float)1000), nullptr);

		}


		EndPaint(hWnd, &ps);

	}
	break;


	case WM_TIMER : {
		switch (wParam) {

		case TM_NEWFRM :


			InvalidateRect(g_hWnd, nullptr, TRUE); //화면을 지우고 WM_PAINT 콜
			//InvalidateRect(hWnd, NULL, TRUE);

			break;
		case TM_ENMFIRE : {
			enemysprite = ! enemysprite;

			for (int i = 0; i < MAX_ENEMY; i++) {
				if (Enemy[i].Live == 0)
					continue;
				//이런 개 새... switch문안에 for문안에 if문안에 if문안에 for문안에 if문안에 if문안데 if문안에 goto문 What The Fuck!!
				if (Percentage(PERCOFENEMYFIRE)) {
					for (int j = 0; j < MAX_ENEMY; j++) {
						if (Enemy[j].Live > 0) {
							//살아있는 적 중
							if (Enemy[j].y > Enemy[i].y) {
								//나보다 앞에 있는 적 중에
								if (Enemy[j].x <= Enemy[i].x + 20 && Enemy[j].x >= Enemy[i].x - 20) {
									//내앞에 적이 있다면
									goto NOFIRE;
								}
							}
						}


					}
					EnemyFire(i);
					//break;	//<-사용하면 한번에 한발씩 쏜다
				NOFIRE:
					continue;

				}
			}


			break;
		}

		case TM_FIRECTRL :
			canFire = true;
			break;
		case TM_ENEMYCTRL :
			CtrlEnemy();


			break;

		}
	}
	break;
	case WM_DESTROY :


		PostQuitMessage(0);
		break;
	default :
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
	case WM_INITDIALOG :
		return (INT_PTR)TRUE;

	case WM_COMMAND :
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

// 이것은 지옥입니다. 절대 현실아니구여(F**king)
