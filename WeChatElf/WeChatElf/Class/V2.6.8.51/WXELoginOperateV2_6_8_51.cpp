#include "stdafx.h"
#include "WXELoginOperateImpl.h"


WXELoginOperateV2_6_8_51::WXELoginOperateV2_6_8_51(DWORD address)
:WXELoginOperateSimple(address) {
	hookGetQRCodeItems = WXEHookItems<5>(address + 0x1F110B, address + 0x480040);
}

WXEError WXELoginOperateV2_6_8_51::getLoginQRCode(const WXENetSceneCallback<WXEData>& callback) {
	WXEError result = WXEErrorSuccess;
	if ((result = hookGetQRCode(true)) != WXEErrorSuccess) {
		return result;
	}

	DWORD callAddr1 = winBaseAddress + 0xB43E0;
	DWORD callAddr2 = winBaseAddress + 0x1EEE30;
	DWORD callAddr3 = winBaseAddress + 0x2E3070;
	char buff[0x20] = { 0 };
	__asm {
		pushad
			lea ecx, buff
			call callAddr1
			call callAddr2
			mov ecx, eax
			call callAddr3
		popad
	}

	QRCodeStore.setObject(callback);
	std::unique_lock <std::mutex> lock(mutex);
	std::cv_status status = condVar.wait_for(lock, std::chrono::seconds(1));
	if (status == std::cv_status::timeout) {
		QRCodeStore.reset();
		result = WXEErrorNetSceneRequestFailed;
	}
	return result;
}