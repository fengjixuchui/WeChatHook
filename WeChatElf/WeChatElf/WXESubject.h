#pragma once

#include "WXESubjectImpl.h"

class WXESubject;

using WXEUserSubjectMap = std::map<DWORD, WXESubject>;

enum WXEError
{

};

class WXESubject {
public:
	WXESubject(const WXESubject& val);
	~WXESubject();
	static WXESubject& createSubject(DWORD address);

public:
	/*
	*	登陆操作
	*/
	std::wstring& getLoginQRCode() const;
	std::wstring& getLoginInfo() const;
	std::wstring& getLogoutInfo() const;

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
	void addFriends(std::vector<int>& friends) const;
	void deleteFriends(std::vector<int>& friends) const;
	void setStarMarkToFriends(std::vector<int>& friends) const;
	void cancelStarMarkToFriends(std::vector<int>& friends) const;
	void modifyFriendNotes(std::vector<int>& friends) const;
	void agreeFriendRequest(std::wstring& friends) const;
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
	void modifyRoomName()const;
	void setRoomAnnouncement() const;
	void modifyMyRoomNickName() const;
	void saveRoomToAddressBook() const;
	void removeRoomToAddressBook() const;

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
	void sendGifMessage()const;

	/*
	*	接收消息
	*/
	void openReceiveMessage() const;
	void stopReceiveMessage() const;
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
	WXESubject(DWORD address);

private:
	/*
	*  微信模块基址
	*/
	DWORD winBaseAddress;

private:
	/*
	*  类的真正实现对象
	*/
	std::unique_ptr<WXESubjectImpl> implementation;

private:
	/*
	* 用户与Subject的对应关系，通过User（DWORD）查找到对应的微信进程
	*/
	static DWORD userNumber;
	static WXEUserSubjectMap userMap;
	static std::mutex mutexLock;
};

