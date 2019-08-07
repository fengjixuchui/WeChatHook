#include "stdafx.h"
#include "WXEMessageOperateBase.h"

static bool openReceiveMessage = false;
static std::array<BYTE, 5> backupReceiveMessageCode;
static WXEHookItems<5> globleHookReceiveMessageItems;
static WXESecurityStore<WXEUserID> store = { WXESecurityStore<WXEUserID>(false) };
void receiveMessage();
void disposeReceivedMessage(DWORD message);

WXEMessageOperateBase::~WXEMessageOperateBase() {
    
}

WXEMessageOperateSimple::WXEMessageOperateSimple(DWORD address)
:winBaseAddress(address) {
    
}

WXEError WXEMessageOperateSimple::addMessageSubscriber(WXESubscribeType type, const WXESubscriber& subscriber) {
	WXEError result = switchReceiveMessage(true);
	if (result == WXEErrorSuccess) {
		subscribers[type] = subscriber;
	}
	return result;
}

void WXEMessageOperateSimple::removeMessageSubscriber(WXESubscribeType type) {

}

WXEError WXEMessageOperateSimple::switchReceiveMessage(bool isOpen) const {
    if (globleHookReceiveMessageItems.hookAddress == 0) {
        globleHookReceiveMessageItems = hookReceiveMessageItems;
        globleHookReceiveMessageItems.jumpCall = (DWORD)receiveMessage;
        globleHookReceiveMessageItems.disposeCall = (DWORD)disposeReceivedMessage;
    }
    if (isOpen) {
        if (openReceiveMessage)  return WXEErrorSuccess;
        backupReceiveMessageCode[0] = 0xE9;
        *(DWORD *)&backupReceiveMessageCode[1] = globleHookReceiveMessageItems.jumpCall - globleHookReceiveMessageItems.hookAddress - 5;
    }
    WXEHookOperator<5> hookOperator;
    WXEError result = hookOperator.execute((LPCVOID)globleHookReceiveMessageItems.hookAddress, backupReceiveMessageCode);
    if (result == WXEErrorSuccess)
        openReceiveMessage = isOpen;
    return result;
}

void __declspec(naked)receiveMessage() {
    __asm {
        pushad
        pushfd
        push ecx
        call globleHookReceiveMessageItems.disposeCall
        popfd
        popad
        call globleHookReceiveMessageItems.originCall
        jmp globleHookReceiveMessageItems.nextOrderAddress
    }
}

void disposeReceivedMessage(DWORD message) {
	// get message type == ...
	// for_each subscribers, and send message to subscriber
}
