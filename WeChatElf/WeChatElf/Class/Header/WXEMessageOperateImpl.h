#pragma once
#include "WXEMessageOperateBase.h"

class WXEMessageOperateV2_6_8_51 : public WXEMessageOperateSimple {
    
public:
    WXEMessageOperateV2_6_8_51(DWORD address);
    
private:
    void sendTextMessage(const std::wstring& recver, const std::wstring& content) const;
    void sendAtRoomMemberMessage(const std::wstring& room, const std::vector<WXEUserID>& atUsers, const std::wstring& content) const;
    void sendNameCardMessage(const std::wstring& recver, const std::wstring& sharedUser, const std::wstring& sharedUserNickName) const;
    void sendLinkMessage(const std::wstring& sender, const std::wstring& recver, const WXEPublicArticle& link) const;
    void sendPictureMessage(const std::wstring& recver, const std::wstring& path) const;
    void sendFileMessage(const std::wstring& recver, const std::wstring& path) const;
    void sendVideoMessage(const std::wstring& recver, const std::wstring& path) const;
    void sendGifMessage(const std::wstring& recver, const std::wstring& path) const;
    void preventWithdrawalMessage() const;
    
private:
    DWORD winBaseAddress;
};

