#include "stdafx.h"
#include "WXESubjectImpl.h"
#include "WXELoginOperateImpl.h"
#include "WXEChatRoomOperateImpl.h"
#include "WXEMessageOperateImpl.h"
#include "WXEFriendOperateImpl.h"
#include "WXEFileOperateImpl.h"

WXESubjectImpl::WXESubjectImpl(WXEVersion version, DWORD address)
	: winBaseAddress(address) {
	if (version == WXEVersion_2_6_8_51) {
		loginModule = std::make_shared<WXELoginOperateV2_6_8_51>(address);
		groupModule = std::make_shared<WXEChatRoomOperateV2_6_8_51>(address);
		friendModule = std::make_shared<WXEFriendOperateV2_6_8_51>(address);
		fileModule = std::make_shared<WXEFileOperateV2_6_8_51>(address);
		messageModule = std::make_shared<WXEMessageOperateV2_6_8_51>(address);
	}
}

void WXESubjectImpl::getLoginQRCode() const {
	WXENetSceneCallback<WXEData> callback = [](WXEError error, WXEData data) {
		printf("\n");
	};
	loginModule->getLoginQRCode(callback);
}

void WXESubjectImpl::getLoginInfo() const {

}

void WXESubjectImpl::getLogoutInfo() const {

}

void WXESubjectImpl::getInfoOfOwner() const {

}

void WXESubjectImpl::getInfoOfFriends(std::vector<int>& friends) const {

}

void WXESubjectImpl::getInfoOfRoom(std::vector<int>& room) const {

}

void WXESubjectImpl::getInfoOfRoomMember(std::vector<int>& members) const {

}

void WXESubjectImpl::getInfoOfOfficialAccount(std::vector<int>& accounts) const {

}

void WXESubjectImpl::getInfoOfOwnerFromNetwork() const {

}

void WXESubjectImpl::getInfoOfRoomMemberFromNetwork(std::vector<int>& members) const {

}


/*
 *    ∫√”—≤Ÿ◊˜
 */
void WXESubjectImpl::sendFriendVerification(const std::wstring& wxid, const std::wstring& verifyText) const {
	friendModule->sendFriendVerification(wxid, verifyText);
}

void WXESubjectImpl::deleteFriends(std::vector<int>& friends) const {

}

void WXESubjectImpl::setStarMarkToFriends(std::vector<int>& friends) const {

}

void WXESubjectImpl::cancelStarMarkToFriends(std::vector<int>& friends) const {

}

void WXESubjectImpl::modifyFriendNotes(std::vector<int>& friends) const {

}

void WXESubjectImpl::agreeFriendRequest(const std::wstring& v1Str, const std::wstring& v2Str) const {
	friendModule->agreeToFriendRequest(v1Str, v2Str);
}

void WXESubjectImpl::receiveFriendTransfer() const {

}

void WXESubjectImpl::agreeRoomInvitaionOfFriend() const {

}

/*
 *    »∫≤Ÿ◊˜
 */
void WXESubjectImpl::createChatRoom() const {
	WXEUserID user1 = WXEUserID(L"wxid_ssxmbzolaz3u12");
	WXEUserID user2 = WXEUserID(L"penglovenan2012");
	std::vector<WXEUserID> users = { user1, user2 };
	groupModule->createChatRoom(users);
}

void WXESubjectImpl::deleteAndQuitChatRoom() const {

}

void WXESubjectImpl::inviteFriendToJoinRoom() const {

}

void WXESubjectImpl::inviteFriendToJoinRoomEx() const {

}

void WXESubjectImpl::kickRoomMember() const {

}

void WXESubjectImpl::modifyRoomName() const {

}

void WXESubjectImpl::setRoomAnnouncement() const {

}

void WXESubjectImpl::modifyMyRoomNickName() const {

}

void WXESubjectImpl::saveRoomToAddressBook() const {

}

void WXESubjectImpl::removeRoomToAddressBook() const {

}

void WXESubjectImpl::addFriendsFromRoom() const {

}

/*
 *    ∑¢ÀÕœ˚œ¢
 */
void WXESubjectImpl::sendTextMessage() const {

}

void WXESubjectImpl::sendAtRoomMemberMessage() const {

}

void WXESubjectImpl::sendNameCardMessage() const {

}

void WXESubjectImpl::sendLinkMessage() const {

}

void WXESubjectImpl::sendPictureMessage() const {

}

void WXESubjectImpl::sendFileMessage() const {

}

void WXESubjectImpl::sendVideoMessage() const {

}

void WXESubjectImpl::sendGifMessage() const {

}

void WXESubjectImpl::switchReceiveMessage(bool isOpen) const {

}

void WXESubjectImpl::preventWithdrawalMessage() const {

}

/*
 *    Œƒº˛≤Ÿ◊˜
 */
void WXESubjectImpl::decodePictureMetadata() const {

}

void WXESubjectImpl::forwardFileMessage() const {

}

/*
 *    ◊‘∂Ø≤Ÿ◊˜
 */
void WXESubjectImpl::autoDownloadFile() const {
	messageModule->addMessageSubscriber(WXESubscribeFile, [](WXEMessage file) {
		// dispose file
	});
}

void WXESubjectImpl::autoReceiveTransfer() const {
	const std::weak_ptr<WXEFriendOperateBase> weakrefFriendModule(friendModule);
	messageModule->addMessageSubscriber(WXESubscribeTransfer, [weakrefFriendModule](WXEMessage file) {
		auto strongrefFriendModule = weakrefFriendModule.lock();
		//strongrefFriendModule->receiveFriendTransfer();
	});
}

void WXESubjectImpl::autoAgreeRoomInvitaion() const {

}

void WXESubjectImpl::autoAgreeFriendInvitation() const {

}

void WXESubjectImpl::autoAddSharedNameCard() const {

}

/*
 *     ˝æ›ø‚≤Ÿ◊˜
 */
void WXESubjectImpl::query() const {

}
