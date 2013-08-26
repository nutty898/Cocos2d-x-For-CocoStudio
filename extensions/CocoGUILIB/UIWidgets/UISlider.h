/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __UISLIDER_H__
#define __UISLIDER_H__

#include "UIWidget.h"

NS_CC_EXT_BEGIN

typedef void (CCObject::*SEL_PercentChangedEvent)(CCObject*);
#define coco_percentchangedselector(_SELECTOR) (SEL_PercentChangedEvent)(&_SELECTOR)
class UISlider : public UIWidget
{
public:
    UISlider();
    virtual ~UISlider();
    static UISlider* create();
    void loadBarTexture(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setScale9Enabled(bool able);
    void setCapInsets(const CCRect &capInsets);
    void loadSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void loadSlidBallNormalTexture(const char* normal,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void loadSlidBallPressedTexture(const char* pressed,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void loadSlidBallDisabledTexture(const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void loadProgressBarTexture(const char* fileName, TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setPercent(int percent);
    virtual void addPercentChangedEvent(CCObject* target,SEL_PushEvent selector);
    int getPercent();
    virtual bool onTouchBegan(const CCPoint &touchPoint);
    virtual void onTouchMoved(const CCPoint &touchPoint);
    virtual void onTouchEnded(const CCPoint &touchPoint);
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    
    /*Compatible*/
    void setBarTexture(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL){loadBarTexture(fileName,texType);};
    void setSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL){loadSlidBallTextures(normal, pressed, disabled,texType);};
    void setSlidBallNormalTexture(const char* normal,TextureResType texType = UI_TEX_TYPE_LOCAL){loadSlidBallNormalTexture(normal,texType);};
    void setSlidBallPressedTexture(const char* pressed,TextureResType texType = UI_TEX_TYPE_LOCAL){loadSlidBallPressedTexture(pressed,texType);};
    void setSlidBallDisabledTexture(const char* disabled,TextureResType texType = UI_TEX_TYPE_LOCAL){loadSlidBallDisabledTexture(disabled,texType);};
    void setProgressBarTexture(const char* fileName, TextureResType texType = UI_TEX_TYPE_LOCAL){loadProgressBarTexture(fileName,texType);};
    void setSlidBallPercent(int percent){setPercent(percent);};
    void setScale9Size(const CCSize& size){setScale9Enabled(true);setSize(size);};
    void setScale9Enable(bool is){setScale9Enabled(is);};
    /************/
    virtual const CCSize& getContentSize() const;
    void ignoreContentAdaptWithSize(bool ignore);
protected:
    virtual void initRenderer();
    float getPercentWithBallPos(float location);
    void percentChangedEvent();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
    virtual void onSizeChanged();
    void barRendererScaleChangedWithSize();
    void progressBarRendererScaleChangedWithSize();
protected:
    CCNode*  m_pBarRenderer;
    CCNode* m_pProgressBarRenderer;
    CCSize m_ProgressBarTextureSize;
    
    CCSprite* m_pSlidBallNormalRenderer;
    CCSprite* m_pSlidBallPressedRenderer;
    CCSprite* m_pSlidBallDisabledRenderer;
    CCNode* m_pSlidBallRenderer;
    
    float m_fBarLength;
    int m_nPercent;
    
    float m_fBarNodeScaleValue;
    float m_fTouchMoveStartLocation;
    bool m_bScale9Enabled;
    std::string m_strTextureFile;
    std::string m_strProgressBarTextureFile;
    std::string m_strSlidBallNormalTextureFile;
    std::string m_strSlidBallPressedTextureFile;
    std::string m_strSlidBallDisabledTextureFile;
    CCRect m_capInsets;
    CCObject*       m_pPercentListener;
    SEL_PushEvent    m_pfnPercentSelector;
    TextureResType m_eBarTexType;
    TextureResType m_eProgressBarTexType;
    TextureResType m_eBallNTexType;
    TextureResType m_eBallPTexType;
    TextureResType m_eBallDTexType;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UISlider__) */
