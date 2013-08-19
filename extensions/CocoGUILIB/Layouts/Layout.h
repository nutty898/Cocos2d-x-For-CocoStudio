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
protected:
    virtual bool init();
    virtual void initRenderer();
    virtual void onSizeChanged();
    virtual void setClippingEnabled(bool able);
    virtual bool isClippingEnabled();
    
protected:
    float m_fWidth;
    float m_fHeight;
    bool m_bClippingEnabled;
    CCArray* m_children;
    LayoutExecutant* m_pLayoutExecutant;
};

NS_CC_EXT_END

#endif /* defined(__Layout__) */
