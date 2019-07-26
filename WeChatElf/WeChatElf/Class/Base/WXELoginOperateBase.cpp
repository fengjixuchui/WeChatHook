#include "stdafx.h"
#include "WXELoginOperateBase.h"

static bool openGetQRCode = false;
static std::array<BYTE, 5> backupGetQRCode;
static WXEHookItems<5> globleHookGetQRCodeItems;
static WXESecurityStore<WXEUserID> store = { WXESecurityStore<WXEUserID>(false) };
void getQRCodeCallback();
void sendQRCodePNG(DWORD pngHeaderPtr);

WXELoginOperateBase::~WXELoginOperateBase() {

}

WXELoginOperateSimple::WXELoginOperateSimple(DWORD address)
	:winBaseAddress(address),
	hookOperator(WXEHookOperator<5>{ }) {

}

WXELoginOperateSimple::~WXELoginOperateSimple() {

}

WXEError WXELoginOperateSimple::getLoginQRCode(WXENetSceneCallback<WXEData> callback) const {
	WXEError result = WXEErrorSuccess;
	if (!openGetQRCode) {
		if ((result = hookGetQRCode(true)) != WXEErrorSuccess) {
			return result;
		}
	}
	//store.setObject(callback);
	// send get qrcode ....
	return result;
}

WXEError WXELoginOperateSimple::hookGetQRCode(bool open) const {
	if (globleHookGetQRCodeItems.hookAddress == 0) {
		globleHookGetQRCodeItems = hookGetQRCodeItems;
		globleHookGetQRCodeItems.jumpCall = (DWORD)getQRCodeCallback;
		globleHookGetQRCodeItems.disposeCall = (DWORD)sendQRCodePNG;
	}

	if (open) {
		backupGetQRCode[0] = 0xE9;
		*(DWORD *)&backupGetQRCode[1] = globleHookGetQRCodeItems.jumpCall - hookGetQRCodeItems.hookAddress - 5;
	}

	WXEError result = hookOperator.execute((LPCVOID)globleHookGetQRCodeItems.hookAddress, backupGetQRCode);
	if (result == WXEErrorSuccess)
		openGetQRCode = open;

	return WXEErrorSuccess;
}

void __declspec(naked)getQRCodeCallback() {
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

void sendQRCodePNG(DWORD pngHeaderPtr) {
	/*
	 WXEData data = WXEData(*(CHAR **)pngHeaderPtr, *(DWORD *)(pngHeaderPtr + 0x4));
	 WXENetSceneCallback<WXEData> callback = store.object();
	 if (data.size > 0) {
	 callback(WXEErrorSuccess, data);
	 } else {
	 callback(WXEErrorNetSceneRequestFailed, data);
	 }
	 */
}
