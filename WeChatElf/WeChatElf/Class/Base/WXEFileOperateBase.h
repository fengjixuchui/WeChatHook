#pragma once

#include "WXECommon.h"

class WXEFileOperateBase {
public:
    virtual ~WXEFileOperateBase();
    
    virtual WXEError switchAutoDownloadFile(bool isOpen) const = 0;
    virtual void downloadFile(const CHAR *aesKey, const CHAR *fileID, const CHAR *savePath) const = 0;
};

// Simple implementation
class WXEFileOperateSimple : public WXEFileOperateBase {
protected:
    WXEFileOperateSimple(DWORD address);
    virtual WXEError switchAutoDownloadFile(bool isOpen) const;
    
private:
    WXEError hookSaveFile(bool isOpen) const;
    
protected:
    WXEHookItems<2> hookAutoDownloadItems;
    WXEHookItems<5> hookSaveFileItems;
    
private:
    DWORD winBaseAddress;
};

