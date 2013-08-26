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

#ifndef __UILOADINGBAR_H__
#define __UILOADINGBAR_H__

#include "../BaseClasses/UIWidget.h"

NS_CC_EXT_BEGIN

typedef enum
{
    LoadingBarTypeLeft,
    LoadingBarTypeRight
}LoadingBarType;

class UILoadingBar : public UIWidget
{
public:
    UILoadingBar();
    virtual ~UILoadingBar();
    static UILoadingBar* create();
    void setDirection(LoadingBarType dir);
    int getDirection();
    void loadTexture(const char* texture,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setPercent(int percent);
    int getPercent();
    float getTotalWidth();
    float getTotalHeight();
    void setScale9Enabled(bool enabled);
    void setCapInsets(const CCRect &capInsets);
    void ignoreContentAdaptWithSize(bool ignore);
    /*Compatible*/
    void setTexture(const char* texture,TextureResType texType = UI_TEX_TYPE_LOCAL){loadTexture(texture,texType);};
    void setScale9Size(const CCSize& size){setScale9Enabled(true);setSize(size);};
    void setScale9Enable(bool is){setScale9Enabled(is);};
    /************/
    virtual const CCSize& getContentSize() const;
protected:
    virtual void initRenderer();
    virtual void onSizeChanged();
    void setScale9Scale();
    void barRendererScaleChangedWithSize();
protected:
    LoadingBarType m_nBarType;
    int m_nPercent;
    float m_fTotalLength;
    CCNode* m_pBarRenderer;
    TextureResType m_eRenderBarTexType;
    CCSize m_barRendererTextureSize;
    bool m_bScale9Enabled;
    CCRect m_capInsets;
    std::string m_strTextureFile;
};

NS_CC_EXT_END

#endif /* defined(__CocoGUI__UILoadingBar__) */
