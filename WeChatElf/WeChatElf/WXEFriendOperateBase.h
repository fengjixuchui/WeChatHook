#pragma once

#include "WXECommon.h"

class WXEFriendOperateBase {
public:
	virtual ~WXEFriendOperateBase();

	virtual void addFriends(const std::wstring& wxid, const std::wstring& verifyText) const = 0;
	virtual void deleteFriends(const std::wstring& wxid) const = 0;
	virtual void setStarMarkToFriends(const std::wstring& wxid, bool isSet) const = 0;
	virtual void cancelStarMarkToFriends() const = 0;
	virtual void modifyFriendNotes() const = 0;
	virtual void agreeFriendRequest() const = 0;
	virtual void receiveFriendTransfer() const = 0;
	virtual void agreeRoomInvitaionOfFriend() const = 0;
};

class WXEFriendOperateSimple : public WXEFriendOperateBase {
protected:
	WXEFriendOperateSimple(DWORD address);
	virtual ~WXEFriendOperateSimple();

protected:
	WXEError hookReceiveTransfer(bool isOpen) const;

protected:
	WXEHookItems<5> hookReceiveTransferItems;

private:
	DWORD winBaseAddress;
	WXEHookOperator<5> hookOperator;
};

typedef struct _WXEFriendVerify {
	WXEUserID friendID;
	CHAR fill[0x10];
	WXEMessage verification;
	_WXEFriendVerify(const std::wstring& wxid, const std::wstring& verifyText)
	:friendID(wxid), verification(verifyText) { }
} WXEFriendVerify;
