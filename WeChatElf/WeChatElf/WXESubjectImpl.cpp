#include "stdafx.h"
#include "WXESubjectImpl.h"
#include "WXELoginOperateImpl.h"

WXESubjectImpl::WXESubjectImpl(WXEVersion version, DWORD address)
	: winBaseAddress(address) {
	if (version == WXEVersion_2_6_8_51) {
		loginModule = std::make_shared<WXELoginOperateV2_6_8_51>(address);
	}
}

void WXESubjectImpl::getLoginQRCode() const {

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
void WXESubjectImpl::addFriends(std::vector<int>& friends) const {

}

void WXESubjectImpl::deleteFriends(std::vector<int>& friends) const {

}

void WXESubjectImpl::setStarMarkToFriends(std::vector<int>& friends) const {

}

void WXESubjectImpl::cancelStarMarkToFriends(std::vector<int>& friends) const {

}

void WXESubjectImpl::modifyFriendNotes(std::vector<int>& friends) const {

}

void WXESubjectImpl::agreeFriendRequest(std::wstring& friends) const {

}

void WXESubjectImpl::receiveFriendTransfer() const {

}

void WXESubjectImpl::agreeRoomInvitaionOfFriend() const {

}

/*
 *    »∫≤Ÿ◊˜
 */
void WXESubjectImpl::createChatRoom() const {

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

/*
 *    Ω” ’œ˚œ¢
 */
void WXESubjectImpl::openReceiveMessage() const {

}

void WXESubjectImpl::stopReceiveMessage() const {

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

}

void WXESubjectImpl::autoReceiveTransfer() const {

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
