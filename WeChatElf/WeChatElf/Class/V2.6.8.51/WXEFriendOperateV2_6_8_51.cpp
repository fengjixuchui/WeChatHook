#include "stdafx.h"
#include "WXEFriendOperateImpl.h"


WXEFriendOperateV2_6_8_51::WXEFriendOperateV2_6_8_51(DWORD address)
:WXEFriendOperateSimple(address) {
	hookReceiveTransferItems = WXEHookItems<5>(address + 0x1F110B, address + 0x480040);
}

// 对好友执行完毕后显示： XXX已通过你的好友请求，可以开始聊天了
void WXEFriendOperateV2_6_8_51::sendFriendVerification(const std::wstring& wxid, const std::wstring& verifyText) const {
	DWORD call1 = winBaseAddress + 0x69C90;
	DWORD call2 = winBaseAddress + 0x58D70;
	DWORD call3 = winBaseAddress + 0x4818C0;
	DWORD call4 = winBaseAddress + 0x481900;
	DWORD call5 = winBaseAddress + 0x4FFB0;
	DWORD call6 = winBaseAddress + 0x2715B0;
	DWORD paramAddr = winBaseAddress + 0x1006CA8;

	WXEFriendVerify verifyInfo(wxid, verifyText);
	WXEMessage verifyMessage(verifyText);

	CHAR buff[0x100] = { 0 };
	_asm {
		sub esp, 0x18
		mov ecx, esp
		push paramAddr
		call call1
		sub esp, 0x18
		mov ecx, esp
		lea eax, buff
		lea edi, verifyMessage
		lea ebx, verifyInfo
		push eax
		call call2
		push 0xE   //群:0xE ，普通：0x6
		sub esp, 0x14
		mov ecx, esp
		push - 0x1
		push edi
		call call3
		push 0x2
		sub esp, 0x14
		mov ecx, esp
		push ebx
		call call4
		call call5
		mov ecx, eax
		call call6
	}
}

void WXEFriendOperateV2_6_8_51::deleteFriends(const std::wstring& wxid) const {
	friendCommonOperate(wxid, 0x0);
}

void WXEFriendOperateV2_6_8_51::setStarMarkToFriends(const std::wstring& wxid) const {
	friendCommonOperate(wxid, 0x43);
}

void WXEFriendOperateV2_6_8_51::cancelStarMarkToFriends(const std::wstring& wxid) const {
	friendCommonOperate(wxid, 0x3);
}

void WXEFriendOperateV2_6_8_51::modifyFriendNotes() const {

}

// 执行完毕后显示： 你已添加了XXX，现在可以开始聊天了
void WXEFriendOperateV2_6_8_51::agreeToFriendRequest(const std::wstring& v1Str, const std::wstring& v2Str) const {
	DWORD call1 = winBaseAddress + 0x1865B0;
	DWORD call2 = winBaseAddress + 0x4F4F0;
	DWORD call3 = winBaseAddress + 0xCE4F0;
	DWORD call4 = winBaseAddress + 0x16BD40;
	DWORD param = winBaseAddress + 0x126E050;

	DWORD start = winBaseAddress + 0x104FF5C;
	DWORD end = winBaseAddress + 0x104E1B8;
	WXEUserV2 v2Data(v2Str);
	WXEUserV1 v1Data(v1Str, (DWORD)&v2Data);

	struct {
		DWORD first;
		char fill[0x548];
		DWORD last;
		char fillEx[0x550];
	} handle = { 0 };
	handle.first = start;
	handle.last = end;
	DWORD pHandle = (DWORD)&handle.last;

	char buff1[0x24] = { 0 };
	char buff2[0x40] = { 0 };
	_asm {
		lea ecx, v1Data
		push 0x6
		sub esp, 0x14
		push esp
		call call1
		lea ecx, v1Data
		lea eax, buff1
		push eax
		call call2
		mov esi, eax
		sub esp, 0x8
		mov ecx, param
		call call3
		mov ecx, pHandle
		lea edx, buff2
		push eax
		push edx
		push esi
		call call4
	}
}

void WXEFriendOperateV2_6_8_51::receiveFriendTransfer(const std::string& wxid, const std::string& transIDStr) const {
	CHAR start[0xF0] = { 0 };
	DWORD callAddress1 = winBaseAddress + 0x1045A0;
	DWORD callAddress2 = winBaseAddress + 0x104D10;
	DWORD callAddress3 = winBaseAddress + 0x69B50;
	DWORD callAddress4 = winBaseAddress + 0x1034F0;
	DWORD callAddress5 = winBaseAddress + 0x58E90;
	DWORD callAddress6 = winBaseAddress + 0xA4ACEA;
	DWORD callAddress7 = winBaseAddress + 0x672620;
	DWORD callAddress8 = winBaseAddress + 0x104C50;
	DWORD callAddress9 = winBaseAddress + 0x6ACF0;
	DWORD callAddress10 = winBaseAddress + 0x6B000;
	DWORD callAddress11 = winBaseAddress + 0x344190;
	DWORD paramAddress1 = winBaseAddress + 0x127A8B8;

	DWORD strOpAddress = winBaseAddress + 0x69C90;
	DWORD timeOpAddress = winBaseAddress + 0x48E650;

	CHAR tansferStr[] = "trans_id";
	CHAR usernameStr[] = "username";
	CHAR timeStr[] = "invalid_time";
	DWORD opStr = winBaseAddress + 0x1070190;
	DWORD confirmStr = winBaseAddress + 0x127A8D0;
	DWORD transferconfirmStr = winBaseAddress + 0x127A8E8;

	const CHAR *transID = transIDStr.c_str();
	size_t transLen = strlen(transID);
	const CHAR *username = wxid.c_str();
	size_t usernameLen = strlen(username);
	DWORD invalidtime = 1999999999;

	__asm {
		lea ecx, [ebp - 0x50]
		call callAddress1
		mov[ebp - 0x50], eax
		mov[ebp - 0x14], 0xF

		lea eax, tansferStr
		lea ecx, [ebp - 0x28]
		push eax
		call strOpAddress
		lea esi, transID
		lea eax, [ebp - 0x28]
		push eax
		lea eax, [ebp - 0x48]
		push eax
		lea ecx, [ebp - 0x50]
		call callAddress2
		mov ebx, [ebp - 0x48]
		mov ecx, transLen
		push ecx
		push esi
		lea ecx, [ebx + 0x28]
		call callAddress3
		mov eax, 0xF

		lea eax, usernameStr
		lea ecx, [ebp - 0x28]
		push eax
		call strOpAddress
		lea esi, username
		lea eax, [ebp - 0x28]
		push eax
		lea eax, [ebp - 0x48]
		push eax
		lea ecx, [ebp - 0x50]
		call callAddress2
		mov ebx, [ebp - 0x48]
		mov ecx, usernameLen
		push ecx
		push esi
		lea ecx, [ebx + 0x28]
		call callAddress3
		mov eax, 0xF

		lea eax, timeStr
		lea ecx, [ebp - 0x40]
		push eax
		call strOpAddress
		lea ecx, [ebp - 0x28]
		push 0x0
		push invalidtime
		call timeOpAddress
		add esp, 0x8
		mov esi, eax
		lea eax, [ebp - 0x40]
		push eax
		lea eax, [ebp - 0x48]
		push eax
		lea ecx, [ebp - 0x50]
		call callAddress2
		mov ecx, [ebp - 0x48]
		push esi
		add ecx, 0x28
		call callAddress4
		mov eax, 0xF
		mov[ebp - 0x14], 0xF

		push opStr
		lea ecx, [ebp - 0x40]
		call strOpAddress
		lea eax, [ebp - 0x40]
		push eax
		lea eax, [ebp - 0x48]
		push eax
		lea ecx, [ebp - 0x50]
		call callAddress2
		mov ecx, [ebp - 0x48]
		add ecx, 0x28
		push - 0x1
		push 0x0
		push confirmStr
		call callAddress5
		mov eax, 0xF
		push - 0x1
		push 0x0
		push confirmStr
		mov ecx, paramAddress1
		call callAddress5

		lea ecx, [ebp - 0x64]
		call callAddress1
		mov[ebp - 0x64], eax
		push 0x188
		call callAddress6
		add esp, 0x4

		mov[ebp - 0x58], eax
		push 0x0
		push ecx
		push 0x55
		lea ecx, [ebp - 0x64]
		push ecx
		lea ecx, [ebp - 0x50]
		push ecx
		push transferconfirmStr
		mov ecx, eax
		call callAddress7

		lea ecx, [ebp - 0x48]
		push eax
		mov[ebp - 0x48], 0x0
		mov[ebp - 0x44], 0x0
		call callAddress8
		lea eax, [ebp - 0x48]
		mov ecx, esp
		push eax
		call callAddress9
		call callAddress10
		mov ecx, eax
		call callAddress11
		sub esp, 0x8
	}
}

void WXEFriendOperateV2_6_8_51::agreeToRoomInvitaionOfFriend(const std::wstring& invitationLinks) const {
	// 发送HTTPS POST
}

void WXEFriendOperateV2_6_8_51::friendCommonOperate(const std::wstring& wxid, DWORD opCode) const {
	struct Param {
		CHAR fill[0x8] = { 0 };
		WXEUserID friendID;
		CHAR fillEx[0x42C] = { 0 };
		Param(const std::wstring& wxid) : friendID(WXEUserID(wxid)) { }
	} param = { wxid };

	*(DWORD *)((CHAR *)&param + 0x48) = opCode;
	*(DWORD *)((CHAR *)&param + 0x228) = opCode;

	DWORD call1st = winBaseAddress + 0x2D91D0;
	DWORD paramAddr = winBaseAddress + 0x127F870;

	char buff[0x64] = { 0 };
	__asm {
		pushad
		mov eax, 0x1
		lea ecx, buff
		lea esi, param
		push ecx
		push esi
		mov ecx, paramAddr
		call call1st
		popad
	}
}
