#include "stdafx.h"
#include "WXEHookOperateV2_6_8_51.h"

extern WXEHookItems<5> hookGetQRCodeItems;

WXEHookOperateV2_6_8_51::WXEHookOperateV2_6_8_51(DWORD address)
:WXEHookOperateSimple(address) {
	initHookOffset();
}


WXEHookOperateV2_6_8_51::~WXEHookOperateV2_6_8_51() {

}

void WXEHookOperateV2_6_8_51::initHookOffset() {
	hookGetQRCodeItems = WXEHookItems<5>(winBaseAddress + 0x1F110B, winBaseAddress + 0x480040);
}


