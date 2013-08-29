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
/*temp action*/
class UIActionNode;

class UIWidget : public CCObject
{
public:
    /// @{
    /// @name Constructor, Distructor and Initializers.
    
    /**
     * Default constructor
     */
    UIWidget(void);
    
    /**
     * Default destructor
     */
    virtual ~UIWidget();
    
    /**
     * Allocates and initializes a widget.
     * @return A initialized widget which is marked as "autorelease".
     */
    static UIWidget* create();
    
    /**
     * Release texture resoures of widget.
     * Release renderer.
     * If you override releaseResoures, you shall call its parent's one, e.g. UIWidget::releaseResoures().
     */
    virtual void releaseResoures();
    
    /**
     * Sets whether the node is enabled
     *
     * Highest control of widget.
     * The default value is true, a widget is default to enabled
     *
     * @param enabled   true if the node is enabled, widget may be touched and visible, false if the node is disabled, widget cannot be touched and hidden.
     */
    void setEnabled(bool enabled);
    
    /**
     * Determines if the widget is enabled
     *
     * @return true if the widget is enabled, false if the widget is disabled.
     */
    bool isEnabled() const;
    
    /**
     * Sets whether the widget is visible
     *
     * The default value is true, a widget is default to visible
     *
     * @param visible   true if the widget is visible, false if the widget is hidden.
     */
    void setVisible(bool visible);
    
    /**
     * Determines if the widget is visible
     *
     * @return true if the widget is visible, false if the widget is hidden.
     */
    bool isVisible() const;
    
    /**
     * Sets whether the widget is bright
     *
     * The default value is true, a widget is default to bright
     *
     * @param visible   true if the widget is bright, false if the widget is dark.
     */
    void setBright(bool bright);
    
    /**
     * Determines if the widget is bright
     *
     * @return true if the widget is bright, false if the widget is dark.
     */
    bool isBright() const;
    
    /**
     * Sets whether the widget is touch enabled
     *
     * The default value is false, a widget is default to touch disabled
     *
     * @param visible   true if the widget is touch enabled, false if the widget is touch disabled.
     */
    virtual void setTouchEnabled(bool enabled);
    
    /**
     * To set the bright style of widget.
     *
     * @see BrightStyle
     *
     * @param style   BRIGHT_NORMAL the widget is normal state, BRIGHT_HIGHLIGHT the widget is height light state.
     */
    void setBrightStyle(BrightStyle style);
    
    /**
     * Determines if the widget is touch enabled
     *
     * @return true if the widget is touch enabled, false if the widget is touch disabled.
     */
    bool isTouchEnabled();
    
    /**
     * Sets whether the widget is on focus
     *
     * The default value is false, a widget is default to not on focus
     *
     * @param visible   true if the widget is on focus, false if the widget is not on focus.
     */
    bool isFocus();
    
    /**
     * Determines if the widget is on focus
     *
     * @return true if the widget is on focus, false if the widget is not on focus.
     */
    void setFocus(bool fucos);
    
    /**
     * Sets the Z order which stands for the drawing order, and reorder this widget in its parent's children array.
     *
     * The Z order of widget is relative to its "brothers": children of the same parent.
     * It's nothing to do with OpenGL's z vertex. This one only affects the draw order of widgets in cocos2d.
     * The larger number it is, the later this widget will be drawn in each message loop.
     * Please refer to setVertexZ(float) for the difference.
     *
     * @param nZOrder   Z order of this widget.
     */
    void setZOrder(int z);
    
    /**
     * Gets the Z order of this widget.
     *
     * @see setZOrder(int)
     *
     * @return The Z order.
     */
    int getZOrder();
    
    /**
     * Gets the left boundary position of this widget.
     *
     * @return The left boundary position of this widget.
     */
    float getLeftInParent();
    
    /**
     * Gets the bottom boundary position of this widget.
     *
     * @return The bottom boundary position of this widget.
     */
    float getBottomInParent();
    
    /**
     * Gets the right boundary position of this widget.
     *
     * @return The right boundary position of this widget.
     */
    float getRightInParent();
    
    /**
     * Gets the top boundary position of this widget.
     *
     * @return The top boundary position of this widget.
     */
    float getTopInParent();

    /**
     * Adds a child to the container.
     *
     * @param child A child widget
     */
    virtual bool addChild(UIWidget* child);
    
    /**
     * Removes a child from the container with a cleanup
     *
     * @param child     The child node which will be removed.
     *
     * @return the result of removing, succeeded or failed.
     */
    virtual bool removeChild(UIWidget* child,bool cleanup);
    
    /**
     * Removes this widget itself from its parent widget.
     * If the widget orphan, then it will destroy itself.
     * @param cleanup   true if all actions and callbacks on this widget should be removed, false otherwise.
     */
    virtual void removeFromParentAndCleanup(bool cleanup);
    
    /**
     * Removes all children from the container, and do a cleanup to all running actions depending on the cleanup parameter.
     *
     * @param cleanup   true if all running actions on all children nodes should be cleanup, false oterwise.
     */
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    
    /**
     *
     *
     * @param cleanup   true if all running actions on all children nodes should be cleanup, false oterwise.
     */
    void setUILayer(UILayer* uiLayer);

    void updateChildrenUILayer(UILayer* uiLayer);
    void disableUpdate();
    virtual void reorderChild(UIWidget* child);
    UIWidget* getChildByName(const char* name);
    UIWidget* getChildByTag(int tag);
    virtual CCArray* getChildren();
    
    
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
    
    
    void didNotSelectSelf();
    
    virtual void update(float dt){};
    bool parentAreaContainPoint(const CCPoint &pt);
    virtual void checkChildInfo(int handleState,UIWidget* sender,const CCPoint &touchPoint);
    
    
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
    
    virtual void ignoreContentAdaptWithSize(bool ignore);
    bool isIgnoreContentAdaptWithSize() const;
    CCPoint getWorldPosition();
    CCPoint convertToWorldSpace(const CCPoint& pt);
    virtual CCNode* getVirtualRenderer();
    
    void setUpdateEnabled(bool enable);
    bool isUpdateEnabled();
    
    /*******to be removed*******/
    virtual void setTouchEnable(bool enabled, bool containChildren = false);
    void disable(bool containChildren = false);
    void active(bool containChildren = false);
    bool isActive();
    void setBright(bool bright, bool containChild);
    CCRect getRect();
    CCNode* getValidNode(){return getVirtualRenderer();};
    void setWidgetZOrder(int z){setZOrder(z);};
    int getWidgetZOrder(){return getZOrder();};
    float getRelativeLeftPos(){return getLeftInParent();};
    float getRelativeBottomPos(){return getBottomInParent();};
    float getRelativeRightPos(){return getRightInParent();};
    float getRelativeTopPos(){return getTopInParent();};
    /***************************/
    
    /*temp action*/
    void setActionTag(int tag);
	int getActionTag();
    void setBindingAction(UIActionNode* actionNode);
    
    virtual const CCSize& getContentSize() const;
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
    CCSize m_customSize;
    LayoutParameter* m_pLayoutParameter;
    bool m_bIgnoreSize;
    CCArray* m_children;
    bool m_bAffectByClipping;
    /*temp action*/
    UIActionNode* m_pBindingAction;
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
