#pragma once

#include "WXECommon.h"

const static WCHAR *WXENameCardXmlTemplate =
L"<?xml version=\"1.0\"?><msg bigheadimgurl=\"\" smallheadimgurl=\"\" username=\"%s\" nickname=\"%s\" fullpy=\"\" shortpy=\"\" alias=\"\" imagestatus=\"\" scene=\"\" province=\"\" city=\"\" sign=\"\" sex=\"\" certflag=\"\" certinfo=\"\" brandIconUrl=\"\" brandHomeUrl=\"\" brandSubscriptConfigUrl= \"\" brandFlags=\"\" regionCode=\"\" />";

const static WCHAR *WXEArticleXmlTemplate =
L"<msg><fromusername>%s</fromusername><scene>0</scene><commenturl></commenturl><appmsg appid=\"\" sdkver=\"0\"><title>%s</title><des>%s</des><action>view</action><type>%s</type><showtype>%s</showtype><content></content><url>%s</url><dataurl></dataurl><lowurl></lowurl><thumburl>%s</thumburl><messageaction></messageaction><recorditem><![CDATA[]]></recorditem><extinfo></extinfo><sourceusername></sourceusername><sourcedisplayname></sourcedisplayname><commenturl></commenturl><appattach><totallen>0</totallen><attachid></attachid><emoticonmd5></emoticonmd5><fileext></fileext></appattach></appmsg><appinfo><version>1</version><appname>Window wechat</appname></appinfo></msg>";

typedef struct _WXEPublicArticleStruct
{
    WCHAR *sender;
    WCHAR *title;
    WCHAR *content;
    WCHAR *type;
    WCHAR *showtype;
    WCHAR *url;
    WCHAR *thumburl;
    DWORD combineXml (WCHAR *const xml, size_t count) const {
        return swprintf_s(xml, count, WXEArticleXmlTemplate, sender, title, content, type, showtype, url, thumburl) > 0;
    }
} WXEPublicArticle;

class WXEMessageOperateBase {
public:
    virtual ~WXEMessageOperateBase();
    
    virtual void sendTextMessage(const std::wstring& recver, const std::wstring& content) const = 0;
    virtual void sendAtRoomMemberMessage(const std::wstring& room, const std::vector<WXEUserID>& atUsers, const std::wstring& content) const = 0;
    virtual void sendNameCardMessage(const std::wstring& recver, const std::wstring& sharedUser, const std::wstring& sharedUserNickName) const = 0;
    virtual void sendLinkMessage(const std::wstring& sender, const std::wstring& recver, const WXEPublicArticle& link) const = 0;
    virtual void sendPictureMessage(const std::wstring& recver, const std::wstring& path) const = 0;
    virtual void sendFileMessage(const std::wstring& recver, const std::wstring& path) const = 0;
    virtual void sendVideoMessage(const std::wstring& recver, const std::wstring& path) const = 0;
    virtual void sendGifMessage(const std::wstring& recver, const std::wstring& path) const = 0;
	virtual WXEError switchReceiveMessage(bool isOpen) const = 0;
    virtual void preventWithdrawalMessage() const = 0;

	//添加消息订阅者
	virtual WXEError addMessageSubscriber(WXESubscribeType type, const WXESubscriber& subscriber) = 0;
	virtual void removeMessageSubscriber(WXESubscribeType type) = 0;
};

// Simple implementation
class WXEMessageOperateSimple : public WXEMessageOperateBase {
protected:
    WXEMessageOperateSimple(DWORD address);
    
private:
	WXEError switchReceiveMessage(bool isOpen) const;
	WXEError addMessageSubscriber(WXESubscribeType type, const WXESubscriber& subscriber);
    void removeMessageSubscriber(WXESubscribeType type);
    
protected:
   WXEHookItems<5> hookReceiveMessageItems;
    
private:
    DWORD winBaseAddress;
	std::map<WXESubscribeType, WXESubscriber> subscribers;
};

