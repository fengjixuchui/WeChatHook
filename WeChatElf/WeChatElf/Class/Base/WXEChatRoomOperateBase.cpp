#include "stdafx.h"
#include "WXEChatRoomOperateBase.h"

static bool openQueryMemberInfo = false;
static std::array<BYTE, 5> backupQueryMemberInfoCode;
static WXEHookItems<5> globleHookQueryMemberInfoItems;
void queryMemberInfoCallback();
void disposeQueryMemberInfoResult(DWORD result);

static bool openCreateRoomResult = false;
static std::array<BYTE, 5> backupCreateRoomResultCode;
static WXEHookItems<5> globleHookCreateRoomResultItems;
void createRoomResultCallback();
void disposeCreateRoomResult(DWORD result);

WXEChatRoomOperateBase::~WXEChatRoomOperateBase() {

}

WXEChatRoomOperateSimple::~WXEChatRoomOperateSimple() {

}

WXEChatRoomOperateSimple::WXEChatRoomOperateSimple(DWORD address)
:winBaseAddress(address),
hookOperator(WXEHookOperator<5>{ }) {
    
}

WXEError WXEChatRoomOperateSimple::hookCreateRoomResult(bool isOpen) const {
    if (globleHookCreateRoomResultItems.hookAddress == 0) {
        globleHookCreateRoomResultItems = hookCreateRoomResultItems;
        globleHookCreateRoomResultItems.jumpCall = (DWORD)createRoomResultCallback;
        globleHookCreateRoomResultItems.disposeCall = (DWORD)disposeCreateRoomResult;
    }
    
    if (isOpen) {
        if (openQueryMemberInfo) return WXEErrorSuccess; // If had open , return
        backupCreateRoomResultCode[0] = 0xE9;
        *(DWORD *)&backupCreateRoomResultCode[1] = globleHookCreateRoomResultItems.jumpCall - globleHookCreateRoomResultItems.hookAddress - 5;
    }
    
    WXEError result = hookOperator.execute((LPCVOID)globleHookCreateRoomResultItems.hookAddress, backupCreateRoomResultCode);
    if (result == WXEErrorSuccess)
		openCreateRoomResult = isOpen;
    
    return WXEErrorSuccess;
}

void __declspec(naked) createRoomResultCallback() {
    __asm {
        pushad
        pushfd
        push ecx
        call globleHookCreateRoomResultItems.disposeCall
        popfd
        popad
        call globleHookCreateRoomResultItems.originCall
        jmp globleHookCreateRoomResultItems.nextOrderAddress
    }
}

void disposeCreateRoomResult(DWORD result) {
    
}



WXEError WXEChatRoomOperateSimple::hookQueryMemberInfo(bool isOpen) const {
    if (globleHookQueryMemberInfoItems.hookAddress == 0) {
        globleHookQueryMemberInfoItems = hookQueryMemberInfoItems;
        globleHookQueryMemberInfoItems.jumpCall = (DWORD)queryMemberInfoCallback;
        globleHookQueryMemberInfoItems.disposeCall = (DWORD)disposeQueryMemberInfoResult;
    }
    
    if (isOpen) {
        if (openQueryMemberInfo) return WXEErrorSuccess; // If had open , return
        backupQueryMemberInfoCode[0] = 0xE9;
        *(DWORD *)&backupQueryMemberInfoCode[1] = globleHookQueryMemberInfoItems.jumpCall - globleHookQueryMemberInfoItems.hookAddress - 5;
    }
    
    WXEError result = hookOperator.execute((LPCVOID)globleHookQueryMemberInfoItems.hookAddress, backupQueryMemberInfoCode);
    if (result == WXEErrorSuccess)
        openQueryMemberInfo = isOpen;
    
    return WXEErrorSuccess;
}

void __declspec(naked) queryMemberInfoCallback() {
    __asm {
        pushad
        pushfd
        push ecx
        call globleHookQueryMemberInfoItems.disposeCall
        popfd
        popad
        call globleHookQueryMemberInfoItems.originCall
        jmp globleHookQueryMemberInfoItems.nextOrderAddress
    }
}

void disposeQueryMemberInfoResult(DWORD result) {
    
}

