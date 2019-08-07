#include "stdafx.h"
#include "WXEChatRoomOperateImpl.h"


WXEChatRoomOperateV2_6_8_51::WXEChatRoomOperateV2_6_8_51(DWORD address)
:WXEChatRoomOperateSimple(address) {
	hookQueryMemberInfoItems = WXEHookItems<5>(address + 0x1F110B, address + 0x480040);
	hookCreateRoomResultItems = WXEHookItems<5>(address + 0x1F110B, address + 0x480040);
}

void WXEChatRoomOperateV2_6_8_51::createChatRoom(const std::vector<WXEUserID>& users, const WXENetSceneCallback<WXEData>& callback) const {
    WXEUserArray userArray = WXEUserArray((DWORD)&users[0], users.size());
    DWORD ediVal = userArray.end;
    DWORD callAddress1 = winBaseAddress + 0x264D10;
    DWORD paramEcx = winBaseAddress + 0x126DDC0;

    char buff[0x20] = { 0 };
    _asm {
        pushad
            sub esp, 0x14
            mov ecx, paramEcx
            lea ebx, buff
            lea esi, userArray
            mov edi, ediVal
            mov edx, 0x2
            push esi
            call callAddress1
        popad
    }
}

void WXEChatRoomOperateV2_6_8_51::deleteAndQuitChatRoom(const std::wstring& room) const {
    WXERoomID roomID(room);
    DWORD callAddr1 = winBaseAddress + 0x50070;
    DWORD callAddr2 = winBaseAddress + 0xD5450;
    DWORD callAddr3 = winBaseAddress + 0x50010;
    DWORD callAddr4 = winBaseAddress + 0x26A2F0;
    
    __asm {
        pushad
            lea ebx, roomID
            call callAddr1
            mov ecx, eax
            call callAddr2
            call callAddr3
            push ebx
            call callAddr4
            sub esp, 0x4
        popad
    }
}

void WXEChatRoomOperateV2_6_8_51::inviteFriendToJoinRoom(const std::wstring& room, const std::vector<WXEUserID>& users) const {
    
    WXEUserArray userArray = WXEUserArray((DWORD)&users[0]);
    DWORD ediVal = userArray.end;
    
    struct _{
        CHAR fill[0x8] = { 0 };
        WXEUserID roomID;
        _(std::wstring room) :roomID(room) { }
    } roomStruct = { room };
    
    DWORD callAddress1 = winBaseAddress + 0x67290;
    DWORD callAddress2 = winBaseAddress + 0x2650D0;
    DWORD paramEcx = winBaseAddress + 0x126DDC0;
    
    char buff[0x20] = { 0 };
    
    _asm {
        pushad
            lea esi, userArray
            lea ecx, roomStruct
            lea ebx, buff
            mov edi, ediVal
            sub esp, 0x14
            mov eax, esp
            push eax
            call callAddress1
            push esi
            mov ecx, paramEcx
            call callAddress2
        popad
    }
}

void WXEChatRoomOperateV2_6_8_51::inviteFriendToJoinRoomEx(const std::wstring& room, const std::vector<WXEUserID>& users) const {
    LPVOID lpRoom = HeapAlloc(GetProcessHeap(), 0, 0x2C);
    CopyMemory(lpRoom, room.c_str(), 0x2C);
    
    WXERoomID roomID((WCHAR *)lpRoom);
    WXEUserArray userArray = WXEUserArray((DWORD)&users[0]);
    DWORD dwCall = winBaseAddress + 0x264F30;
    
    __asm {
        pushad
            sub esp, 0x14
            mov ecx, 0x5
            lea esi, roomID
            mov edi, esp
            rep movsd
        
            lea eax, userArray
            push eax
            call dwCall
        popad
    }
}

void WXEChatRoomOperateV2_6_8_51::kickRoomMember(const std::wstring& room, const std::vector<WXEUserID>& users) const {
    WXEUserID roomID(room);
    WXEUserArray userArray = WXEUserArray((DWORD)&users[0]);
    
    DWORD callAddress1 = winBaseAddress + 0x481900;
    DWORD callAddress2 = winBaseAddress + 0x50010;
    DWORD callAddress3 = winBaseAddress + 0x2652F0;
    
    __asm {
        sub esp, 0x14
        lea edi, userArray
        lea eax, room
        mov ecx, esp
        push eax
        call callAddress1
        push edi
        call callAddress2
        mov ecx, eax
        call callAddress3
    }
}

void WXEChatRoomOperateV2_6_8_51::modifyRoomName(const std::wstring& room, const std::wstring& text) const {
    WXERoomID roomID(room);
    WXEGeneralTextStruct name(text);
    WXEOPString operation((WCHAR *)L"menuCmdModifyRoomName");
    DWORD callAddr1 = winBaseAddress + 0x172900;
    char buff[0x100] = { 0 };
    __asm {
        lea eax, name
        push eax
        lea eax, room
        push eax
        lea eax, operation
        push eax
        call callAddr1
    }
}

void WXEChatRoomOperateV2_6_8_51::setRoomAnnouncement(const std::wstring& room, const std::wstring& text) const {
    LPVOID lpRoom = HeapAlloc(GetProcessHeap(), 0, 0x2C);
    CopyMemory(lpRoom, room.c_str(), 0x2C);
    LPVOID lpContent = HeapAlloc(GetProcessHeap(), 0, text.length()+0x4);
    CopyMemory(lpContent, text.c_str(), text.length()+0x4);
    
    struct _{
        WXERoomID roomID;
        WXEGeneralTextStruct content;
        char fill[0x3C] = { 0 };
        _(const std::wstring& room, const std::wstring& text) :roomID(room), content(text){ }
    } param { std::wstring((WCHAR *)lpRoom), std::wstring((WCHAR *)lpContent) };
    
    struct {
        DWORD start;
        DWORD end1;
        DWORD end2;
    } eaxVal;
    eaxVal.start = (DWORD)&param;
    eaxVal.end1 = eaxVal.start + 0x60;
    eaxVal.end2 = eaxVal.end1;
    
    DWORD callAddress1 = winBaseAddress + 0x26CFF0;
    __asm {
        pushad
            lea eax, eaxVal
            push eax
            call callAddress1
        popad
    }
}

void WXEChatRoomOperateV2_6_8_51::modifyMyRoomNickName() const {
    
}

void WXEChatRoomOperateV2_6_8_51::saveRoomToAddressBook() const {
    
}

void WXEChatRoomOperateV2_6_8_51::removeRoomToAddressBook() const {
    
}

void WXEChatRoomOperateV2_6_8_51::addFriendsFromRoom(const std::wstring& room, const std::wstring& user) const {
    LPVOID lpRoom = HeapAlloc(GetProcessHeap(), 0, room.length() + 0x4);
    CopyMemory(lpRoom, room.c_str(), room.length() + 0x4);
    DWORD dwRoom = (DWORD)lpRoom;
    
    WXEUserID userID = WXEUserID(user);
    WXEUserArray userArray = WXEUserArray((DWORD)&userID);
    
    DWORD eaxAddr = *(DWORD *)(winBaseAddress + 0x126E080);
    DWORD ediVal = winBaseAddress + 0x104F9AC;
    
    DWORD dwCall0 = winBaseAddress + 0xA4ACEA;
    DWORD dwCall1 = winBaseAddress + 0x481BC0;
    DWORD dwCall2 = winBaseAddress + 0x350950;
    DWORD dwCall3 = winBaseAddress + 0x2780E0;
    DWORD dwCall4 = winBaseAddress + 0x6B000;
    DWORD dwCall5 = winBaseAddress + 0x344190;
    
    char buff[0x18] = { 0 };
    __asm {
        
        push 0x160
        call dwCall0
        mov esi, eax
        
        sub esp, 0x10
        mov ecx, esp
        mov dword ptr ds : [ecx], 0x0
        mov dword ptr ds : [ecx+0x4], 0x0
        mov dword ptr ds : [ecx+0x8], 0x0
        mov dword ptr ds : [ecx+0xC], 0x0
        mov dword ptr ds : [ecx+0x10], 0x0
        push -0x1
        mov eax, dwRoom
        push eax
        call dwCall1
        
        mov ebx, 0x0
        lea edi, userID
        lea eax, userArray
        mov ecx, esi
        push eax
        call dwCall2
        
        lea ecx, buff
        push eax
        call dwCall3
        sub esp, 0x8
        
        mov ecx, esp
        lea esi, buff[0x4]
        mov esi, dword ptr ds : [esi]
        mov dword ptr ds : [ecx], 0x0
        mov dword ptr ds : [ecx + 0x4], 0x0
        mov dword ptr ds : [ecx+0x4], esi
        lea eax, buff
        mov eax, dword ptr ds : [eax]
        mov dword ptr ds : [ecx], eax
        call dwCall4
        
        mov ecx, eax
        call dwCall5
    }
}
