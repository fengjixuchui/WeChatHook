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

enum WXEError {
	WXEErrorSuccess = 0,
	WXEErrorHookFailed = 1,
};

typedef struct _WXEGeneralTextStruct
{
	std::wstring text;
	DWORD length;
	DWORD maxLength;
	CHAR fill[0x8];
	_WXEGeneralTextStruct(const std::wstring& value) {
		text = value;
		length = value.length();
		maxLength = length * 2;
		memset(fill, 0, sizeof(fill));
	}
} WXEGeneralTextStruct;
using WXEUserID = WXEGeneralTextStruct;
using WXERoomID = WXEGeneralTextStruct;
using WXEMessage = WXEGeneralTextStruct;
using WXEOPString = WXEGeneralTextStruct;

template<typename T>
struct _WXEGeneralStructArray {
	DWORD start;
	DWORD end;
	DWORD endEx;
	_WXEGeneralStructArray(DWORD header) {
		start = header;
		end = header + sizeof(T);
		endEx = end;
	}
};
template<typename T>
using WXEStructArray = _WXEGeneralStructArray<T>;

typedef struct _WXEGeneralDataStruct {
	DWORD bytes;
	DWORD size;
	_WXEGeneralDataStruct(DWORD header, DWORD length) {
		bytes = header;
		size = length;
	}
	_WXEGeneralDataStruct(const _WXEGeneralDataStruct& other) {
		this->bytes = other.bytes;
		this->size = other.size;
	}
} WXEGeneralDataStruct;
using WXEData = WXEGeneralDataStruct;
using WXEDataAutoPtr = std::unique_ptr<WXEData>;

template<typename T>
using WXENetSceneCallback = std::function<void(WXEError error, T data)>;