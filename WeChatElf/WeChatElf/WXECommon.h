#pragma once

#include "WXETypes.h"

template<size_t T>
struct WXEHookItems {
	DWORD hookAddress;
	DWORD originCall;
	DWORD nextOrderAddress;
	DWORD jumpCall; //  Bare function
	DWORD disposeCall; // User dispose call
	WXEHookItems(DWORD address = 0x0, DWORD call = 0x0) {
		hookAddress = address;
		originCall = call;
		nextOrderAddress = hookAddress + T;
		jumpCall = 0x0;
		disposeCall = 0x0;
	}
};

template<size_t T>
class WXEHookOperator {
public:
	WXEError execute(LPCVOID hookAddress, std::array<BYTE, T>& code) const {
		std::array<BYTE, T> tempCode;
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, GetCurrentProcessId());

		if (ReadProcessMemory(hProc, hookAddress, tempCode.data(), T, NULL) == 0)
			return WXEErrorHookFailed;
		if (WriteProcessMemory(hProc, (LPVOID)hookAddress, code.data(), T, NULL) == 0)
			return WXEErrorHookFailed;

		memcpy(code.data(), tempCode.data(), T);
		return WXEErrorSuccess;
	}
};

template<typename T>
class  WXESecurityStore {
public:
	WXESecurityStore(bool set = false) :isSet(set) { }
	WXESecurityStore(const WXESecurityStore& other):WXESecurityStore(other.isSet){ }
	void setObject(const T& e) {
		lock.try_lock();
		cache = e;
		isSet = true;
		lock.unlock();
	}
	const T& object() {
		lock.try_lock();
		isSet = false;
		lock.unlock();
		return std::move(cache);
	}
	const bool isValid() const {
		return isSet;
	}
	void reset() {
		lock.try_lock();
		cache = NULL;
		isSet = false;
		lock.unlock();
	}

private:
	T cache;
	std::mutex lock;
	bool isSet;
};