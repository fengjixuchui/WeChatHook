#pragma once
#include "WXEHookOperateBase.h"


class WXEHookOperateV2_6_8_51 : public WXEHookOperateSimple {

public:
	WXEHookOperateV2_6_8_51(DWORD address);
	virtual ~WXEHookOperateV2_6_8_51();

	//void sendQRCodePNG(DWORD *pngHeaderPtr) const;
	/*
	void hookReceiveTransferResult() const;
	void hookReceiveMessage() const;
	void hookGetUserInfoFromNetwork() const;

	bool isOpenGetQRCode() const;
	bool isOpenReceiveTransferResult() const;
	bool isOpenReceiveMessage() const;
	bool isOpenGetUserInfoFromNetwork() const;
	*/

protected:
	void initHookOffset() override;

private:
	void hookGetQRCode(bool open);
	void getQRCodeCallback();
};

