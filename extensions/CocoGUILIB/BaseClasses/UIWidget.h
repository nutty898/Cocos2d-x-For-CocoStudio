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

#ifndef __UIWIDGET_H__
#define __UIWIDGET_H__

#include "cocos2d.h"
#include "ExtensionMacros.h"
#include "../Layouts/UILayoutDefine.h"
#include "../Layouts/LayoutParameter.h"
NS_CC_EXT_BEGIN


typedef enum
{
    BRIGHT_NONE = -1,
    BRIGHT_NORMAL,
    BRIGHT_HIGHLIGHT
}BrightStyle;

typedef enum
{
    WidgetTypeWidget, //control
    WidgetTypeContainer //container
}WidgetType;

typedef enum
{
    UI_TEX_TYPE_LOCAL,
    UI_TEX_TYPE_PLIST
}TextureResType;

typedef void (CCObject::*SEL_PushEvent)(CCObject*);
typedef void (CCObject::*SEL_MoveEvent)(CCObject*);
typedef void (CCObject::*SEL_ReleaseEvent)(CCObject*);
typedef void (CCObject::*SEL_CancelEvent)(CCObject*);
#define coco_pushselector(_SELECTOR) (cocos2d::extension::SEL_PushEvent)(&_SELECTOR)
#define coco_moveselector(_SELECTOR) (cocos2d::extension::SEL_MoveEvent)(&_SELECTOR)
#define coco_releaseselector(_SELECTOR) (cocos2d::extension::SEL_ReleaseEvent)(&_SELECTOR)
#define coco_cancelselector(_SELECTOR) (cocos2d::extension::SEL_CancelEvent)(&_SELECTOR)

class UILayer;

class UIWidget : public CCObject
{
public:
    UIWidget();
    virtual ~UIWidget();
    virtual void releaseResoures();
    static UIWidget* create();
    void setBrightStyle(BrightStyle style);
    virtual void setWidgetZOrder(int z);
    virtual int getWidgetZOrder();
    virtual void setTouchEnabled(bool enable);
    bool isTouchEnabled();
    void setUpdateEnabled(bool enable);
    bool isUpdateEnabled();
    bool isFocus();
    void setFocus(bool fucos);
    void setVisible(bool visible);
    bool isVisible() const;
    void setBright(bool bright);
    bool isBright() const;
    void setEnabled(bool enabled);
    bool isEnabled() const;
    virtual float getRelativeLeftPos();
    virtual float getRelativeBottomPos();
    virtual float getRelativeRightPos();
    virtual float getRelativeTopPos();
    
    
    CCNode* getContainerNode();
    
	void setWidgetParent(UIWidget* parent);
    UIWidget* getWidgetParent();
    
    virtual void addPushDownEvent(CCObject* target,SEL_PushEvent selector);
    virtual void addMoveEvent(CCObject* target,SEL_MoveEvent selector);
    virtual void addReleaseEvent(CCObject* target,SEL_ReleaseEvent selector);
    virtual void addCancelEvent(CCObject* target,SEL_CancelEvent selector);
    //cocos2d property
    void setPosition(const CCPoint &pos);
    virtual void setAnchorPoint(const CCPoint &pt);
    void updateAnchorPoint();
    const CCPoint& getPosition();
    const CCPoint& getAnchorPoint();
    virtual void setScale(float scale);
    float getScale();
    virtual void setScaleX(float scaleX);
    float getScaleX();
    virtual void setScaleY(float scaleY);
    float getScaleY();
    void setRotation(float rotation);
    float getRotation();
    void setRotationX(float rotationX);
    float getRotationX();
    void setRotationY(float rotationY);
    float getRotationY();
    virtual void setSkewX(float skewX);
    virtual float getSkewX();
    virtual void setSkewY(float skewY);
    virtual float getSkewY();
    virtual void setFlipX(bool flipX){};
    virtual bool isFlipX(){return false;};
    virtual void setFlipY(bool flipY){};
    virtual bool isFlipY(){return false;};
    virtual void setColor(const ccColor3B &color);
    virtual const ccColor3B& getColor();
    virtual void setOpacity(int opacity);
    virtual int getOpacity();
    virtual bool isCascadeOpacityEnabled();
    virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
    virtual bool isCascadeColorEnabled();
    virtual void setCascadeColorEnabled(bool cascadeColorEnabled);
    void setBlendFunc(ccBlendFunc blendFunc);
    //cocos action
    virtual void setActionManager(CCActionManager* actionManager);
    virtual CCActionManager* getActionManager();
    CCAction* runAction(CCAction* action);
    void stopAllActions(void);
    void stopAction(CCAction* action);
    void stopActionByTag(int tag);
    CCAction* getActionByTag(int tag);
    
	void setActionTag(int tag);
	int getActionTag();
    
    void didNotSelectSelf();
    
    virtual void update(float dt){};
    bool checkVisibleDependParent(const CCPoint &pt);
    virtual void checkChildInfo(int handleState,UIWidget* sender,const CCPoint &touchPoint);
    void setUILayer(UILayer* uiLayer);
    
    void structureChangedEvent();
    
    const CCPoint& getTouchStartPos();
    const CCPoint& getTouchMovePos();
    const CCPoint& getTouchEndPos();
    void setWidgetTag(int tag);
    int getWidgetTag();
    void setName(const char* name);
    const char* getName();
    WidgetType getWidgetType();
    virtual void setSize(const CCSize &size);
    const CCSize& getSize() const;
    
    virtual bool hitTest(const CCPoint &pt);
    virtual bool onTouchBegan(const CCPoint &touchPoint);
    virtual void onTouchMoved(const CCPoint &touchPoint);
    virtual void onTouchEnded(const CCPoint &touchPoint);
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    virtual void onTouchLongClicked(const CCPoint &touchPoint);
    
    void setLayoutParameter(LayoutParameter* parameter);
    LayoutParameter* getLayoutParameter();
protected:
    virtual void onSizeChanged();
    virtual bool init();
    virtual void initRenderer();
    virtual void onPressStateChangedToNormal();
    virtual void onPressStateChangedToPressed();
    virtual void onPressStateChangedToDisabled();
    void pushDownEvent();
    void moveEvent();
    void releaseUpEvent();
    void cancelUpEvent();
    void longClickEvent();    
protected:
    bool m_bEnabled;
    bool m_bVisible;
    bool m_bBright;
    bool m_bTouchEnabled;
    bool m_bTouchPassedEnabled;
    bool m_bFocus;

    int m_nWidgetZOrder;
    CCPoint m_anchorPoint;
    UIWidget* m_pWidgetParent;
    BrightStyle m_eBrightStyle;
    bool m_bUpdateEnabled;
    CCNode* m_pRenderer;
    
    CCPoint m_touchStartPos;
    CCPoint m_touchMovePos;
    CCPoint m_touchEndPos;
    CCObject*       m_pPushListener;
    SEL_PushEvent    m_pfnPushSelector;
    CCObject*       m_pMoveListener;
    SEL_MoveEvent    m_pfnMoveSelector;
    CCObject*       m_pReleaseListener;
    SEL_ReleaseEvent    m_pfnReleaseSelector;
    CCObject*       m_pCancelListener;
    SEL_ReleaseEvent    m_pfnCancelSelector;
    bool m_bOpacityDirty;
    int m_nWidgetTag;
    std::string m_strName;
    WidgetType m_WidgetType;
    UILayer* m_pUILayer;
	int m_nActionTag;
    CCSize m_size;
    
    LayoutParameter* m_pLayoutParameter;
};

class GUIRenderer : public CCNodeRGBA
{
public:
    GUIRenderer();
    virtual ~GUIRenderer();
    virtual void visit(void);
    static GUIRenderer* create();
    void setEnabled(bool enabled);
    bool getEnabled() const;
protected:
    bool m_bEnabled;
};

NS_CC_EXT_END

#endif /* defined(__UIWidget__) */
