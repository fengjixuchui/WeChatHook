#pragma once

#include "WXECommon.h"

class WXEFriendOperateBase {
public:
	virtual ~WXEFriendOperateBase();

	virtual void sendFriendVerification(const std::wstring& wxid, const std::wstring& verifyText) const = 0;
	virtual void deleteFriends(const std::wstring& wxid) const = 0;
	virtual void setStarMarkToFriends(const std::wstring& wxid) const = 0;
	virtual void cancelStarMarkToFriends(const std::wstring& wxid) const = 0;
	virtual void modifyFriendNotes() const = 0;
	virtual void agreeToFriendRequest(const std::wstring& v1Str, const std::wstring& v2Str) const = 0;
	virtual void receiveFriendTransfer(const std::string& wxid, const std::string& transID) const = 0;
	virtual void agreeToRoomInvitaionOfFriend(const std::wstring& invitationLinks) const = 0;
};

class WXEFriendOperateSimple : public WXEFriendOperateBase {
protected:
	WXEFriendOperateSimple(DWORD address);
	virtual ~WXEFriendOperateSimple();

protected:
	WXEError hookReceiveTransfer(bool isOpen) const;

protected:
	DWORD winBaseAddress;
	WXEHookItems<5> hookReceiveTransferItems;
};

typedef struct _WXEFriendVerify {
	WXEUserID friendID;
	CHAR fill[0x10];
	WXEMessage verification;
	_WXEFriendVerify(const std::wstring& wxid, const std::wstring& verifyText) {
		friendID = WXEUserID(wxid);
		verification = WXEMessage(verifyText);
	}
} WXEFriendVerify;
