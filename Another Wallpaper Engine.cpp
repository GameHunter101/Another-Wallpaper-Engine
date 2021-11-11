#include "C:\Users\liors\Documents\Coding projects\testing_project\resource.h"
#include <shellapi.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <gdiplus.h>
#include <conio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <thread>
#include <chrono>
#include <string>

#define ID_BTNCLOSE 0
#define ID_BTNCNFRM 0

using namespace std;





HWND window_main;
HWND control_window;
UINT WM_TASKBAR = 0;
HMENU Hmenu;
NOTIFYICONDATA notifyIconData;
TCHAR szTIP[64] = TEXT("Another WP Engine");
char szClassName[] = "Another Wallpaper Engine";


LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void minimize();
void restore();
void InitNotifyIconData();






BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
	HWND p = FindWindowEx(hwnd, NULL, "SHELLDLL_DefView", NULL);
	HWND* ret = (HWND*)lParam;

	if (p)
	{
		// Gets the WorkerW Window after the current one.
		*ret = FindWindowEx(NULL, hwnd, "WorkerW", NULL);
	}
	return true;
}

HWND get_wallpaper_window()
{
	// Fetch the Progman window
	HWND progman = FindWindow("ProgMan", NULL);
	// Send 0x052C to Progman. This message directs Progman to spawn a 
	// WorkerW behind the desktop icons. If it is already there, nothing 
	// happens.
	SendMessageTimeout(progman, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);
	// We enumerate all Windows, until we find one, that has the SHELLDLL_DefView 
	// as a child. 
	// If we found that window, we take its next sibling and assign it to workerw.
	HWND wallpaper_hwnd = nullptr;
	EnumWindows(EnumWindowsProc, (LPARAM)&wallpaper_hwnd);
	// Return the handle you're looking for.
	return wallpaper_hwnd;
}

HWND get_gif_window() {
	for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT))
	{

		if (!IsWindowVisible(hwnd))
			continue;

		int length = GetWindowTextLength(hwnd);
		if (length == 0)
			continue;

		char* title = new char[length + 1];
		//GetWindowText(hwnd, const_cast<char *>(title.c_str()), length + 1);
		GetWindowText(hwnd, title, length + 1);
		string temp;
		temp = title;
		if (title == "Program Manager")
			continue;
		if (temp == "custom_wallpaper") {
			//std::cout << "HWND: " << hwnd << " Title: " << title << "!!!!!!!"<< std::endl;
			HWND temp_gif = FindWindowExA(hwnd, NULL, NULL, NULL);
			return temp_gif;
			//OutputDebugString(title);
			//OutputDebugStringW(L"\n");
		}
		//OutputDebugString(title);
		//OutputDebugStringW(L"\n");

		//std::cout << "HWND: " << hwnd << " Title: " << temp << std::endl;
	}
}



int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, LPSTR lpszArgument, int nCmdShow) {
	// Initialize GDI+ for images
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);


	// Register the window class
	const char* CLASS_NAME = "myWin32WindowClass";
	WNDCLASSEX wincl{};
	wincl.hInstance = currentInstance;
	wincl.lpszClassName = CLASS_NAME;
	wincl.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wincl.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wincl.lpfnWndProc = WindowProcedure;





	WM_TASKBAR = RegisterWindowMessageA("TaskbarCreated");
	/* The Window structure */
	wincl.hInstance = currentInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	wincl.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */


	if (!RegisterClassEx(&wincl))
		return -1;
	this_thread::sleep_for(std::chrono::milliseconds(1000));

	//ShellExecute(NULL, NULL, "wp_engine.exe", NULL, NULL, SW_SHOW);
	//ShellExecute(NULL, NULL, "video_display.exe", NULL, NULL, SW_SHOW);
	//Sleep(2000);

	//HWND gif_win = FindWindowExA(parent_gif_win, NULL, NULL, "wallpaper.gif");
	//HWND gif_win = FindWindow("Qt5152QWindowIcon", NULL);
	//HWND gif_win = FindWindow("Main HighGUI class", NULL);
	HWND gif_win = FindWindow(NULL, "another_wallpaper_video_looper_69420");

	if (gif_win != 0) {

		OutputDebugString("found window");

		HWND wallpaper = get_wallpaper_window();
		window_main = gif_win;
		//control_window = CreateWindowA(CLASS_NAME, "control", WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX, 500, 500, 300, 300, nullptr, nullptr, nullptr, nullptr);
		control_window = CreateWindowA(szClassName, szClassName, WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX, 500, 500, 200, 90, nullptr, nullptr, nullptr, nullptr);
		HWND button = CreateWindowA(
			"BUTTON",  // Predefined class; Unicode assumed 
			"CLOSE",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			10,						// x position 
			10,						// y position 
			160,					// Button width
			30,						// Button height
			control_window,			// Parent window
			(HMENU)ID_BTNCLOSE,		// No menu.
			NULL,
			NULL);					// Pointer not needed.




		InitNotifyIconData();
		SetWindowLongA(window_main, GWL_STYLE, 0);
		SetWindowPos(window_main, HWND_BOTTOM, 0, 0, 3840, 1080, SWP_NOACTIVATE);
		SetParent(window_main, wallpaper);
		ShowWindow(control_window, nCmdShow);
		ShowWindow(window_main, SW_SHOW);
		UpdateWindow(control_window);
	}
	else {
		OutputDebugString("not found");
	}
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Gdiplus::GdiplusShutdown(gdiplusToken);
	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	string path;
	ifstream MyReadFile("temp.txt");
	getline(MyReadFile, path);
	int ret;
	std::wstring widestr = std::wstring(path.begin(), path.end());
	const wchar_t* widecstr = widestr.c_str();
	ret = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void*)widecstr, SPIF_UPDATEINIFILE);


	if (msg == WM_TASKBAR && !IsWindowVisible(control_window))
	{
		minimize();
		return 0;
	}


	switch (msg) {
	case WM_ACTIVATE:
		Shell_NotifyIcon(NIM_ADD, &notifyIconData);
		break;
	case WM_CREATE:

		ShowWindow(control_window, SW_HIDE);
		Hmenu = CreatePopupMenu();
		AppendMenu(Hmenu, MF_STRING, ID_TRAY_EXIT, TEXT("Close Program"));

		break;
	case WM_SYSCOMMAND:
		/*In WM_SYSCOMMAND messages, the four low-order bits of the wParam parameter
		are used internally by the system. To obtain the correct result when testing the value of wParam,
		an application must combine the value 0xFFF0 with the wParam value by using the bitwise AND operator.*/

		switch (wParam & 0xFFF0)
		{
		case SC_MINIMIZE:
		case SC_CLOSE:
			minimize();
			return 0;
			break;
		}
		break;
	case WM_SYSICON:
	{

		switch (wParam)
		{
		case ID_TRAY_APP_ICON:
			SetForegroundWindow(control_window);

			break;
		}


		if (lParam == WM_LBUTTONUP)
		{

			restore();
		}
		else if (lParam == WM_RBUTTONDOWN)
		{
			// Get current mouse position.
			POINT curPoint;
			GetCursorPos(&curPoint);
			SetForegroundWindow(control_window);

			// TrackPopupMenu blocks the app until TrackPopupMenu returns

			UINT clicked = TrackPopupMenu(Hmenu, TPM_RETURNCMD | TPM_NONOTIFY, curPoint.x, curPoint.y, 0, hwnd, NULL);



			SendMessage(hwnd, WM_NULL, 0, 0); // send benign message to window to make sure the menu goes away.
			if (clicked == ID_TRAY_EXIT)
			{
				// quit the application.
				Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
				//PostQuitMessage(0);
				//UpdateWindow(window_main);
				ret = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, (void*)widecstr, SPIF_UPDATEINIFILE);
				SetParent(window_main, control_window);
				DestroyWindow(window_main);
				DestroyWindow(control_window);
				remove("temp.txt");
				_Exit(10);
			}
		}
	}
	break;
	case WM_NCHITTEST:
	{
		UINT uHitTest = DefWindowProc(hwnd, WM_NCHITTEST, wParam, lParam);
		if (uHitTest == HTCLIENT)
			return HTCAPTION;
		else
			return uHitTest;
	}
	case WM_CLOSE:

		minimize();
		return 0;
		break;
	case WM_DESTROY:

		PostQuitMessage(0);
		DestroyWindow(window_main);
		DestroyWindow(hwnd);
		remove("temp.txt");
		_Exit(10);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	case WM_COMMAND: {
		switch (wParam) {
		case ID_BTNCLOSE: {
			UpdateWindow(window_main);
			SetParent(window_main, control_window);
			DestroyWindow(window_main);
			DestroyWindow(hwnd);
			_Exit(10);
			break;
		}/*
		case 1: {
			int gwstat = 0;
			char* t = &retrieved_path[0];
			gwstat = GetWindowText(text_box, t, 50);
			temp_path = retrieved_path;
		}*/
		}
		break;
	}
	}
	return 0;
}

void minimize()
{
	// hide the main window
	ShowWindow(control_window, SW_HIDE);
}


void restore()
{
	ShowWindow(control_window, SW_SHOW);
}

void InitNotifyIconData()
{
	memset(&notifyIconData, 0, sizeof(NOTIFYICONDATA));

	notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
	notifyIconData.hWnd = control_window;
	notifyIconData.uID = ID_TRAY_APP_ICON;
	notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	notifyIconData.uCallbackMessage = WM_SYSICON; //Set up our invented Windows Message
	notifyIconData.hIcon = (HICON)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
	strncpy_s(notifyIconData.szTip, szTIP, sizeof(szTIP));
}