#pragma once
#include "WXEHookOperateBase.h"


class WXEHookOperateV2_6_8_51 : public WXEHookOperateSimple {

public:
	WXEHookOperateV2_6_8_51(DWORD address);
	virtual ~WXEHookOperateV2_6_8_51();

	/*
	void hookReceiveTransferResult() const;
	void hookReceiveMessage() const;
	void hookGetUserInfoFromNetwork() const;

	bool isOpenGetQRCode() const;
	bool isOpenReceiveTransferResult() const;
	bool isOpenReceiveMessage() const;
	bool isOpenGetUserInfoFromNetwork() const;
	*/

private:
	void initHookOffset() override;

};

