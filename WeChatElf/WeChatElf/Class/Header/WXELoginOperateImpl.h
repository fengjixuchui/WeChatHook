#pragma once
#include "WXELoginOperateBase.h"

class WXELoginOperateV2_6_8_51 : public WXELoginOperateSimple {

public:
	WXELoginOperateV2_6_8_51(DWORD address);

	WXEError getLoginQRCode(const WXENetSceneCallback<WXEData>& callback);
	/*
	void getLoginInfo() const override;
	void getLogoutInfo() const override;
	*/
};

