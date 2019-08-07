#pragma once

#include "WXECommon.h"

class WXESubjectImpl;

class WXESubject {
public:
	WXESubject(WXEVersion version, DWORD address);
	~WXESubject();

public:
	/*
	*	登陆操作
	*/
	void getLoginQRCode() const;
	void getLoginInfo() const;
	void getLogoutInfo() const;

	/*
	*	获取用户信息
	*/
	void getInfoOfOwner() const;
	void getInfoOfFriends(std::vector<int>& friends) const;
	void getInfoOfRoom(std::vector<int>& room) const;
	void getInfoOfRoomMember(std::vector<int>& members) const;
	void getInfoOfOfficialAccount(std::vector<int>& accounts) const;
	void getInfoOfOwnerFromNetwork() const;
	void getInfoOfRoomMemberFromNetwork(std::vector<int>& members) const;

	/*
	*	好友操作
	*/
	void sendFriendVerification(const std::wstring& wxid, const std::wstring& verifyText) const;
	void deleteFriends(std::vector<int>& friends) const;
	void setStarMarkToFriends(std::vector<int>& friends) const;
	void cancelStarMarkToFriends(std::vector<int>& friends) const;
	void modifyFriendNotes(std::vector<int>& friends) const;
	void agreeFriendRequest(const std::wstring& v1Str, const std::wstring& v2Str) const;
	void receiveFriendTransfer() const;
	void agreeRoomInvitaionOfFriend() const;

	/*
	*	群操作
	*/
	void createChatRoom() const;
	void deleteAndQuitChatRoom() const;
	void inviteFriendToJoinRoom() const;  //直接拉进群
	void inviteFriendToJoinRoomEx() const; //需要好友同意
	void kickRoomMember() const;
	void modifyRoomName() const;
	void setRoomAnnouncement() const;
	void modifyMyRoomNickName() const;
	void saveRoomToAddressBook() const;
	void removeRoomToAddressBook() const;
	void addFriendsFromRoom() const;

	/*
	*	发送消息
	*/
	void sendTextMessage() const;
	void sendAtRoomMemberMessage() const;
	void sendNameCardMessage() const;
	void sendLinkMessage() const;
	void sendPictureMessage() const;
	void sendFileMessage() const;
	void sendVideoMessage() const;
	void sendGifMessage() const;
	void switchReceiveMessage(bool isOpen) const;
	void preventWithdrawalMessage() const;

	/*
	*	文件操作
	*/
	void decodePictureMetadata() const;
	void forwardFileMessage() const;

	/*
	*	自动操作
	*/
	void autoDownloadFile() const;
	void autoReceiveTransfer() const;
	void autoAgreeRoomInvitaion() const;
	void autoAgreeFriendInvitation() const;
	void autoAddSharedNameCard() const;

	/*
	*	数据库操作
	*/
	void query() const;

private:
	/*
	*  类的真正实现对象
	*/
	std::shared_ptr<WXESubjectImpl> pImpl;
};

