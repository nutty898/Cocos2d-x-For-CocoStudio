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

#include "UICheckBox.h"

NS_CC_EXT_BEGIN

UICheckBox::UICheckBox():
m_pBackGroundBox(NULL),
m_pBackGroundSelectedBox(NULL),
m_pFrontCross(NULL),
m_bIsSelected(true),
m_pSelectListener(NULL),
m_pfnSelectSelector(NULL),
m_pUnSelectListener(NULL),
m_pfnUnSelectSelector(NULL),
m_pBackGroundBoxDisabled(NULL),
m_pFrontCrossDisabled(NULL),
m_eBackGroundTexType(UI_TEX_TYPE_LOCAL),
m_eBackGroundSelectedTexType(UI_TEX_TYPE_LOCAL),
m_eFrontCrossTexType(UI_TEX_TYPE_LOCAL),
m_eBackGroundDisabledTexType(UI_TEX_TYPE_LOCAL),
m_eFrontCrossDisabledTexType(UI_TEX_TYPE_LOCAL)
{
}

UICheckBox::~UICheckBox()
{
    
}

UICheckBox* UICheckBox::create()
{
    UICheckBox* widget = new UICheckBox();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UICheckBox::init()
{
    if (UIWidget::init())
    {
        setSelectedState(false);
        return true;
    }
    return false;
}

void UICheckBox::initRenderer()
{
    UIWidget::initRenderer();
    m_pBackGroundBox = CCSprite::create();
    m_pBackGroundSelectedBox = CCSprite::create();
    m_pFrontCross = CCSprite::create();
    m_pBackGroundBoxDisabled = CCSprite::create();
    m_pFrontCrossDisabled = CCSprite::create();
    m_pRenderer->addChild(m_pBackGroundBox);
    m_pRenderer->addChild(m_pBackGroundSelectedBox);
    m_pRenderer->addChild(m_pFrontCross);
    m_pRenderer->addChild(m_pBackGroundBoxDisabled);
    m_pRenderer->addChild(m_pFrontCrossDisabled);
}

void UICheckBox::loadTextures(const char *backGround, const char *backGroundSelected, const char *cross,const char* backGroundDisabled,const char* frontCrossDisabled,TextureResType texType)
{
    loadBackGroundTexture(backGround,texType);
    loadBackGroundSelectedTexture(backGroundSelected,texType);
    loadFrontCrossTexture(cross,texType);
    loadBackGroundDisabledTexture(backGroundDisabled,texType);
    loadFrontCrossDisabledTexture(frontCrossDisabled,texType);
}

void UICheckBox::loadBackGroundTexture(const char *backGround,TextureResType texType)
{
    if (!backGround || strcmp(backGround, "") == 0)
    {
        return;
    }
//    setUseMergedTexture(useSpriteFrame);
    m_eBackGroundTexType = texType;
    switch (m_eBackGroundTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pBackGroundBox->initWithFile(backGround);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pBackGroundBox->initWithSpriteFrameName(backGround);
            break;
        default:
            break;
    }
    m_pBackGroundBox->setColor(getColor());
    m_pBackGroundBox->setOpacity(getOpacity());
    backGroundTextureScaleChangedWithSize();
}

void UICheckBox::loadBackGroundSelectedTexture(const char *backGroundSelected,TextureResType texType)
{
    if (!backGroundSelected || strcmp(backGroundSelected, "") == 0)
    {
        return;
    }
//    setUseMergedTexture(useSpriteFrame);
    m_eBackGroundSelectedTexType = texType;
    switch (m_eBackGroundSelectedTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pBackGroundSelectedBox->initWithFile(backGroundSelected);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pBackGroundSelectedBox->initWithSpriteFrameName(backGroundSelected);
            break;
        default:
            break;
    }
    m_pBackGroundSelectedBox->setColor(getColor());
    m_pBackGroundSelectedBox->setOpacity(getOpacity());
    backGroundSelectedTextureScaleChangedWithSize();
}

void UICheckBox::loadFrontCrossTexture(const char *cross,TextureResType texType)
{
    if (!cross || strcmp(cross, "") == 0)
    {
        return;
    }
//    setUseMergedTexture(useSpriteFrame);
    m_eFrontCrossTexType = texType;
    switch (m_eFrontCrossTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pFrontCross->initWithFile(cross);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pFrontCross->initWithSpriteFrameName(cross);
            break;
        default:
            break;
    }
    m_pFrontCross->setColor(getColor());
    m_pFrontCross->setOpacity(getOpacity());
    frontCrossTextureScaleChangedWithSize();
}

void UICheckBox::loadBackGroundDisabledTexture(const char *backGroundDisabled,TextureResType texType)
{
    if (!backGroundDisabled || strcmp(backGroundDisabled, "") == 0)
    {
        return;
    }
//    setUseMergedTexture(useSpriteFrame);
    m_eBackGroundDisabledTexType = texType;
    switch (m_eBackGroundDisabledTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pBackGroundBoxDisabled->initWithFile(backGroundDisabled);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pBackGroundBoxDisabled->initWithSpriteFrameName(backGroundDisabled);
            break;
        default:
            break;
    }
    m_pBackGroundBoxDisabled->setColor(getColor());
    m_pBackGroundBoxDisabled->setOpacity(getOpacity());
    backGroundDisabledTextureScaleChangedWithSize();
}

void UICheckBox::loadFrontCrossDisabledTexture(const char *frontCrossDisabled,TextureResType texType)
{
    if (!frontCrossDisabled || strcmp(frontCrossDisabled, "") == 0)
    {
        return;
    }
//    setUseMergedTexture(useSpriteFrame);
    m_eFrontCrossDisabledTexType = texType;
    switch (m_eFrontCrossDisabledTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pFrontCrossDisabled->initWithFile(frontCrossDisabled);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pFrontCrossDisabled->initWithSpriteFrameName(frontCrossDisabled);
            break;
        default:
            break;
    }
    m_pFrontCrossDisabled->setColor(getColor());
    m_pFrontCross->setOpacity(getOpacity());
    frontCrossDisabledTextureScaleChangedWithSize();
}

void UICheckBox::onTouchEnded(const CCPoint &touchPoint)
{
    if (m_bFocus)
    {
        releaseUpEvent();
        if (m_bIsSelected){
            setSelectedState(false);
            unSelectedEvent();
        }
        else
        {
            setSelectedState(true);
            selectedEvent();
        }
    }
    setFocus(false);
    m_pWidgetParent->checkChildInfo(2,this,touchPoint);
}

void UICheckBox::onPressStateChangedToNormal()
{
    m_pBackGroundBox->setVisible(true);
    m_pBackGroundSelectedBox->setVisible(false);
    m_pBackGroundBoxDisabled->setVisible(false);
    m_pFrontCrossDisabled->setVisible(false);
}

void UICheckBox::onPressStateChangedToPressed()
{
    m_pBackGroundBox->setVisible(false);
    m_pBackGroundSelectedBox->setVisible(true);
    m_pBackGroundBoxDisabled->setVisible(false);
    m_pFrontCrossDisabled->setVisible(false);
}

void UICheckBox::onPressStateChangedToDisabled()
{
    m_pBackGroundBox->setVisible(false);
    m_pBackGroundSelectedBox->setVisible(false);
    m_pBackGroundBoxDisabled->setVisible(true);
    m_pFrontCross->setVisible(false);
    if (m_bIsSelected)
    {
        m_pFrontCrossDisabled->setVisible(true);
    }
}

void UICheckBox::setSelectedState(bool selected)
{
    if (selected == m_bIsSelected)
    {
        return;
    }
    m_bIsSelected = selected;
    m_pFrontCross->setVisible(m_bIsSelected);
}

bool UICheckBox::getSelectedState()
{
    return m_bIsSelected;
}

void UICheckBox::selectedEvent()
{
    if (m_pSelectListener && m_pfnSelectSelector)
    {
        (m_pSelectListener->*m_pfnSelectSelector)(this);
    }
}

void UICheckBox::unSelectedEvent()
{
    if (m_pUnSelectListener && m_pfnUnSelectSelector)
    {
        (m_pUnSelectListener->*m_pfnUnSelectSelector)(this);
    }
}

void UICheckBox::addSelectEvent(CCObject *target, SEL_SelectEvent selector)
{
    m_pSelectListener = target;
    m_pfnSelectSelector = selector;
}

void UICheckBox::addUnSelectEvent(CCObject *target, SEL_UnSelectEvent selector)
{
    m_pUnSelectListener = target;
    m_pfnUnSelectSelector = selector;
}

void UICheckBox::setFlipX(bool flipX)
{
    m_pBackGroundBox->setFlipX(flipX);
    m_pBackGroundSelectedBox->setFlipX(flipX);
    m_pFrontCross->setFlipX(flipX);
    m_pBackGroundBoxDisabled->setFlipX(flipX);
    m_pFrontCrossDisabled->setFlipX(flipX);
}

void UICheckBox::setFlipY(bool flipY)
{
    m_pBackGroundBox->setFlipX(flipY);
    m_pBackGroundSelectedBox->setFlipY(flipY);
    m_pFrontCross->setFlipY(flipY);
    m_pBackGroundBoxDisabled->setFlipY(flipY);
    m_pFrontCrossDisabled->setFlipY(flipY);
}

bool UICheckBox::isFlipX()
{
    return m_pBackGroundBox->isFlipX();
}

bool UICheckBox::isFlipY()
{
    return m_pBackGroundBox->isFlipY();
}

void UICheckBox::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pBackGroundBox->setAnchorPoint(pt);
    m_pBackGroundSelectedBox->setAnchorPoint(pt);
    m_pBackGroundBoxDisabled->setAnchorPoint(pt);
    m_pFrontCross->setAnchorPoint(pt);
    m_pFrontCrossDisabled->setAnchorPoint(pt);
}

void UICheckBox::onSizeChanged()
{
    backGroundTextureScaleChangedWithSize();
    backGroundSelectedTextureScaleChangedWithSize();
    frontCrossTextureScaleChangedWithSize();
    backGroundDisabledTextureScaleChangedWithSize();
    frontCrossDisabledTextureScaleChangedWithSize();
}

const CCSize& UICheckBox::getContentSize() const
{
    return m_pBackGroundBox->getContentSize();
}

void UICheckBox::backGroundTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pBackGroundBox->setScale(1.0f);
    }
    else
    {
        CCSize textureSize = m_pBackGroundBox->getContentSize();
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pBackGroundBox->setScaleX(scaleX);
        m_pBackGroundBox->setScaleY(scaleY);
    }
}

void UICheckBox::backGroundSelectedTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pBackGroundSelectedBox->setScale(1.0f);
    }
    else
    {
        CCSize textureSize = m_pBackGroundSelectedBox->getContentSize();
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pBackGroundSelectedBox->setScaleX(scaleX);
        m_pBackGroundSelectedBox->setScaleY(scaleY);

    }
}

void UICheckBox::frontCrossTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pFrontCross->setScale(1.0f);
    }
    else
    {
        CCSize textureSize = m_pFrontCross->getContentSize();
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pFrontCross->setScaleX(scaleX);
        m_pFrontCross->setScaleY(scaleY);
    }
}

void UICheckBox::backGroundDisabledTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pBackGroundBoxDisabled->setScale(1.0f);
    }
    else
    {
        CCSize textureSize = m_pBackGroundBoxDisabled->getContentSize();
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pBackGroundBoxDisabled->setScaleX(scaleX);
        m_pBackGroundBoxDisabled->setScaleY(scaleY);
    }
}

void UICheckBox::frontCrossDisabledTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pFrontCrossDisabled->setScale(1.0f);
    }
    else
    {
        CCSize textureSize = m_pFrontCrossDisabled->getContentSize();
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pFrontCrossDisabled->setScaleX(scaleX);
        m_pFrontCrossDisabled->setScaleY(scaleY);
    }
}

NS_CC_EXT_END