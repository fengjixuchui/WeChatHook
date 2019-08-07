#pragma once

#include "WXECommon.h"

class WXEChatRoomOperateBase {
public:
	virtual ~WXEChatRoomOperateBase();
    
    virtual void createChatRoom(const std::vector<WXEUserID>& users, const WXENetSceneCallback<WXEData>& callback = NULL) const = 0;
    virtual void deleteAndQuitChatRoom(const std::wstring& room) const = 0;
    virtual void inviteFriendToJoinRoom(const std::wstring& , const std::vector<WXEUserID>&) const = 0;
    virtual void inviteFriendToJoinRoomEx(const std::wstring& , const std::vector<WXEUserID>&) const = 0;
    virtual void kickRoomMember(const std::wstring& room, const std::vector<WXEUserID>& users) const = 0;
    virtual void modifyRoomName(const std::wstring& room, const std::wstring& name) const = 0;
    virtual void setRoomAnnouncement(const std::wstring& room, const std::wstring& text) const = 0;
//    virtual void modifyMyRoomNickName() const = 0;
//    virtual void saveRoomToAddressBook() const = 0;
 //   virtual void removeRoomToAddressBook() const = 0;
    virtual void addFriendsFromRoom(const std::wstring& room, const std::wstring& user) const = 0;
};

class WXEChatRoomOperateSimple : public WXEChatRoomOperateBase {
protected:
    WXEChatRoomOperateSimple(DWORD address);
    virtual ~WXEChatRoomOperateSimple();
    
protected:
    WXEError hookQueryMemberInfo(bool isOpen) const;
    WXEError hookCreateRoomResult(bool isOpen) const;
    
protected:
    DWORD winBaseAddress;
    
    WXEHookItems<5> hookQueryMemberInfoItems;
    WXEHookItems<5> hookCreateRoomResultItems;
    
private:
    WXEHookOperator<5> hookOperator;
};

