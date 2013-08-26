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

#include "UIButton.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN
    
UIButton::UIButton():
m_pButtonNormal(NULL),
m_pButtonClicked(NULL),
m_pButtonDisable(NULL),
m_bScale9Enabled(false),
m_strClickedFileName(""),
m_strDisabledFileName(""),
m_strNormalFileName(""),
m_capInsets(CCRectZero),
m_eNormalTexType(UI_TEX_TYPE_LOCAL),
m_ePressedTexType(UI_TEX_TYPE_LOCAL),
m_eDisabledTexType(UI_TEX_TYPE_LOCAL),
m_normalTextureSize(m_size),
m_pressedTextureSize(m_size),
m_disabledTextureSize(m_size)
{
    
}

UIButton::~UIButton()
{
    
}

UIButton* UIButton::create()
{
    UIButton* widget = new UIButton();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UIButton::init()
{
    if (UIWidget::init())
    {
        return true;
    }
    return false;
}

void UIButton::initRenderer()
{
    UIWidget::initRenderer();
    m_pButtonNormal = CCSprite::create();
    m_pButtonClicked = CCSprite::create();
    m_pButtonDisable = CCSprite::create();
    m_pRenderer->addChild(m_pButtonNormal,-1);
    m_pRenderer->addChild(m_pButtonClicked,-1);
    m_pRenderer->addChild(m_pButtonDisable,-1);
}

void UIButton::setScale9Enabled(bool able)
{
    if (m_bScale9Enabled == able)
    {
        return;
    }
    

    
    m_eBrightStyle = BRIGHT_NONE;
    m_bScale9Enabled = able;
    if (m_bScale9Enabled)
    {
        m_bIgnoreSize = false;
    }
    
    m_pRenderer->removeChild(m_pButtonNormal, true);
    m_pRenderer->removeChild(m_pButtonClicked, true);
    m_pRenderer->removeChild(m_pButtonDisable, true);
    
    m_pButtonNormal = NULL;
    m_pButtonClicked = NULL;
    m_pButtonDisable = NULL;
    if (m_bScale9Enabled)
    {
        m_pButtonNormal = CCScale9Sprite::create();
        m_pButtonClicked = CCScale9Sprite::create();
        m_pButtonDisable = CCScale9Sprite::create();
    }
    else
    {
        m_pButtonNormal = CCSprite::create();
        m_pButtonClicked = CCSprite::create();
        m_pButtonDisable = CCSprite::create();
    }
//    setTextures(m_strNormalFileName.c_str(), m_strClickedFileName.c_str(), m_strDisabledFileName.c_str(),getUseMergedTexture());
    loadNormalTexture(m_strNormalFileName.c_str(), m_eNormalTexType);
    loadPressedTexture(m_strClickedFileName.c_str(), m_ePressedTexType);
    loadDisabledTexture(m_strDisabledFileName.c_str(), m_eDisabledTexType);
    m_pRenderer->addChild(m_pButtonNormal,-1);
    m_pRenderer->addChild(m_pButtonClicked,-1);
    m_pRenderer->addChild(m_pButtonDisable,-1);
    setCapInsets(m_capInsets);
    setBright(m_bBright);
    
}

void UIButton::loadTextures(const char* normal,const char* selected,const char* disabled,TextureResType texType)
{
    loadNormalTexture(normal,texType);
    loadPressedTexture(selected,texType);
    loadDisabledTexture(disabled,texType);
}

void UIButton::loadNormalTexture(const char* normal,TextureResType texType)
{
    if (!normal || strcmp(normal, "") == 0)
    {
        return;
    }
    m_strNormalFileName = normal;
//    setUseMergedTexture(useSpriteFrame);
    m_eNormalTexType = texType;
    if (m_bScale9Enabled)
    {
        switch (m_eNormalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->initWithFile(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->setOpacity(getOpacity());
    }
    else
    {
        switch (m_eNormalTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCSprite*>(m_pButtonNormal)->initWithFile(normal);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCSprite*>(m_pButtonNormal)->initWithSpriteFrameName(normal);
                break;
            default:
                break;
        }
        dynamic_cast<CCSprite*>(m_pButtonNormal)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pButtonNormal)->setOpacity(getOpacity());
    }
    m_normalTextureSize = m_pButtonNormal->getContentSize();
    updateAnchorPoint();
    normalTextureScaleChangedWithSize();
}

void UIButton::loadPressedTexture(const char* selected,TextureResType texType)
{
    if (!selected || strcmp(selected, "") == 0)
    {
        return;
    }
    m_strClickedFileName = selected;
//    setUseMergedTexture(useSpriteFrame);
    m_ePressedTexType = texType;
    if (m_bScale9Enabled)
    {
        switch (m_ePressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->initWithFile(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->setOpacity(getOpacity());
    }
    else
    {
        switch (m_ePressedTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCSprite*>(m_pButtonClicked)->initWithFile(selected);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCSprite*>(m_pButtonClicked)->initWithSpriteFrameName(selected);
                break;
            default:
                break;
        }
        dynamic_cast<CCSprite*>(m_pButtonClicked)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pButtonClicked)->setOpacity(getOpacity());
    }
    m_pressedTextureSize = m_pButtonClicked->getContentSize();
    updateAnchorPoint();
    pressedTextureScaleChangedWithSize();
}

void UIButton::loadDisabledTexture(const char* disabled,TextureResType texType)
{
    if (!disabled || strcmp(disabled, "") == 0)
    {
        return;
    }
    m_strDisabledFileName = disabled;
//    setUseMergedTexture(useSpriteFrame);
    m_eDisabledTexType = texType;
    if (m_bScale9Enabled)
    {
        switch (m_eDisabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->initWithFile(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
        dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->setOpacity(getOpacity());
    }
    else
    {
        switch (m_eDisabledTexType)
        {
            case UI_TEX_TYPE_LOCAL:
                dynamic_cast<CCSprite*>(m_pButtonDisable)->initWithFile(disabled);
                break;
            case UI_TEX_TYPE_PLIST:
                dynamic_cast<CCSprite*>(m_pButtonDisable)->initWithSpriteFrameName(disabled);
                break;
            default:
                break;
        }
        dynamic_cast<CCSprite*>(m_pButtonDisable)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pButtonDisable)->setOpacity(getOpacity());
    }
    m_disabledTextureSize = m_pButtonDisable->getContentSize();
    updateAnchorPoint();
    disabledTextureScaleChangedWithSize();
}

void UIButton::setCapInsets(const CCRect &capInsets)
{
    m_capInsets = capInsets;
    if (!m_bScale9Enabled)
    {
        return;
    }
    dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->setCapInsets(capInsets);
    dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->setCapInsets(capInsets);
    dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->setCapInsets(capInsets);
}

void UIButton::onPressStateChangedToNormal()
{
    m_pButtonNormal->setVisible(true);
    m_pButtonClicked->setVisible(false);
    m_pButtonDisable->setVisible(false);
}

void UIButton::onPressStateChangedToPressed()
{
    m_pButtonNormal->setVisible(false);
    m_pButtonClicked->setVisible(true);
    m_pButtonDisable->setVisible(false);
}

void UIButton::onPressStateChangedToDisabled()
{
    m_pButtonNormal->setVisible(false);
    m_pButtonClicked->setVisible(false);
    m_pButtonDisable->setVisible(true);
}

void UIButton::setFlipX(bool flipX)
{
    if (m_bScale9Enabled)
    {
        return;
    }
    dynamic_cast<CCSprite*>(m_pButtonNormal)->setFlipX(flipX);
    dynamic_cast<CCSprite*>(m_pButtonClicked)->setFlipX(flipX);
    dynamic_cast<CCSprite*>(m_pButtonDisable)->setFlipX(flipX);
}

void UIButton::setFlipY(bool flipY)
{
    if (m_bScale9Enabled)
    {
        return;
    }
    dynamic_cast<CCSprite*>(m_pButtonNormal)->setFlipY(flipY);
    dynamic_cast<CCSprite*>(m_pButtonClicked)->setFlipY(flipY);
    dynamic_cast<CCSprite*>(m_pButtonDisable)->setFlipY(flipY);
}

bool UIButton::isFlipX()
{
    if (m_bScale9Enabled)
    {
        return false;
    }
    return dynamic_cast<CCSprite*>(m_pButtonNormal)->isFlipX();
}

bool UIButton::isFlipY()
{
    if (m_bScale9Enabled)
    {
        return false;
    }
    return dynamic_cast<CCSprite*>(m_pButtonNormal)->isFlipY();
}

void UIButton::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pButtonNormal->setAnchorPoint(pt);
    m_pButtonClicked->setAnchorPoint(pt);
    m_pButtonDisable->setAnchorPoint(pt);
}

void UIButton::setNormalSpriteFrame(CCSpriteFrame *frame)
{
    if (!frame)
    {
        return;
    }
    if (m_bScale9Enabled)
    {
        dynamic_cast<CCScale9Sprite*>(m_pButtonNormal)->setSpriteFrame(frame);
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pButtonNormal)->setDisplayFrame(frame);
    }
}

void UIButton::setPressedSpriteFrame(CCSpriteFrame *frame)
{
    if (!frame)
    {
        return;
    }
    if (m_bScale9Enabled)
    {
        dynamic_cast<CCScale9Sprite*>(m_pButtonClicked)->setSpriteFrame(frame);
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pButtonClicked)->setDisplayFrame(frame);
    }
}

void UIButton::setDisabledSpriteFrame(CCSpriteFrame *frame)
{
    if (!frame)
    {
        return;
    }
    if (m_bScale9Enabled)
    {
        dynamic_cast<CCScale9Sprite*>(m_pButtonDisable)->setSpriteFrame(frame);
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pButtonDisable)->setDisplayFrame(frame);
    }
}

void UIButton::onSizeChanged()
{
    normalTextureScaleChangedWithSize();
    pressedTextureScaleChangedWithSize();
    disabledTextureScaleChangedWithSize();
}

const CCSize& UIButton::getContentSize() const
{
    return m_normalTextureSize;
}

void UIButton::normalTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
//        if (m_bScale9Enabled)
//        {
//            m_pButtonNormal->setContentSize(m_normalTextureSize);
//        }
//        else
        {
            m_pButtonNormal->setScale(1.0f);
        }
        m_size = m_normalTextureSize;
    }
    else
    {
        if (m_bScale9Enabled)
        {
            m_pButtonNormal->setContentSize(m_size);
        }
        else
        {
            float scaleX = m_size.width / m_normalTextureSize.width;
            float scaleY = m_size.height / m_normalTextureSize.height;
            m_pButtonNormal->setScaleX(scaleX);
            m_pButtonNormal->setScaleY(scaleY);
        }
    }
}

void UIButton::pressedTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
//        if (m_bScale9Enabled)
//        {
//            m_pButtonClicked->setContentSize(m_pressedTextureSize);
//        }
//        else
        {
            m_pButtonClicked->setScale(1.0f);
        }
    }
    else
    {
        if (m_bScale9Enabled)
        {
            m_pButtonClicked->setContentSize(m_size);
        }
        else
        {
            float scaleX = m_size.width / m_pressedTextureSize.width;
            float scaleY = m_size.height / m_pressedTextureSize.height;
            m_pButtonClicked->setScaleX(scaleX);
            m_pButtonClicked->setScaleY(scaleY);
        }
    }
}

void UIButton::disabledTextureScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
//        if (m_bScale9Enabled)
//        {
//            m_pButtonDisable->setContentSize(m_disabledTextureSize);
//        }
//        else
        {
            m_pButtonDisable->setScale(1.0f);
        }
    }
    else
    {
        if (m_bScale9Enabled)
        {
            m_pButtonDisable->setContentSize(m_size);
        }
        else
        {
            float scaleX = m_size.width / m_disabledTextureSize.width;
            float scaleY = m_size.height / m_disabledTextureSize.height;
            m_pButtonDisable->setScaleX(scaleX);
            m_pButtonDisable->setScaleY(scaleY);
        }
    }
}

NS_CC_EXT_END