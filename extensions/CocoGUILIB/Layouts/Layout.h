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

#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "../BaseClasses/UIWidget.h"
#include "LayoutExecutant.h"

NS_CC_EXT_BEGIN

typedef enum
{
    LAYOUT_COLOR_NONE,
    LAYOUT_COLOR_SOLID,
    LAYOUT_COLOR_GRADIENT
}LayoutBackGroundColorType;

class Layout : public UIWidget
{
public:
    Layout();
    virtual ~Layout();
    static Layout* create();    
    void setLayoutExecutant(LayoutExecutant* exe);
    LayoutExecutant* getLayoutExecutant() const;
    virtual bool addChild(UIWidget* child);
    virtual bool removeChild(UIWidget* child,bool cleanup);
    virtual void removeFromParentAndCleanup(bool cleanup);
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    virtual void releaseResoures();
    void updateChildrenUILayer(UILayer* uiLayer);
    void disableUpdate();
    virtual void reorderChild(UIWidget* child);
    void setEnabled(bool enabled);
    UIWidget* getChildByName(const char* name);
    UIWidget* getChildByTag(int tag);
    CCArray* getChildren();
    virtual bool hitTest(const CCPoint &pt);
    
    //background
    void setBackGroundImage(const char* fileName,TextureResType texType = UI_TEX_TYPE_LOCAL);
    void setBackGroundImageCapInsets(const CCRect& capInsets);
    virtual void setBackGroundColorType(LayoutBackGroundColorType type);
    void setBackGroundImageScale9Enabled(bool able);
    void setBackGroundColor(const ccColor3B &color);
    void setBackGroundColor(const ccColor3B &startColor, const ccColor3B &endColor);
    void setBackGroundColorOpacity(int opacity);
    void setBackGroundColorVector(const CCPoint &vector);
    virtual void setColor(const ccColor3B &color);
    virtual void setOpacity(int opacity);
    void removeBackGroundImage();
    const CCSize& getBackGroundImageTextureSize() const;
    /*Compatible*/
    void setBackGroundImageScale9Enable(bool is){setBackGroundImageScale9Enabled(is);};
    /************/
protected:
    virtual bool init();
    virtual void initRenderer();
    virtual void onSizeChanged();
    virtual void setClippingEnabled(bool able);
    virtual bool isClippingEnabled();
    void addBackGroundImage();
protected:
//    float m_fWidth;
//    float m_fHeight;
    bool m_bClippingEnabled;
    CCArray* m_children;
    LayoutExecutant* m_pLayoutExecutant;
    
    //background
    bool m_bBackGroundScale9Enable;
    CCNode* m_pBackGroundImage;
    std::string m_strBackGroundImageFileName;
    CCRect m_backGroundImageCapInsets;
    LayoutBackGroundColorType m_colorType;
    TextureResType m_eBGImageTexType;
    CCLayerColor* m_pColorRender;
    CCLayerGradient* m_pGradientRender;
    ccColor3B m_cColor;
    ccColor3B m_gStartColor;
    ccColor3B m_gEndColor;
    CCPoint m_AlongVector;
    int m_nCOpacity;
    CCSize m_backGroundImageTextureSize;
};

class RectClippingNode : public CCClippingNode
{
public:
    virtual ~RectClippingNode();
    virtual bool init();
    static RectClippingNode* create();
    void setClippingSize(const CCSize& size);
protected:
    CCDrawNode* m_pInnerStencil;
private:
    RectClippingNode();
    CCPoint rect[4];
    CCSize m_clippingSize;
};

NS_CC_EXT_END

#endif /* defined(__Layout__) */
