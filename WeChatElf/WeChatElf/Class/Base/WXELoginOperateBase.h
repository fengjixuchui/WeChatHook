#pragma once

#include "WXECommon.h"

class WXELoginOperateBase {
public:
	virtual ~WXELoginOperateBase();

	virtual WXEError getLoginQRCode(const WXENetSceneCallback<WXEData>& callback) = 0;
	//virtual void getLoginInfo() const = 0;
	//virtual void getLogoutInfo() const = 0;
};

// Simple implementation
class WXELoginOperateSimple : public WXELoginOperateBase {
protected:
	WXELoginOperateSimple(DWORD address);
	virtual ~WXELoginOperateSimple();

	WXEError hookGetQRCode(bool open);

private:
	//virtual void getLoginInfo();
	//virtual void getLogoutInfo();

protected:
	DWORD winBaseAddress;
	WXEHookItems<5> hookGetQRCodeItems;
	std::shared_ptr<WXESecurityStore<WXEData>> dataStore;
};


extern std::mutex mutex;
extern std::condition_variable condVar;
extern WXESecurityStore<WXENetSceneCallback<WXEData>> QRCodeStore;
