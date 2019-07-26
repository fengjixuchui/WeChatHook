#pragma once

#include "WXECommon.h"

class WXELoginOperateBase {
public:
	virtual ~WXELoginOperateBase();

	//virtual WXEError getLoginQRCode(WXENetSceneCallback<WXEData> data) const = 0;
	//virtual void getLoginInfo() const = 0;
	//virtual void getLogoutInfo() const = 0;
};

// Simple implementation
class WXELoginOperateSimple : public WXELoginOperateBase {
public:
	WXELoginOperateSimple(DWORD address);

protected:
	virtual ~WXELoginOperateSimple();

private:
	virtual WXEError getLoginQRCode(WXENetSceneCallback<WXEData> data) const;
	//virtual void getLoginInfo();
	//virtual void getLogoutInfo();

	WXEError hookGetQRCode(bool open) const;

protected:
	WXEHookItems<5> hookGetQRCodeItems;

private:
	DWORD winBaseAddress;
	WXEHookOperator<5> hookOperator;
};

