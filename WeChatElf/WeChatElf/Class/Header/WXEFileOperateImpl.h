#pragma once
#include "WXEFileOperateBase.h"

class WXEFileOperateV2_6_8_51 : public WXEFileOperateSimple {
    
public:
    WXEFileOperateV2_6_8_51(DWORD address);
    
private:
    void downloadFile(const CHAR *aesKey, const CHAR *fileID, const CHAR *savePath) const;
    
private:
    DWORD winBaseAddress;
};

