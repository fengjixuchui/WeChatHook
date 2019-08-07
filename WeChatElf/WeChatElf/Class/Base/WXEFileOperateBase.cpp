#include "stdafx.h"
#include "WXEFileOperateBase.h"

static bool openAutoDownload = false;
static std::array<BYTE, 2> backupAutoDownloadCode;
static WXEHookItems<2> globleHookAutoDownloadItems;

static bool openHookSaveFile = false;
static std::array<BYTE, 5> backupSaveFileCode;
static WXEHookItems<5> globleHookSaveFileItems;
static WXESecurityStore<WXEUserID> store = { WXESecurityStore<WXEUserID>(false) };
static void saveFile();
static void disposeFile(DWORD fileData);

WXEFileOperateBase::~WXEFileOperateBase() {

}

WXEFileOperateSimple::WXEFileOperateSimple(DWORD address)
:winBaseAddress(address) {
    
}

WXEError WXEFileOperateSimple::switchAutoDownloadFile(bool isOpen) const {
    if (globleHookAutoDownloadItems.hookAddress == 0) {
        globleHookAutoDownloadItems = hookAutoDownloadItems;
    }
    if (isOpen) {
        if (openAutoDownload) return WXEErrorSuccess;
        backupAutoDownloadCode[0] = 0xE9;
        backupAutoDownloadCode[0] = 0xA6;
    }
    WXEHookOperator<2> hookOperator;
    WXEError result = hookOperator.execute((LPCVOID)globleHookAutoDownloadItems.hookAddress, backupAutoDownloadCode);
    if (result == WXEErrorSuccess)
        openAutoDownload = isOpen;
    return result;
}

WXEError WXEFileOperateSimple::hookSaveFile(bool isOpen) const {
    if (globleHookSaveFileItems.hookAddress == 0) {
        globleHookSaveFileItems = hookSaveFileItems;
        globleHookSaveFileItems.jumpCall = (DWORD)saveFile;
        globleHookSaveFileItems.disposeCall = (DWORD)disposeFile;
    }
    if (isOpen) {
        if(openHookSaveFile) return WXEErrorSuccess;
        backupSaveFileCode[0] = 0xE9;
        *(DWORD *)&backupSaveFileCode[1] = globleHookSaveFileItems.jumpCall - globleHookSaveFileItems.hookAddress - 5;
    }
    WXEHookOperator<5> hookOperator;
    WXEError result = hookOperator.execute((LPCVOID)globleHookSaveFileItems.hookAddress, backupSaveFileCode);
    if (result == WXEErrorSuccess)
        openHookSaveFile = isOpen;
    return result;
}

void __declspec(naked)saveFile() {
    __asm {
        pushad
        pushfd
        push ecx
        call globleHookSaveFileItems.disposeCall
        popfd
        popad
        call globleHookSaveFileItems.originCall
        jmp globleHookSaveFileItems.nextOrderAddress
    }
}

void disposeFile(DWORD message) {

}
