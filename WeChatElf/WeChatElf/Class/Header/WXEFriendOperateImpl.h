#pragma once

#include "WXEFriendOperateBase.h"

typedef struct __WXEUserV1 {
	DWORD fill;
	WCHAR *v1;
	DWORD length;
	DWORD maxLength;
	CHAR fillEx[0x41c];
	DWORD v2Address;
	__WXEUserV1(const std::wstring& v1Str, DWORD pV2) {
		memset(this, 0, sizeof(WXEUserV1));
		v1 = (WCHAR *)v1Str.c_str();
		length = v1Str.length();
		maxLength = length * 2;
		v2Address = pV2;
	}
} WXEUserV1;

typedef struct __WXEUserV2 {
	CHAR fill[0x24c];
	DWORD val;
	CHAR fillEx[0x40];
	WCHAR *v2;
	DWORD length;
	DWORD maxLength;
	CHAR fillEx2[0x8];
	__WXEUserV2(const std::wstring& v2Str) {
		memset(this, 0, sizeof(WXEUserV2));
		v2 = (WCHAR *)v2Str.c_str();
		length = v2Str.length();
		maxLength = length * 2;
		val = 0x25;
	}
} WXEUserV2;

class WXEFriendOperateV2_6_8_51 : public WXEFriendOperateSimple {
public:
	WXEFriendOperateV2_6_8_51(DWORD address);

private:
	void sendFriendVerification(const std::wstring& wxid, const std::wstring& verifyText) const;
	void deleteFriends(const std::wstring& wxid) const;
	void setStarMarkToFriends(const std::wstring& wxid) const;
	void cancelStarMarkToFriends(const std::wstring& wxid) const;
	void modifyFriendNotes() const;
	void agreeToFriendRequest(const std::wstring& v1Str, const std::wstring& v2Str) const;
	void receiveFriendTransfer(const std::string& wxid, const std::string& transID) const;
	void agreeToRoomInvitaionOfFriend(const std::wstring& invitationLinks) const;
	void friendCommonOperate(const std::wstring& wxid, DWORD opCode) const;
};

