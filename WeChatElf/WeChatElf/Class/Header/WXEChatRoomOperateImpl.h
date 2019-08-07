#pragma once
#include "WXEChatRoomOperateBase.h"

class WXEChatRoomOperateV2_6_8_51 : public WXEChatRoomOperateSimple {
public:
	WXEChatRoomOperateV2_6_8_51(DWORD address);
    
private:
    void createChatRoom(const std::vector<WXEUserID>& users, const WXENetSceneCallback<WXEData>& callback = NULL) const;
    void deleteAndQuitChatRoom(const std::wstring& room) const;
    void inviteFriendToJoinRoom(const std::wstring& , const std::vector<WXEUserID>&) const;
    void inviteFriendToJoinRoomEx(const std::wstring& , const std::vector<WXEUserID>&) const;
    void kickRoomMember(const std::wstring& room, const std::vector<WXEUserID>& users) const;
    void modifyRoomName(const std::wstring& room, const std::wstring& text) const;
    void setRoomAnnouncement(const std::wstring& room, const std::wstring& text) const;
    void modifyMyRoomNickName() const;
    void saveRoomToAddressBook() const;
    void removeRoomToAddressBook() const;
	void addFriendsFromRoom(const std::wstring& room, const std::wstring& user) const;
};

