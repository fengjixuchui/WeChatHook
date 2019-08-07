// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "resource.h"
#include "WXESubject.h"

DWORD& WXEBaseAddress() {
	static DWORD base = 0;
	if(base == 0)
		base = (DWORD)LoadLibrary(L"WeChatWin.dll"); //单线程测试
	return base;
}

WXESubject subject = { WXEVersion_2_6_8_51, WXEBaseAddress() };


INT_PTR CALLBACK DlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_INITDIALOG) {
		SetDlgItemText(hWnd, IDC_EDIT1, L"v1_efa0a650c06c0549572b2d9eb92beb6ea34083bde3b28da2f57d7026d07ea15c@stranger");//zhou091679
		//SetDlgItemText(hWnd, IDC_EDIT2, L"v2_f7b3f9bd857552c2a49b0b1a2be38c352e864f0bca9141f9141bfb98e7de5decbe604a3ad41745c1dda7093798ca91e27bf85ab4e46af13ead924fb0b16afee8@stranger");
		SetDlgItemText(hWnd, IDC_EDIT2, L"wxid_t4jyzahv4yvc11");
		SetDlgItemText(hWnd, IDC_EDIT3, L"wxid_ssxmbzolaz3u12");
		SetDlgItemText(hWnd, IDC_EDIT4, L"penglovenan2012");
		//SetDlgItemText(hWnd, IDC_EDIT3, L"wxid_t4jyzahv4yvc11");
		//SetDlgItemText(hWnd, IDC_EDIT4, L"18850574785@chatroom");
		//wchar_t v1[0x200] = { 0 };
		//wchar_t v2[0x200] = { 0 };
		//GetDlgItemText(hWnd, IDC_EDIT3, v1, 0x200);
		//GetDlgItemText(hWnd, IDC_EDIT4, v2, 0x200);
	}
	if (uMsg == WM_CLOSE) {
		EndDialog(hWnd, 0);
	}
	if (uMsg == WM_COMMAND) {
		if (wParam == IDOK) {

			wchar_t v1[0x500] = { 0 };
			wchar_t self[0x200] = { 0 };
			wchar_t xiaohao[0x200] = { 0 };
			wchar_t YPhao[0x200] = { 0 };
			GetDlgItemText(hWnd, IDC_EDIT1, v1, 0x500);
			GetDlgItemText(hWnd, IDC_EDIT2, xiaohao, 0x200);
			GetDlgItemText(hWnd, IDC_EDIT3, self, 0x200);
			GetDlgItemText(hWnd, IDC_EDIT4, YPhao, 0x200);

			//subject.getLoginQRCode();
			//subject.createChatRoom();
			//subject.sendFriendVerification(xiaohao, std::wstring(L"111"));
			subject.agreeFriendRequest(v1, std::wstring(L""));
		} else if (wParam == IDCANCEL) {

		}
		return 0;
	}
	return false;
}

DWORD WINAPI threadProcess(HMODULE hModule)
{
	DialogBox(hModule, MAKEINTRESOURCE(IDD_DIALOG1), NULL, &DlgProc);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadProcess, hModule, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}