#include "stdafx.h"
#include "WXEMessageOperateImpl.h"

WXEMessageOperateV2_6_8_51::WXEMessageOperateV2_6_8_51(DWORD address)
:WXEMessageOperateSimple(address) {
    hookReceiveMessageItems = WXEHookItems<5>(address+0x1F110B, address+0x480040);
}

void WXEMessageOperateV2_6_8_51::sendTextMessage(const std::wstring& recver, const std::wstring& content) const {
    WXEUserID recverID(recver);
    WXEMessage text(content);
    DWORD sendCall = winBaseAddress + 0x2EB4E0;
    char buff[0x81C] = { 0 };
    __asm {
        pushad
            lea edx, recverID
            lea ebx, text
            mov eax, 0x0
            push 0x1
            push eax
            push ebx
            lea ecx, buff
            call sendCall
            add esp, 0xC
        popad
    }
}

void WXEMessageOperateV2_6_8_51::sendAtRoomMemberMessage(const std::wstring& room, const std::vector<WXEUserID>& atUsers, const std::wstring& content) const {
    DWORD sendCall = winBaseAddress + 0x2EB4E0;
    WXEUserID roomID(room);
    WXEMessage text(content);
    WXEUserArray userArray = WXEUserArray((DWORD)&atUsers[0]);
    
    char buff[0x81C] = { 0 };
    __asm {
        pushad
            lea edx, roomID
            lea ebx, text
            lea eax, userArray
            push 0x1
            push eax
            push ebx
            lea ecx, buff
            call sendCall
            add esp, 0xC
        popad
    }
}

void WXEMessageOperateV2_6_8_51::sendNameCardMessage(const std::wstring& recver, const std::wstring& sharedUser, const std::wstring& sharedUserNickName) const {
    WCHAR cardXml[0x400] = { 0 };
    swprintf_s(cardXml, WXENameCardXmlTemplate, sharedUser.c_str(), sharedUserNickName.c_str());
    
    WXEUserID recverID(recver);
    WXEMessage cardMsg(cardXml);
    
    DWORD sendXmlCall = winBaseAddress + 0x2EB4E0;
    CHAR buff[0x20C] = { 0 };
    __asm {
        pushad
            push 0x2A
            lea esi, recverID
            lea eax, cardMsg
            lea edx, recverID
            push 0x0
            push eax
            lea ecx, buff
            call sendXmlCall
            add esp, 0xC
        popad
    }
}

void WXEMessageOperateV2_6_8_51::sendLinkMessage(const std::wstring& sender, const std::wstring& recver, const WXEPublicArticle& link) const {
    
    WCHAR articleXml[0x1000] = { 0 };
    link.combineXml(articleXml, 0x1000);
    WXEUserID senderID(sender);
    WXEUserID recverID(recver);
    WXEMessage articalMsg(articleXml);
    
    DWORD sendCall = winBaseAddress + 0x237AE0;
    DWORD paramAddress = winBaseAddress + 0x1277570;
    DWORD nextCall = winBaseAddress + 0x237CF0;
    
    WCHAR buff[0x2D8] = { 0 };
    __asm {
        pushad
            push 0x5
            lea eax, buff[0x250]
            push eax
            lea eax, buff[0x23C]
            //lea eax, icon   //可设置缩略图
            push eax
            lea eax, articalMsg
            push eax
            lea ebx, recverID
            push ebx
            lea eax, senderID
            push eax
            lea eax, buff
            push eax
            call sendCall
            push paramAddress
            push paramAddress
            lea eax, buff[0x2A4]
            mov eax, [eax]
            push eax
            lea eax, buff
            push eax
            call nextCall
        popad
        
    }
}

void WXEMessageOperateV2_6_8_51::sendPictureMessage(const std::wstring& recver, const std::wstring& path) const {
    DWORD sendCall1 = winBaseAddress + 0x817F0;
    DWORD sendCall2 = winBaseAddress + 0x2EAED0;
    
    WXEUserID recverID(recver);
    WXEMessage picture(path);
    
    CHAR buff[0x45c] = { 0 };
    __asm {
        pushad
            lea ebx, picture
            push ebx
            lea eax, recverID
            push eax
            lea eax, buff
            push eax
            mov ecx, 0x0
            push ecx
            call sendCall1
            add esp, 0x4
            mov ecx, eax
            call sendCall2
            //free image
        popad
    }
}

void WXEMessageOperateV2_6_8_51::sendFileMessage(const std::wstring& recver, const std::wstring& path) const {
    WXEUserID recverID(recver);
    WXELocalFile file(path);
    
    DWORD paramCall = winBaseAddress + 0x10A7C04;
    DWORD callAddress0 = winBaseAddress + 0x4818C0;
    DWORD callAddress1 = winBaseAddress + 0x481900;
    DWORD callAddress2 = winBaseAddress + 0x6BAC0;
    DWORD callAddress3 = winBaseAddress + 0x237DF0;
    
    CHAR buff[0x45C] = { 0 };
    __asm {
        pushad
            push 0x0
            sub esp, 0x14
            mov ecx, esp
            push -0x1
            push paramCall
            call callAddress0
            sub esp, 0x14
            mov ecx, esp
            lea ebx, file
            push ebx
            call callAddress1
            sub esp, 0x14
            mov ecx, esp
            lea eax, recverID
            push eax
            call callAddress1
            lea eax, buff
            push eax
            call callAddress2
            mov ecx, eax
            call callAddress3
        popad
    }
}

void WXEMessageOperateV2_6_8_51::sendVideoMessage(const std::wstring& recver, const std::wstring& path) const {
    
}

void WXEMessageOperateV2_6_8_51::sendGifMessage(const std::wstring& recver, const std::wstring& path) const {
    WXEUserID recverID(recver);
    WXELocalFile gif(path);
    
    DWORD paramCall = winBaseAddress + 0x10A7C04;
    DWORD callAddress0 = winBaseAddress + 0x48DF60;
    DWORD callAddress1 = winBaseAddress + 0x481A10;
    DWORD callAddress2 = winBaseAddress + 0x592D0;
    DWORD callAddress3 = winBaseAddress + 0x481900;
    DWORD callAddress4 = winBaseAddress + 0x4818C0;
    DWORD callAddress5 = winBaseAddress + 0x6BAC0;
    DWORD callAddress6 = winBaseAddress + 0x238B40;
    
    char buff[0x45C] = { 0 };
    __asm {
        pushad
            lea edi, recverID
            lea eax, gif
            mov eax, [eax]
            mov edx, eax
            lea ecx, buff[0x430]
            call callAddress0
            push 0x0
            push eax
            lea ecx, buff[0x3e4]
            call callAddress1
            lea ecx, buff[0x430]
            call callAddress2
            sub esp, 0x14
            lea eax, buff[0x3e4]
            mov ecx, esp
            push eax
            call callAddress3
            sub esp, 0x14
            mov ecx, esp
            push -0x1
            push paramCall
            call callAddress4
            sub esp, 0x14
            mov ecx, esp
            lea ebx, gif
            push ebx
            call callAddress3
            sub esp, 0x14
            mov ecx, esp
            push edi
            call callAddress3
            lea eax, buff
            push eax
            call callAddress5
            mov ecx, eax
            call callAddress6
        popad
    }
}

void WXEMessageOperateV2_6_8_51::preventWithdrawalMessage() const {
    
}

