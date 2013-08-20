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

#include "Layout.h"
#include "../System/UILayer.h"
#include "../System/UIHelper.h"
#include "../Drawable/UIClippingLayer.h"

NS_CC_EXT_BEGIN

#define DYNAMIC_CAST_CLIPPINGLAYER dynamic_cast<UIClippingLayer*>(m_pRenderer)

Layout::Layout():
m_fWidth(0.0),
m_fHeight(0.0),
m_bClippingEnabled(false),
m_children(NULL),
m_pLayoutExecutant(NULL)
{
    m_WidgetType = WidgetTypeContainer;
}

Layout::~Layout()
{
    
}

Layout* Layout::create()
{
    Layout* layout = new Layout();
    if (layout && layout->init())
    {
        return layout;
    }
    CC_SAFE_DELETE(layout);
    return NULL;
}

void Layout::releaseResoures()
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
    removeAllChildrenAndCleanUp(true);
    m_pRenderer->removeAllChildrenWithCleanup(true);
    m_pRenderer->removeFromParentAndCleanup(true);
    m_pRenderer->release();
    m_children->release();
}

bool Layout::init()
{
    m_children = CCArray::create();
    m_children->retain();
    initRenderer();
    m_pRenderer->retain();
    m_pRenderer->setZOrder(m_nWidgetZOrder);
    CCRGBAProtocol* renderRGBA = dynamic_cast<CCRGBAProtocol*>(m_pRenderer);
    if (renderRGBA)
    {
        renderRGBA->setCascadeColorEnabled(false);
        renderRGBA->setCascadeOpacityEnabled(false);
    }
    setSize(CCSizeZero);
    setClippingEnabled(true);
    return true;
}

void Layout::setLayoutExecutant(LayoutExecutant *exe)
{
    if (m_pLayoutExecutant)
    {
        CC_SAFE_RELEASE_NULL(m_pLayoutExecutant);
    }
    m_pLayoutExecutant = exe;
    m_pLayoutExecutant->setLayout(this);
    CC_SAFE_RETAIN(m_pLayoutExecutant);
}

LayoutExecutant* Layout::getLayoutExecutant() const
{
    return m_pLayoutExecutant;
}

void Layout::initRenderer()
{
    m_pRenderer = UIClippingLayer::create();
}

bool Layout::isClippingEnabled()
{
    return m_bClippingEnabled;
}

bool Layout::addChild(UIWidget *child)
{
    if (!child)
    {
        return false;
    }
    if (m_children->containsObject(child))
    {
        return false;
    }
    child->setWidgetParent(this);
    int childrenCount = m_children->data->num;
    if (childrenCount <= 0)
    {
        m_children->addObject(child);
    }
    else
    {
        bool seekSucceed = false;
        ccArray* arrayChildren = m_children->data;
        for (int i=childrenCount-1; i>=0; --i)
        {
            UIWidget* widget = (UIWidget*)(arrayChildren->arr[i]);
            if (child->getWidgetZOrder() >= widget->getWidgetZOrder())
            {
                if (i == childrenCount-1)
                {
                    m_children->addObject(child);
                    seekSucceed = true;
                    break;
                }
                else
                {
                    m_children->insertObject(child, i+1);
                    seekSucceed = true;
                    break;
                }
            }
        }
        if (!seekSucceed)
        {
            m_children->insertObject(child,0);
        }
    }
    child->getContainerNode()->setZOrder(child->getWidgetZOrder());
    m_pRenderer->addChild(child->getContainerNode());
    
    if (m_pUILayer)
    {
        int childrenCount = m_children->data->num;
        ccArray* arrayChildren = m_children->data;
        for (int i=0; i<childrenCount; i++)
        {
            UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
            Layout* layout = dynamic_cast<Layout*>(child);
            if (layout)
            {
                layout->updateChildrenUILayer(m_pUILayer);
            }
        }
    }
    structureChangedEvent();
    return true;
}

bool Layout::removeChild(UIWidget *child, bool cleanup)
{
    if (!child)
    {
        return false;
    }
    if (cleanup)
    {
        if (m_children->containsObject(child))
        {
            m_children->removeObject(child);
            child->structureChangedEvent();
            child->releaseResoures();
            child->setWidgetParent(NULL);
            delete child;
        }
    }
    else
    {
        if (m_children->containsObject(child))
        {
            child->structureChangedEvent();
            Layout* layout = dynamic_cast<Layout*>(child);
            if (layout)
            {
                layout->disableUpdate();
                layout->updateChildrenUILayer(NULL);
            }
            m_pRenderer->removeChild(child->getContainerNode(), false);
            m_children->removeObject(child);
            child->setWidgetParent(NULL);
        }
    }
    return true;
}

void Layout::removeFromParentAndCleanup(bool cleanup)
{
    if (m_pWidgetParent)
    {
        ((Layout*)m_pWidgetParent)->removeChild(this, cleanup);
    }
    else
    {
        structureChangedEvent();
        releaseResoures();
        m_pWidgetParent = NULL;
        delete this;
    }
}

void Layout::removeAllChildrenAndCleanUp(bool cleanup)
{
    int times = m_children->data->num;
    for (int i=0;i<times;i++)
    {
        UIWidget* child = (UIWidget*)(m_children->lastObject());
        m_children->removeObject(child);
        child->structureChangedEvent();
        child->releaseResoures();
        delete child;
        child = NULL;
    }
}

void Layout::reorderChild(UIWidget* child)
{
    m_children->removeObject(child);
    int childrenCount = m_children->data->num;
    if (childrenCount <= 0)
    {
        m_children->addObject(child);
    }
    else
    {
        bool seekSucceed = false;
        ccArray* arrayChildren = m_children->data;
        for (int i=childrenCount-1; i>=0; --i)
        {
            UIWidget* widget = (UIWidget*)(arrayChildren->arr[i]);
            if (child->getWidgetZOrder() >= widget->getWidgetZOrder())
            {
                if (i == childrenCount-1)
                {
                    m_children->addObject(child);
                    seekSucceed = true;
                    break;
                }
                else
                {
                    m_children->insertObject(child, i+1);
                    seekSucceed = true;
                    break;
                }
            }
        }
        if (!seekSucceed)
        {
            m_children->insertObject(child,0);
        }
    }
    structureChangedEvent();
}

void Layout::updateChildrenUILayer(UILayer* uiLayer)
{
    setUILayer(uiLayer);
    setUpdateEnabled(isUpdateEnabled());
    int childrenCount = m_children->data->num;
    ccArray* arrayChildren = m_children->data;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        Layout* layout = dynamic_cast<Layout*>(child);
        if (layout)
        {
            layout->updateChildrenUILayer(m_pUILayer);
        }
    }
}

void Layout::disableUpdate()
{
    if (m_pUILayer)
    {
        m_pUILayer->removeUpdateEnableWidget(this);
    }
    int childrenCount = m_children->data->num;
    ccArray* arrayChildren = m_children->data;
    for (int i=0; i<childrenCount; i++)
    {
        UIWidget* child = (UIWidget*)(arrayChildren->arr[i]);
        Layout* layout = dynamic_cast<Layout*>(child);
        if (layout)
        {
            layout->disableUpdate();
        }
    }
}

void Layout::setEnabled(bool enabled)
{
    UIWidget::setEnabled(enabled);
    ccArray* arrayChildren = m_children->data;
    int childrenCount = arrayChildren->num;
    for (int i = 0; i < childrenCount; i++)
    {
        UIWidget* child = dynamic_cast<UIWidget*>(arrayChildren->arr[i]);
        child->setEnabled(enabled);
    }
}

UIWidget* Layout::getChildByName(const char *name)
{
    return CCUIHELPER->seekWidgetByName(this, name);
}

UIWidget* Layout::getChildByTag(int tag)
{
    return CCUIHELPER->seekWidgetByTag(this, tag);
}

CCArray* Layout::getChildren()
{
    return m_children;
}

bool Layout::hitTest(const CCPoint &pt)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(pt);
    CCRect bb = CCRectMake(0.0f, 0.0f, m_size.width, m_size.height);
    if (nsp.x >= bb.origin.x && nsp.x <= bb.origin.x + bb.size.width && nsp.y >= bb.origin.y && nsp.y <= bb.origin.y + bb.size.height)
    {
        return true;
    }
    return false;
}

void Layout::setClippingEnabled(bool able)
{
    m_bClippingEnabled = able;
    DYNAMIC_CAST_CLIPPINGLAYER->setClippingEnabled(able);
}

void Layout::onSizeChanged()
{
    DYNAMIC_CAST_CLIPPINGLAYER->setContentSize(m_size);
    if (m_pLayoutExecutant)
    {
        m_pLayoutExecutant->doLayout();
    }
}

NS_CC_EXT_END