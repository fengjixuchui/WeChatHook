#include "stdafx.h"
#include "WXESubject.h"

DWORD WXESubject::userNumber = 2000;
WXEUserSubjectMap WXESubject::userMap;
std::mutex WXESubject::mutexLock;

WXESubject::WXESubject(const WXESubject& val) {
	winBaseAddress = val.winBaseAddress;
}

WXESubject::WXESubject(DWORD address)
	:winBaseAddress(address) {

}

WXESubject::~WXESubject() {

}

WXESubject& WXESubject::createSubject(DWORD address) {
	mutexLock.try_lock();
	WXESubject instance = WXESubject(address);
	userMap.insert(std::pair<DWORD, WXESubject>(userNumber, instance));
	mutexLock.unlock();
	return instance;
}