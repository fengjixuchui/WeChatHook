#pragma once

#include "WXECommon.h"


/*
 *	Interface
 */

class WXEHookOperateBase{
public:
	virtual ~WXEHookOperateBase();

	virtual void hookGetQRCode(bool open) = 0;/*
	virtual void hookReceiveTransferResult() const = 0;
	virtual void hookReceiveMessage() const = 0;
	virtual void hookGetUserInfoFromNetwork() const = 0;*/

	virtual bool isOpenGetQRCode() const = 0;/*
	virtual bool isOpenTransferResult() const = 0;
	virtual bool isOpenReceiveMessage() const = 0;
	virtual bool isOpenGetUserInfoFromNetwork() const = 0;*/
};



/*
 *	Common Implementation
 */
template<size_t T>
struct WXEHookItems {
	DWORD hookAddress;
	DWORD originCall;
	DWORD nextOrderAddress;
	WXEHookItems(DWORD address = 0x0, DWORD call = 0x0) {
		hookAddress = address;
		originCall = call;
		nextOrderAddress = hookAddress + T;
	}
};

class WXEHookOperateSimple : public WXEHookOperateBase {
public:
	bool isOpenGetQRCode() const;

protected:
	WXEHookOperateSimple(DWORD address);
	virtual void initHookOffset() = 0;

private:
	void sendQRCodePNG(DWORD *pngHeaderPtr) const;

protected:
	DWORD winBaseAddress;

protected:
	static std::mutex hookGetQRCodeLock;

protected:
	std::array<BYTE, 5> backupGetQRCode;

	bool openGetQRCode;
	bool openReceiveTransferResult;
	bool openReceiveMessage;
	bool openGetUserInfoFromNetwork;
};



template<size_t T>
class WXEHookOperator {
public:
	WXEError execute(DWORD hookAddress, std::array<BYTE, T>& code) const {
		std::array<BYTE, T> backCode;
		HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, GetCurrentProcessId());

		if (ReadProcessMemory(hProc, (LPCVOID)hookAddress, backCode.data(), T, NULL) == 0)
			return WXEErrorHookFailed;
		if (WriteProcessMemory(hProc, (LPVOID)hookAddress, code.data(), T, NULL) == 0)
			return WXEErrorHookFailed;

		memcpy(code.data(), backCode.data(), T);
		return WXEErrorSuccess;
	}
};
