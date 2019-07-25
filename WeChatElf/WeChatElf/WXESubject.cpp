#include "stdafx.h"
#include "WXESubject.h"
#include "WXESubjectImpl.h"

WXESubject::WXESubject(WXEVersion version, DWORD address)
	: pImpl(std::make_unique<WXESubjectImpl>(version, address)) {

}

WXESubject::~WXESubject() {

}

// Login Module

void WXESubject::getLoginQRCode() const {
	pImpl->getLoginInfo();
}

void WXESubject::getLoginInfo() const {
	pImpl->getLoginInfo();
}

void WXESubject::getLogoutInfo() const {
	pImpl->getLogoutInfo();
}

// Base Info Module

void WXESubject::getInfoOfOwner() const {
	pImpl->getInfoOfOwner();
}

void WXESubject::getInfoOfFriends(std::vector<int>& friends) const {
	pImpl->getInfoOfFriends(friends);
}

void WXESubject::getInfoOfRoom(std::vector<int>& room) const {
	pImpl->getInfoOfRoom(room);
}

void WXESubject::getInfoOfRoomMember(std::vector<int>& members) const {
	pImpl->getInfoOfRoomMember(members);
}

void WXESubject::getInfoOfOfficialAccount(std::vector<int>& accounts) const {
	pImpl->getInfoOfOfficialAccount(accounts);
}

void WXESubject::getInfoOfOwnerFromNetwork() const {
	pImpl->getInfoOfOwnerFromNetwork();
}

void WXESubject::getInfoOfRoomMemberFromNetwork(std::vector<int>& members) const {
	pImpl->getInfoOfRoomMemberFromNetwork(members);
}

// Friend Module

void WXESubject::addFriends(std::vector<int>& friends) const {
	pImpl->addFriends(friends);
}

void WXESubject::deleteFriends(std::vector<int>& friends) const {
	pImpl->deleteFriends(friends);
}

void WXESubject::setStarMarkToFriends(std::vector<int>& friends) const {
	pImpl->setStarMarkToFriends(friends);
}

void WXESubject::cancelStarMarkToFriends(std::vector<int>& friends) const {
	pImpl->cancelStarMarkToFriends(friends);
}

void WXESubject::modifyFriendNotes(std::vector<int>& friends) const {
	pImpl->modifyFriendNotes(friends);
}

void WXESubject::agreeFriendRequest(std::wstring& friends) const {
	pImpl->agreeFriendRequest(friends);
}

void WXESubject::receiveFriendTransfer() const {
	pImpl->receiveFriendTransfer();
}

void WXESubject::agreeRoomInvitaionOfFriend() const {
	pImpl->agreeRoomInvitaionOfFriend();
}

// Room Module

void WXESubject::createChatRoom() const {
	pImpl->createChatRoom();
}

void WXESubject::deleteAndQuitChatRoom() const {
	pImpl->deleteAndQuitChatRoom();
}

void WXESubject::inviteFriendToJoinRoom() const {
	pImpl->inviteFriendToJoinRoom();
}

void WXESubject::inviteFriendToJoinRoomEx() const {
	pImpl->inviteFriendToJoinRoomEx();
}

void WXESubject::kickRoomMember() const {
	pImpl->kickRoomMember();
}

void WXESubject::modifyRoomName()const {
	pImpl->modifyRoomName();
}

void WXESubject::setRoomAnnouncement() const {
	pImpl->setRoomAnnouncement();
}

void WXESubject::modifyMyRoomNickName() const {
	pImpl->modifyMyRoomNickName();
}

void WXESubject::saveRoomToAddressBook() const {
	pImpl->saveRoomToAddressBook();
}

void WXESubject::removeRoomToAddressBook() const {
	pImpl->removeRoomToAddressBook();
}

// Message Module

void WXESubject::sendTextMessage() const {
	pImpl->sendTextMessage();
}

void WXESubject::sendAtRoomMemberMessage() const {
	pImpl->sendAtRoomMemberMessage();
}

void WXESubject::sendNameCardMessage() const {
	pImpl->sendNameCardMessage();
}

void WXESubject::sendLinkMessage() const {
	pImpl->sendLinkMessage();
}

void WXESubject::sendPictureMessage() const {
	pImpl->sendPictureMessage();
}

void WXESubject::sendFileMessage() const {
	pImpl->sendFileMessage();
}

void WXESubject::sendVideoMessage() const {
	pImpl->sendVideoMessage();
}

void WXESubject::sendGifMessage() const {
	pImpl->sendGifMessage();
}

void WXESubject::openReceiveMessage() const {
	pImpl->openReceiveMessage();
}

void WXESubject::stopReceiveMessage() const {
	pImpl->stopReceiveMessage();
}

void WXESubject::preventWithdrawalMessage() const {
	pImpl->preventWithdrawalMessage();
}

/*
 *   File Module
 */
void WXESubject::decodePictureMetadata() const {
	pImpl->decodePictureMetadata();
}

void WXESubject::forwardFileMessage() const {
	pImpl->forwardFileMessage();
}

/*
 *    Auto Module
 */
void WXESubject::autoDownloadFile() const {
	pImpl->autoDownloadFile();
}

void WXESubject::autoReceiveTransfer() const {
	pImpl->autoReceiveTransfer();
}

void WXESubject::autoAgreeRoomInvitaion() const {
	pImpl->autoAgreeRoomInvitaion();
}

void WXESubject::autoAgreeFriendInvitation() const {
	pImpl->autoAgreeFriendInvitation();
}

void WXESubject::autoAddSharedNameCard() const {
	pImpl->autoAddSharedNameCard();
}

/*
 *    Database Module
 */
void WXESubject::query() const {
	pImpl->query();
}
