#include "stdafx.h"
#include "WXELoginOperateImpl.h"


WXELoginOperateV2_6_8_51::WXELoginOperateV2_6_8_51(DWORD address)
:WXELoginOperateSimple(address) {
	hookGetQRCodeItems = WXEHookItems<5>(address + 0x1F110B, address + 0x480040);
}

/*
void WXELoginOperateV2_6_8_51::getLoginInfo() const {

}

WXEError WXELoginOperateV2_6_8_51::getLoginQRCode(WXENetSceneCallback<WXEData> callBack) const{

	
	callBack(WXEErrorSuccess, WXEData(141414, 200));
	return WXEErrorSuccess;
}
*/