#pragma once

#include <vector>
#include <list>
#include <set>
#include <map>
#include <array>

#include <string>

#include <memory>
#include <mutex>
#include <commctrl.h>

enum WXEVersion {
	WXEVersion_2_6_8_51 = 0,
};

enum WXEError {
	WXEErrorSuccess = 0,
	WXEErrorHookFailed = 1,
	WXEErrorNetSceneRequestFailed = 2
};

enum WXESubscribeType {
	WXESubscribeTransfer,
	WXESubscribeFriendRequest,
	WXESubscribeFile,
	WXESubscribeNameCard,
	WXESubscribeRoomInvitation
};

typedef struct _WXEGeneralTextStruct {
	WCHAR *text;
	DWORD length;
	DWORD maxLength;
	CHAR fill[0x8];
	_WXEGeneralTextStruct(const std::wstring &value = std::wstring(L"")) {
		text = const_cast<WCHAR *>(value.c_str());
		length = value.length();
		maxLength = length * 2;
		memset(fill, 0, sizeof(fill));
	}
} WXEGeneralTextStruct;
using WXEUserID = WXEGeneralTextStruct;
using WXERoomID = WXEGeneralTextStruct;
using WXEMessage = WXEGeneralTextStruct;
using WXEOPString = WXEGeneralTextStruct;
using WXELocalFile = WXEGeneralTextStruct;

template<typename T>
struct WXEStructArray {
	DWORD start;
	DWORD end;
	DWORD endEx;
	WXEStructArray(DWORD header, size_t count = 1) {
		start = header;
		end = header + sizeof(T) * count;
		endEx = end;
	}
};
using WXEUserArray = WXEStructArray<WXEUserID>;

typedef struct _WXEGeneralDataStruct {
	CHAR *bytes;
	DWORD size;
	_WXEGeneralDataStruct(CHAR *header = NULL, DWORD length = 0) {
		bytes = header;
		size = length;
	}
} WXEGeneralDataStruct;
using WXEData = WXEGeneralDataStruct;
using WXEDataAutoPtr = std::unique_ptr<WXEData>;

template<typename T>
using WXENetSceneCallback = std::function<void(WXEError error, T data)>;

using WXESubscriber = std::function<void(WXEMessage message)>;
