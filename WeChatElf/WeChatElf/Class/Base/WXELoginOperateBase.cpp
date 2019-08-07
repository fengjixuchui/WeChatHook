#include "stdafx.h"
#include "WXELoginOperateBase.h"

static bool openGetQRCode = false; 
static std::array<BYTE, 5> backupGetQRCode;
static WXEHookItems<5> globleHookGetQRCodeItems;
void getQRCodeCallback();
void __stdcall disposeQRCodePNG(DWORD pngHeaderPtr);

std::mutex mutex;// = std::mutex();
std::condition_variable condVar;// = std::condition_variable();
WXESecurityStore<WXENetSceneCallback<WXEData>> QRCodeStore;


WXELoginOperateBase::~WXELoginOperateBase() {

}

WXELoginOperateSimple::WXELoginOperateSimple(DWORD address)
:winBaseAddress(address) {

}

WXELoginOperateSimple::~WXELoginOperateSimple() {

}

WXEError WXELoginOperateSimple::hookGetQRCode(bool open) {
	if (open) {
		if (openGetQRCode) return WXEErrorSuccess;
		globleHookGetQRCodeItems = hookGetQRCodeItems;
		globleHookGetQRCodeItems.jumpCall = (DWORD)getQRCodeCallback;
		globleHookGetQRCodeItems.disposeCall = (DWORD)disposeQRCodePNG;
		backupGetQRCode[0] = 0xE9;
		*(DWORD *)&backupGetQRCode[1] = globleHookGetQRCodeItems.jumpCall - hookGetQRCodeItems.hookAddress - 5;
	}

	WXEHookOperator<5> hookOperator;
	WXEError result = hookOperator.execute((LPCVOID)globleHookGetQRCodeItems.hookAddress, backupGetQRCode);
	if (result == WXEErrorSuccess)
		openGetQRCode = open;
	return result;
}

void __declspec(naked)getQRCodeCallback() {
	__asm {
		pushad
		pushfd
		push ecx
		call globleHookGetQRCodeItems.disposeCall
		popfd
		popad
		call globleHookGetQRCodeItems.originCall
		jmp globleHookGetQRCodeItems.nextOrderAddress
	}
}

void __stdcall disposeQRCodePNG(DWORD pngHeaderPtr) {
	std::unique_lock <std::mutex> lock(mutex);
	WXEData data = WXEData(*(CHAR **)pngHeaderPtr, *(DWORD *)(pngHeaderPtr + 0x4));
	if (QRCodeStore.isValid()) {
		WXENetSceneCallback<WXEData> callback = QRCodeStore.object();
		callback(WXEErrorSuccess, data);
	}
	condVar.notify_one();
}


