#include "stdafx.h"
#include "WXEHookOperateBase.h"

WXEHookOperateBase::~WXEHookOperateBase() {

}


std::mutex WXEHookOperateSimple::hookGetQRCodeLock;

WXEHookOperateSimple::WXEHookOperateSimple(DWORD address)
:winBaseAddress(address) {
	
}

bool WXEHookOperateSimple::isOpenGetQRCode() const {
	return openGetQRCode;
}

void WXEHookOperateSimple::sendQRCodePNG(DWORD *pngHeaderPtr) const {
	//WXEData pngData = WXEData(*pngHeaderPtr, *(pngHeaderPtr + 0x4));
}

