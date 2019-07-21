#include "stdafx.h"
#include "WXEHookOperateBase.h"

WXEHookItems<5> globleHookGetQRCodeItems;
WXEHookItems<5> globleHookTransferResultItems;
WXEHookItems<5> globlehookReceiveMessageItems;
WXEHookItems<5> globleHookGetUserInfoFromNetworkItems;

WXEHookOperateBase::~WXEHookOperateBase() {

}

WXEHookOperateSimple::WXEHookOperateSimple(DWORD address)
:winBaseAddress(address) {
	
}

bool WXEHookOperateSimple::isOpenGetQRCode() const {
	return openGetQRCode;
}

void WXEHookOperateSimple::hookGetQRCode(bool open) {
	WXEHookOperator<5> hookOperator;
	globleHookGetQRCodeItems = hookGetQRCodeItems;
	void (WXEHookOperateSimple::*getQRCodeCallbackFun)() = &WXEHookOperateSimple::getQRCodeCallback;
	if (open) {
		backupGetQRCode[0] = 0xE9;
		*(DWORD *)&backupGetQRCode[1] = *(DWORD *)&getQRCodeCallbackFun - hookGetQRCodeItems.hookAddress - 5;
	}
	WXEError result = hookOperator.execute(hookGetQRCodeItems.hookAddress, backupGetQRCode);
	openGetQRCode = (result == WXEErrorSuccess) && open;
}

void __declspec(naked)WXEHookOperateSimple::getQRCodeCallback() {
	__asm {
		pushad
		pushfd
		push ecx
		call sendQRCodePNG
		popfd
		popad
		call globleHookGetQRCodeItems.originCall
		jmp globleHookGetQRCodeItems.nextOrderAddress
	}
}

void WXEHookOperateSimple::sendQRCodePNG(const DWORD& pngHeaderPtr) const {
	WXEData pngData = WXEData(*(CHAR **)pngHeaderPtr, *(DWORD *)(pngHeaderPtr + 0x4));
	WCHAR szFile[] = L"C:\\test.png";
	HANDLE hFile = CreateFile(szFile,	//创建文件的名称。
		GENERIC_WRITE,					 // GENERIC_WRITE | GENERIC_READ, 写和读文件。 
		FILE_SHARE_READ,				 // 共享读。
		NULL,							// 缺省安全属性
		CREATE_ALWAYS,					// CREATE_ALWAYS  覆盖文件（不存在则创建）    OPEN_EXISTING 打开文件（不存在则报错）
		FILE_ATTRIBUTE_NORMAL,			// 一般的文件。
		NULL);							// 模板文件为空。
	if (hFile == INVALID_HANDLE_VALUE) {  //无效值
		OutputDebugString(TEXT("CreateFile fail!\r\n"));
	}
	DWORD dwSize = pngData.size; //读取文件大小
	char* cBuf = (char*)pngData.bytes;
	DWORD dwreturnsize;
	WriteFile(hFile, cBuf, dwSize, &dwreturnsize, NULL);
	//delete[] cBuf;
	CloseHandle(hFile);
}

