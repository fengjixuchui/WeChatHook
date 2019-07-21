#pragma once
#include "WXELoginOperateBase.h"

class WXELoginOperateV2_6_8_51 : public WXELoginOperateBase {

public:
	WXELoginOperateV2_6_8_51(DWORD address);
	virtual ~WXELoginOperateV2_6_8_51();

	/*
	WXEError getLoginQRCode(WXENetSceneCallback<WXEData>) const override;
	void getLoginInfo() const override;
	void getLogoutInfo() const override;
	*/

private:
	DWORD winBaseAddress;
};

