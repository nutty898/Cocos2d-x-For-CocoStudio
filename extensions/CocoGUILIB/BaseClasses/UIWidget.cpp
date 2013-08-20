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

#include "UIWidget.h"
#include "../System/UILayer.h"
#include "../Layouts/Layout.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CCBLENDPROTOCOL dynamic_cast<cocos2d::CCBlendProtocol*>(m_pRenderer)

#define DYNAMIC_CAST_CCRGBAPROTOCOL dynamic_cast<cocos2d::CCRGBAProtocol*>(m_pRenderer)

#define DYNAMIC_CAST_CCNODERGBA dynamic_cast<GUIRenderer*>(m_pRenderer)
    
UIWidget::UIWidget():
m_bEnabled(true),
m_bBright(true),
m_bFocus(false),
m_nWidgetZOrder(0),
m_pWidgetParent(NULL),
m_eBrightStyle(BRIGHT_NONE),
m_bTouchEnabled(true),
m_bTouchPassedEnabled(false),
m_nWidgetTag(-1),
m_bUpdateEnabled(false),
m_pRenderer(NULL),
m_strName("default"),
m_WidgetType(WidgetTypeWidget),
m_bVisible(true),
m_pPushListener(NULL),
m_pfnPushSelector(NULL),
m_pMoveListener(NULL),
m_pfnMoveSelector(NULL),
m_pReleaseListener(NULL),
m_pfnReleaseSelector(NULL),
m_pCancelListener(NULL),
m_pfnCancelSelector(NULL),
//m_bUseMergedTexture(false),
m_anchorPoint(ccp(0.5f, 0.5f)),
m_pUILayer(NULL),
m_nActionTag(0),
m_pLayoutParameter(NULL),
m_size(CCSizeMake(50.0f, 50.0f))
{
}

UIWidget::~UIWidget()
{
    
}

UIWidget* UIWidget::create()
{
    UIWidget* widget = new UIWidget();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIWidget::init()
{
    initRenderer();
    m_pRenderer->retain();
    m_pRenderer->setZOrder(m_nWidgetZOrder);
    CCRGBAProtocol* renderRGBA = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(true);
        renderRGBA->setCascadeOpacityEnabled(true);
    }
    //test
    setSize(m_size);
    setBright(true);
    return true;
}

void UIWidget::releaseResoures()
{
    m_pPushListener = NULL;
    m_pfnPushSelector = NULL;
    m_pMoveListener = NULL;
    m_pfnMoveSelector = NULL;
    m_pReleaseListener = NULL;
    m_pfnReleaseSelector = NULL;
    m_pCancelListener = NULL;
    m_pfnCancelSelector = NULL;
    setUpdateEnabled(false);
    if (m_pUILayer)
    {
        m_pUILayer->getInputManager()->removeManageredWidget(this);
        setUILayer(NULL);
    }
//    removeAllChildrenAndCleanUp(true);
    m_pRenderer->removeAllChildrenWithCleanup(true);
    m_pRenderer->removeFromParentAndCleanup(true);
    m_pRenderer->release();
}

void UIWidget::initRenderer()
{
    m_pRenderer = GUIRenderer::create();
}

void UIWidget::setSize(const CCSize &size)
{
    m_size = size;
    onSizeChanged();
}

const CCSize& UIWidget::getSize() const
{
    return m_size;
}

void UIWidget::onSizeChanged()
{
    
}

void UIWidget::setUILayer(UILayer *uiLayer)
{
    m_pUILayer = uiLayer;
}

void UIWidget::structureChangedEvent()
{
    if (m_pUILayer)
    {
        m_pUILayer->getInputManager()->uiSceneHasChanged();
    }
}

void UIWidget::setWidgetZOrder(int z)
{
    m_nWidgetZOrder = z;
    m_pRenderer->setZOrder(z);
    if (m_pWidgetParent)
    {
        ((Layout*)m_pWidgetParent)->reorderChild(this);
    }
}

int UIWidget::getWidgetZOrder()
{
    return m_nWidgetZOrder;
}

void UIWidget::setTouchEnabled(bool enable)
{
    m_bTouchEnabled = enable;
    structureChangedEvent();
}

bool UIWidget::isTouchEnabled()
{
    return m_bTouchEnabled;
}

void UIWidget::setUpdateEnabled(bool enable)
{
    m_bUpdateEnabled = enable;
    if (enable)
    {
        if (m_pUILayer)
        {
            m_pUILayer->addUpdateEnableWidget(this);
        }
    }
    else
    {
        if (m_pUILayer)
        {
            m_pUILayer->removeUpdateEnableWidget(this);
        }
    }
}

bool UIWidget::isUpdateEnabled()
{
    return m_bUpdateEnabled;
}

bool UIWidget::isFocus()
{
    return m_bFocus;
}

void UIWidget::setFocus(bool fucos)
{
    if (fucos == m_bFocus)
    {
        return;
    }
    m_bFocus = fucos;
    if (m_bBright)
    {
        if (m_bFocus)
        {
            setBrightStyle(BRIGHT_HIGHLIGHT);
        }
        else
        {
            setBrightStyle(BRIGHT_NORMAL);
        }
    }
    else
    {
        onPressStateChangedToDisabled();
    }
}

void UIWidget::setBright(bool bright)
{
    m_bBright = bright;
    if (m_bBright)
    {
        m_eBrightStyle = BRIGHT_NONE;
        setBrightStyle(BRIGHT_NORMAL);
    }
    else
    {
        onPressStateChangedToDisabled();
    }
}

void UIWidget::setBrightStyle(BrightStyle style)
{
    if (m_eBrightStyle == style)
    {
        return;
    }
    m_eBrightStyle = style;
    switch (m_eBrightStyle)
    {
        case BRIGHT_NORMAL:
            onPressStateChangedToNormal();
            break;
        case BRIGHT_HIGHLIGHT:
            onPressStateChangedToPressed();
            break;
        default:
            break;
    }
}

void UIWidget::onPressStateChangedToNormal()
{
    
}

void UIWidget::onPressStateChangedToPressed()
{
    
}

void UIWidget::onPressStateChangedToDisabled()
{
    
}

void UIWidget::didNotSelectSelf()
{
    
}

bool UIWidget::onTouchBegan(const CCPoint &touchPoint)
{
    setFocus(true);
    m_touchStartPos.x = touchPoint.x;
    m_touchStartPos.y = touchPoint.y;
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(0,this,touchPoint);
    }
    pushDownEvent();
    return m_bTouchPassedEnabled;
}

void UIWidget::onTouchMoved(const CCPoint &touchPoint)
{
    m_touchMovePos.x = touchPoint.x;
    m_touchMovePos.y = touchPoint.y;
    setFocus(hitTest(touchPoint));
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(1,this,touchPoint);
    }
    moveEvent();
}

void UIWidget::onTouchEnded(const CCPoint &touchPoint)
{
    m_touchEndPos.x = touchPoint.x;
    m_touchEndPos.y = touchPoint.y;
    bool focus = m_bFocus;
    setFocus(false);
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(2,this,touchPoint);
    }
    if (focus)
    {
        releaseUpEvent();
    }
    else
    {
        cancelUpEvent();
    }
}

void UIWidget::onTouchCancelled(const CCPoint &touchPoint)
{
    setFocus(false);
}

void UIWidget::onTouchLongClicked(const CCPoint &touchPoint)
{
    longClickEvent();
}

void UIWidget::pushDownEvent()
{
    if (m_pPushListener && m_pfnPushSelector)
    {
        (m_pPushListener->*m_pfnPushSelector)(this);
    }
}

void UIWidget::moveEvent()
{
    if (m_pMoveListener && m_pfnMoveSelector)
    {
        (m_pMoveListener->*m_pfnMoveSelector)(this);
    }
}

void UIWidget::releaseUpEvent()
{
    if (m_pReleaseListener && m_pfnReleaseSelector)
    {
        (m_pReleaseListener->*m_pfnReleaseSelector)(this);
    }
}

void UIWidget::cancelUpEvent()
{
    if (m_pCancelListener && m_pfnCancelSelector)
    {
        (m_pCancelListener->*m_pfnCancelSelector)(this);
    }
}

void UIWidget::longClickEvent()
{
    
}

void UIWidget::addPushDownEvent(CCObject*target, SEL_PushEvent selector)
{
    m_pPushListener = target;
    m_pfnPushSelector = selector;
}

void UIWidget::addMoveEvent(CCObject* target,SEL_MoveEvent selector)
{
    m_pMoveListener = target;
    m_pfnMoveSelector = selector;
}

void UIWidget::addReleaseEvent(CCObject* target,SEL_ReleaseEvent selector)
{
    m_pReleaseListener = target;
    m_pfnReleaseSelector = selector;
}

void UIWidget::addCancelEvent(CCObject *target, SEL_CancelEvent selector)
{
    m_pCancelListener = target;
    m_pfnCancelSelector = selector;
}

CCNode* UIWidget::getContainerNode()
{
    return m_pRenderer;
}

bool UIWidget::hitTest(const CCPoint &pt)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(pt);
    CCRect bb = CCRectMake(-m_size.width * m_anchorPoint.x, -m_size.height * m_anchorPoint.y, m_size.width, m_size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

bool UIWidget::checkVisibleDependParent(const CCPoint &pt)
{
    if (m_pWidgetParent)
    {
        bool bRet = false;
        if (m_pWidgetParent->hitTest(pt))
        {
            bRet = true;
        }
        if (bRet)
        {
            return m_pWidgetParent->checkVisibleDependParent(pt);
        }
        return false;
    }
    return true;
}

void UIWidget::checkChildInfo(int handleState, UIWidget *sender,const CCPoint &touchPoint)
{
    if (m_pWidgetParent)
    {
        m_pWidgetParent->checkChildInfo(handleState,sender,touchPoint);
    }
}

void UIWidget::setPosition(const CCPoint &pos)
{
    m_pRenderer->setPosition(pos);
}

void UIWidget::setAnchorPoint(const CCPoint &pt)
{
    m_anchorPoint = pt;
    m_pRenderer->setAnchorPoint(pt);
}

void UIWidget::updateAnchorPoint()
{
    setAnchorPoint(m_anchorPoint);
}

const CCPoint& UIWidget::getPosition()
{
    return m_pRenderer->getPosition();
}

const CCPoint& UIWidget::getAnchorPoint()
{
    return m_anchorPoint;
}

void UIWidget::setScale(float scale)
{
    m_pRenderer->setScale(scale);
}

float UIWidget::getScale()
{
    return m_pRenderer->getScale();
}

void UIWidget::setScaleX(float scaleX)
{
    m_pRenderer->setScaleX(scaleX);
}

float UIWidget::getScaleX()
{
    return m_pRenderer->getScaleX();
}

void UIWidget::setScaleY(float scaleY)
{
    m_pRenderer->setScaleY(scaleY);
}

float UIWidget::getScaleY()
{
    return m_pRenderer->getScaleY();
}

void UIWidget::setRotation(float rotation)
{
    m_pRenderer->setRotation(rotation);
}

float UIWidget::getRotation()
{
    return m_pRenderer->getRotation();
}

void UIWidget::setRotationX(float rotationX)
{
    m_pRenderer->setRotationX(rotationX);
}

float UIWidget::getRotationX()
{
    return m_pRenderer->getRotationX();
}

void UIWidget::setRotationY(float rotationY)
{
    m_pRenderer->setRotationY(rotationY);
}

float UIWidget::getRotationY()
{
    return m_pRenderer->getRotationY();
}

void UIWidget::setSkewX(float skewX)
{
    m_pRenderer->setSkewX(skewX);
}

float UIWidget::getSkewX()
{
    return m_pRenderer->getSkewX();
}

void UIWidget::setSkewY(float skewY)
{
    m_pRenderer->setSkewY(skewY);
}

float UIWidget::getSkewY()
{
    return m_pRenderer->getSkewY();
}

void UIWidget::setVisible(bool visible)
{
    m_bVisible = visible;
    m_pRenderer->setVisible(visible);
}

bool UIWidget::isVisible() const
{
    return m_bVisible;
}

bool UIWidget::isBright() const
{
    return m_bBright;
}

void UIWidget::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
    DYNAMIC_CAST_CCNODERGBA->setEnabled(enabled);
}

bool UIWidget::isEnabled() const
{
    return m_bEnabled;
}

float UIWidget::getRelativeLeftPos()
{
    float leftPos = 0.0f;
    switch (m_WidgetType)
    {
        case WidgetTypeWidget:
            leftPos = getPosition().x - getAnchorPoint().x * m_size.width;
            break;
        case WidgetTypeContainer:
            leftPos = getPosition().x;
            break;
        default:
            break;
    }
    return leftPos;
}

float UIWidget::getRelativeBottomPos()
{
    float bottomPos = 0.0f;
    switch (m_WidgetType)
    {
        case WidgetTypeWidget:
            bottomPos = getPosition().y - getAnchorPoint().y * m_size.height;
            break;
        case WidgetTypeContainer:
            bottomPos = getPosition().y;
            break;
        default:
            break;
    }
    return bottomPos;
}

float UIWidget::getRelativeRightPos()
{
    return getRelativeLeftPos() + m_size.width;
}

float UIWidget::getRelativeTopPos()
{
    return getRelativeBottomPos() + m_size.height;
}

UIWidget* UIWidget::getWidgetParent()
{
    return m_pWidgetParent;
}

void UIWidget::setWidgetParent(UIWidget* parent)
{
	m_pWidgetParent = parent;
}

CCAction* UIWidget::runAction(CCAction *action)
{
    return m_pRenderer->runAction(action);
}

void UIWidget::setActionManager(CCActionManager *actionManager)
{
    m_pRenderer->setActionManager(actionManager);
}

CCActionManager* UIWidget::getActionManager()
{
    return m_pRenderer->getActionManager();
}

void UIWidget::stopAllActions()
{
    m_pRenderer->stopAllActions();
}

void UIWidget::stopAction(CCAction *action)
{
    m_pRenderer->stopAction(action);
}

void UIWidget::stopActionByTag(int tag)
{
    m_pRenderer->stopActionByTag(tag);
}

CCAction* UIWidget::getActionByTag(int tag)
{
    return m_pRenderer->getActionByTag(tag);
}  

void UIWidget::setColor(const ccColor3B &color)
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setColor(color);
    }
}

const ccColor3B& UIWidget::getColor()
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->getColor();
    }
    return ccWHITE;
}

void UIWidget::setOpacity(int opacity)
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setOpacity(opacity);
    }
}

int UIWidget::getOpacity()
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->getOpacity();
    }
    return 0;
}

bool UIWidget::isCascadeOpacityEnabled()
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->isCascadeOpacityEnabled();
    }
    return false;
}

void UIWidget::setCascadeOpacityEnabled(bool cascadeOpacityEnabled)
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setCascadeOpacityEnabled(cascadeOpacityEnabled);
    }
}

bool UIWidget::isCascadeColorEnabled()
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        return rgbap->isCascadeColorEnabled();
    }
    return false;
}

void UIWidget::setCascadeColorEnabled(bool cascadeColorEnabled)
{
    CCRGBAProtocol* rgbap = DYNAMIC_CAST_CCRGBAPROTOCOL;
    if (rgbap)
    {
        rgbap->setCascadeColorEnabled(cascadeColorEnabled);
    }
}

void UIWidget::setBlendFunc(ccBlendFunc blendFunc)
{
    CCBlendProtocol * blendNode = DYNAMIC_CAST_CCBLENDPROTOCOL;
    if (blendNode)
    {
        blendNode->setBlendFunc(blendFunc);
    }
}

const CCPoint& UIWidget::getTouchStartPos()
{
    return m_touchStartPos;
}

const CCPoint& UIWidget::getTouchMovePos()
{
    return m_touchMovePos;
}

const CCPoint& UIWidget::getTouchEndPos()
{
    return m_touchEndPos;
}

void UIWidget::setWidgetTag(int tag)
{
    m_nWidgetTag = tag;
}

int UIWidget::getWidgetTag()
{
    return m_nWidgetTag;
}

void UIWidget::setName(const char* name)
{
    m_strName = name;
}

const char* UIWidget::getName()
{
    return m_strName.c_str();
}

WidgetType UIWidget::getWidgetType()
{
    return m_WidgetType;
}

void UIWidget::setActionTag(int tag)
{
	m_nActionTag = tag;
}

int UIWidget::getActionTag()
{
	return m_nActionTag;
}

void UIWidget::setLayoutParameter(LayoutParameter *parameter)
{
    if (m_pLayoutParameter)
    {
        CC_SAFE_RELEASE_NULL(m_pLayoutParameter);
    }
    m_pLayoutParameter = parameter;
    CC_SAFE_RETAIN(m_pLayoutParameter);
}

LayoutParameter* UIWidget::getLayoutParameter()
{
    return m_pLayoutParameter;
}

GUIRenderer::GUIRenderer():
m_bEnabled(true)
{
    
}

GUIRenderer::~GUIRenderer()
{
    
}

GUIRenderer* GUIRenderer::create()
{
    GUIRenderer* renderer = new GUIRenderer();
    if (renderer && renderer->init())
    {
        renderer->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(renderer);
    }
    return renderer;
}

void GUIRenderer::setEnabled(bool enabled)
{
    m_bEnabled = enabled;
}

bool GUIRenderer::getEnabled() const
{
    return m_bEnabled;
}

void GUIRenderer::visit()
{
    if (!m_bEnabled)
    {
        return;
    }
    CCNodeRGBA::visit();
}

NS_CC_EXT_END
