#pragma once

#include <vector>

class WXEFriendOperateBase
{
public:
	WXEFriendOperateBase();
	virtual ~WXEFriendOperateBase();

	virtual void addFriends(std::vector<int>& friends) const = 0;
	virtual void deleteFriends(std::vector<int>& friends) const = 0;
	virtual void setStarMarkToFriends(std::vector<int>& friends) const = 0;
	virtual void cancelStarMarkToFriends(std::vector<int>& friends) const = 0;
	virtual void modifyFriendNotes(std::vector<int>& friends) const = 0;
	virtual void agreeFriendRequest(std::wstring& friends) const = 0;
	virtual void receiveFriendTransfer() const = 0;
	virtual void agreeRoomInvitaionOfFriend() const = 0;
};

