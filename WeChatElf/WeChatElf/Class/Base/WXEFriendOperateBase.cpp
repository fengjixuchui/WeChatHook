#include "stdafx.h"
#include "WXEFriendOperateBase.h"

static bool openReceiveTransfer = false;
static std::array<BYTE, 5> backupReceiveTransferCode;
static WXEHookItems<5> globleHookReceiveTransferItems;
void receiveTransferCallback();
void disposeReceiveTransferResult(DWORD result);

WXEFriendOperateBase::~WXEFriendOperateBase() {

}

WXEFriendOperateSimple::WXEFriendOperateSimple(DWORD address)
:winBaseAddress(address) {

}

WXEFriendOperateSimple::~WXEFriendOperateSimple() {

}

WXEError WXEFriendOperateSimple::hookReceiveTransfer(bool isOpen) const {
	if (globleHookReceiveTransferItems.hookAddress == 0) {
		globleHookReceiveTransferItems = hookReceiveTransferItems;
		globleHookReceiveTransferItems.jumpCall = (DWORD)receiveTransferCallback;
		globleHookReceiveTransferItems.disposeCall = (DWORD)disposeReceiveTransferResult;
	}

	if (isOpen) {
		if (openReceiveTransfer) return WXEErrorSuccess; // If had open , return
		backupReceiveTransferCode[0] = 0xE9;
		*(DWORD *)&backupReceiveTransferCode[1] = globleHookReceiveTransferItems.jumpCall - globleHookReceiveTransferItems.hookAddress - 5;
	}

	WXEHookOperator<5> hookOperator;
	WXEError result = hookOperator.execute((LPCVOID)globleHookReceiveTransferItems.hookAddress, backupReceiveTransferCode);
	if (result == WXEErrorSuccess)
		openReceiveTransfer = isOpen;

	return WXEErrorSuccess;
}

void __declspec(naked) receiveTransferCallback() {
	__asm {
		pushad
		pushfd
		push ecx
		call globleHookReceiveTransferItems.disposeCall
		popfd
		popad
		call globleHookReceiveTransferItems.originCall
		jmp globleHookReceiveTransferItems.nextOrderAddress
	}
}

void disposeReceiveTransferResult(DWORD result) {

}
