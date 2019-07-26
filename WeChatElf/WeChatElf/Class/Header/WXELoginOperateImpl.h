#pragma once
#include "WXELoginOperateBase.h"

class WXELoginOperateV2_6_8_51 : public WXELoginOperateSimple {

public:
	WXELoginOperateV2_6_8_51(DWORD address);

	/*
	WXEError getLoginQRCode(WXENetSceneCallback<WXEData>) const override;
	void getLoginInfo() const override;
	void getLogoutInfo() const override;
	*/
};

