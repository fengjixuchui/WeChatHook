#include "stdafx.h"
#include "WXEHookOperateV2_6_8_51.h"

WXEHookItems<5> hookGetQRCodeItems;
WXEHookItems<5> hookTransferResultItems;
WXEHookItems<5> hookReceiveMessageItems;
WXEHookItems<5> hookGetUserInfoFromNetworkItems;

WXEHookOperateV2_6_8_51::WXEHookOperateV2_6_8_51(DWORD address)
:WXEHookOperateSimple(address) {
	initHookOffset();
}


WXEHookOperateV2_6_8_51::~WXEHookOperateV2_6_8_51() {

}

void WXEHookOperateV2_6_8_51::initHookOffset() {

}

void WXEHookOperateV2_6_8_51::hookGetQRCode(bool open) {
	WXEHookOperator<5> hookOperator;
	void (WXEHookOperateV2_6_8_51::*getQRCodeCallbackFun)() = &WXEHookOperateV2_6_8_51::getQRCodeCallback;
	hookGetQRCodeLock.lock();
	hookGetQRCodeItems = WXEHookItems<5>(winBaseAddress + 0x1F110B, winBaseAddress + 0x480040);
	if (open) {
		backupGetQRCode[0] = 0xE9;
		*(DWORD *)&backupGetQRCode[1] = *(DWORD *)&getQRCodeCallbackFun - hookGetQRCodeItems.hookAddress - 5;
	}
	WXEError result = hookOperator.execute(hookGetQRCodeItems.hookAddress, backupGetQRCode);
	hookGetQRCodeLock.unlock();
	openGetQRCode = (result == WXEErrorSuccess) && open;
}

void __declspec(naked)WXEHookOperateV2_6_8_51::getQRCodeCallback() {
	__asm {
		pushad
		pushfd
		push ecx
		call sendQRCodePNG
		popfd
		popad
		//call this+0xC
		call hookGetQRCodeItems.originCall
		//jmp
	}
}
