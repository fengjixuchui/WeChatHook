#pragma once

#include "WXECommon.h"

class WXELoginOperateBase;
class WXEChatRoomOperateBase;
class WXEMessageOperateBase;
class WXEFileOperateBase;
class WXEFriendOperateBase;

class WXESubjectImpl {
public:
	WXESubjectImpl(WXEVersion version, DWORD address);

public:
	/*
	 *    µ«¬Ω≤Ÿ◊˜
	 */
	void getLoginQRCode() const;
	void getLoginInfo() const;
	void getLogoutInfo() const;

	/*
	 *    ªÒ»°”√ªß–≈œ¢
	 */
	void getInfoOfOwner() const;
	void getInfoOfFriends(std::vector<int>& friends) const;
	void getInfoOfRoom(std::vector<int>& room) const;
	void getInfoOfRoomMember(std::vector<int>& members) const;
	void getInfoOfOfficialAccount(std::vector<int>& accounts) const;
	void getInfoOfOwnerFromNetwork() const;
	void getInfoOfRoomMemberFromNetwork(std::vector<int>& members) const;

	/*
	 *    ∫√”—≤Ÿ◊˜
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
	 *    »∫≤Ÿ◊˜
	 */
	void createChatRoom() const;
	void deleteAndQuitChatRoom() const;
	void inviteFriendToJoinRoom() const;  //÷±Ω”¿≠Ω¯»∫
	void inviteFriendToJoinRoomEx() const; //–Ë“™∫√”—Õ¨“‚
	void kickRoomMember() const;
	void modifyRoomName() const;
	void setRoomAnnouncement() const;
	void modifyMyRoomNickName() const;
	void saveRoomToAddressBook() const;
	void removeRoomToAddressBook() const;
	void addFriendsFromRoom() const;

	/*
	 *    ∑¢ÀÕœ˚œ¢
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
	 *    Œƒº˛≤Ÿ◊˜
	 */
	void decodePictureMetadata() const;
	void forwardFileMessage() const;

	/*
	 *    ◊‘∂Ø≤Ÿ◊˜
	 */
	void autoDownloadFile() const;
	void autoReceiveTransfer() const;
	void autoAgreeRoomInvitaion() const;
	void autoAgreeFriendInvitation() const;
	void autoAddSharedNameCard() const;

	/*
	 *     ˝æ›ø‚≤Ÿ◊˜
	 */
	void query() const;

private:
	DWORD winBaseAddress;

	std::shared_ptr<WXELoginOperateBase> loginModule;
	std::shared_ptr<WXEChatRoomOperateBase> groupModule;
	std::shared_ptr<WXEMessageOperateBase> messageModule;
	std::shared_ptr<WXEFileOperateBase> fileModule;
	std::shared_ptr<WXEFriendOperateBase> friendModule;
};
