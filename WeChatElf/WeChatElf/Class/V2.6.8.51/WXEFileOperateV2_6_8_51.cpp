#include "stdafx.h"
#include "WXEFileOperateImpl.h"

WXEFileOperateV2_6_8_51::WXEFileOperateV2_6_8_51(DWORD address)
:WXEFileOperateSimple(address) {
    hookAutoDownloadItems = WXEHookItems<2>(address+0x1F110B, 0x0);
    hookSaveFileItems = WXEHookItems<5>(address+0x1F110B, address+0x480040);
}

void WXEFileOperateV2_6_8_51::downloadFile(const CHAR *aesKey, const CHAR *fileID, const CHAR *savePath) const {
    
    CHAR buff[0x1500] = { 0 }; //begin 0x1200
    CHAR buff2[0x2DC] = { 0 };
    CHAR buff3[0x28] = { 0 };
    
    DWORD paramEdi = *(DWORD *)(winBaseAddress + 0x12637D8);
    
    DWORD callAddress1 = winBaseAddress + 0xBF0710;
    DWORD callAddress2 = winBaseAddress + 0xBF0380;
    DWORD getHandleAddress = winBaseAddress + 0xA4ACEA;
    DWORD callAddress3 = winBaseAddress + 0xAFBB20;
    DWORD callAddress4 = winBaseAddress + 0xA7F200;
    DWORD callAddress5 = winBaseAddress + 0xAF1B30;
    DWORD callAddress6 = winBaseAddress + 0xBF0F80;
    DWORD callAddress7 = winBaseAddress + 0xBC91C0;
    DWORD callAddress8 = winBaseAddress + 0xA86550;
    DWORD callAddress9 = winBaseAddress + 0xA9B020;
    DWORD callAddress10 = winBaseAddress + 0xAF9ED0;
    DWORD callAddress11 = winBaseAddress + 0xAFE940;
    
  //  char aesKey[] = "6d3867f3df4d154162b5aaee533c3116";
    size_t aesKeyLen = strlen(aesKey);
    size_t aesKeyLenEx = aesKeyLen | 0xF;
    
  //  char fileID[] = "305a020100045330510201000204b21fbcad02033d14bb02046a80337902045d1728fd042c777875706c6f61645f31323130303037373836394063686174726f6f6d313035385f313536313739383930380204010818020201000400";
    size_t fileIDLen = strlen(fileID);
    size_t fileIDLenEx = fileIDLen | 0xF;
    
  //  char savePath[] = "C:\\Users\\lenovo\\Documents\\test.jpg";
    size_t pathLen = strlen(savePath);
    size_t pathLenEx = pathLen | 0xF;
    
    __asm {
        pushad
            //构造参数
            lea eax, buff[0xA58]
            mov ecx, eax
            call callAddress1
            mov esi, eax
        
            lea ecx, buff[0x140]
            call callAddress3
        
            lea eax, buff[0x120]
            push eax
            call callAddress4
            add esp, 0x4
        
            mov eax, esi
            mov [eax], 0x02
        
            add eax, 0x24
            lea ecx, fileID
            mov [eax], ecx
            add eax, 0x10
            mov ecx, fileIDLen
            mov [eax], ecx
            add eax, 0x4
            mov ecx, fileIDLenEx
            mov [eax], ecx
        
            lea eax, aesKey
            push aesKeyLen
            push eax
            lea eax, buff3
            push eax
            call callAddress5
            add esp, 0xC
            mov eax, esi
            add eax, 0x3C
            lea ecx, buff3
            mov ecx, [ecx]
            mov [eax], ecx
            add eax, 0x10
            mov [eax], 0x10
            add eax, 0x4
            mov [eax], 0x1F
        
            mov eax, esi
            add eax, 0x1AC
            lea ecx, savePath
            mov [eax], ecx
            add eax, 0x10
            mov ecx, pathLen
            mov [eax], ecx
            add eax, 0x4
            mov ecx, pathLenEx
            mov [eax], ecx
        
            mov eax, esi
            add eax, 0x9C
            mov [eax], 0x2
            add eax, 0x8
            mov [eax], 0xB
            add eax, 0x4
            mov [eax], 0x6
            add eax, 0x4
            mov [eax], 0x1
            add eax, 0x10
            mov dword ptr ss : [eax], 0x4E20
            add eax, 0x8
            mov dword ptr ss : [eax], 0x1010000
            add eax, 0xC
            mov dword ptr ss : [eax], 0x1010000
            add eax, 0xA0
            mov dword ptr ss : [eax], 0x1
            add eax, 0x4
            mov dword ptr ss : [eax], 0x1
            add eax, 0x4
            mov dword ptr ss : [eax], 0x2
        
            mov eax, esi
            add eax, 0x280
            mov dword ptr ss : [eax], 0x6E776F64 //down...
            add eax, 0x4
            mov dword ptr ss : [eax], 0x64616F6C //....load
            add eax, 0xC
            mov [eax], 0x8
        
            mov eax, esi
            add eax, 0x3EC
            mov [eax], 0x0
            add eax, 0x8
            mov [eax], 0x3
        
            mov eax, 0x90
            mov ebx, 0xF
            mov ecx, 0x7
            mov edx, 0x2F
            mov edi, 0xF
            push eax
            call getHandleAddress
            add esp, 0x4
            mov ebx, eax
            mov eax, esi
            add eax, 0x6C
            mov [eax], ebx
            add eax, 0x10
            mov [eax], 0x80
            add eax, 0x4
            mov [eax], 0x8F
        
            lea eax, buff[0x140]
            push eax
            lea eax, buff[0xA58]
            push eax
            lea eax, buff[0x134]
            push eax
            call callAddress2
            add esp, 0xC
            // 得到参数存在eax
        
            //将参数存到buff2中
            mov edx, eax
            mov edx, [edx]
            lea ecx, buff2[0xC]
            mov [ecx], edx
            add ecx, 0x4
            sub edx, 0x10
            mov [ecx], edx
        
            //下载文件
            lea eax, buff2[0xC]
            lea ecx, buff2
            call callAddress6
            lea esi, buff2[0xC]
            mov esi, [esi]
            lea eax, buff2[0x26C]
            push eax
            mov ecx, esi
            call callAddress7
            push eax
            lea ecx, buff2[0x224]
            call callAddress8
            push 0xA
            push dword ptr ds : [esi + 0x190]
            lea ecx, buff2[0x194]
            call callAddress9
            lea esi, buff2[0xC]
            mov esi, [esi]
            sub esp, 0x8
            lea eax, buff2[0xC]
            mov ecx, esp
            push eax
            call callAddress10
            mov edi, paramEdi
            mov ecx, edi
            call callAddress11
        popad
    }
}
