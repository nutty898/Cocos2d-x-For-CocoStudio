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

#include "UISlider.h"
#include "../../GUI/CCControlExtension/CCScale9Sprite.h"

NS_CC_EXT_BEGIN

UISlider::UISlider():
m_fBarLength(0.0),
m_nPercent(0),
m_fBarNodeScaleValue(1.0),
m_fTouchMoveStartLocation(0.0),
m_pBarNode(NULL),
m_pProgressBarNode(NULL),
m_pSlidBallNormalRenderer(NULL),
m_pSlidBallPressedRenderer(NULL),
m_pSlidBallDisabledRenderer(NULL),
m_pSlidBallRenderer(NULL),
m_pPercentListener(NULL),
m_pfnPercentSelector(NULL),
m_bScale9Enabled(false),
m_eBarTexType(UI_TEX_TYPE_LOCAL),
m_eBallNTexType(UI_TEX_TYPE_LOCAL),
m_eBallPTexType(UI_TEX_TYPE_LOCAL),
m_eBallDTexType(UI_TEX_TYPE_LOCAL),
m_eProgressBarTexType(UI_TEX_TYPE_LOCAL),
m_strTextureFile(""),
m_strProgressBarTextureFile(""),
m_strSlidBallNormalTextureFile(""),
m_strSlidBallPressedTextureFile(""),
m_strSlidBallDisabledTextureFile(""),
m_capInsets(CCRectZero)
{
}

UISlider::~UISlider()
{
    
}

UISlider* UISlider::create()
{
    UISlider* widget = new UISlider();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UISlider::initRenderer()
{
    UIWidget::initRenderer();
    m_pBarNode = CCSprite::create();
    m_pProgressBarNode = CCSprite::create();
    m_pRenderer->addChild(m_pBarNode, -1);
    m_pRenderer->addChild(m_pProgressBarNode, -1);
    m_pSlidBallNormalRenderer = CCSprite::create();
    m_pSlidBallPressedRenderer = CCSprite::create();
    m_pSlidBallPressedRenderer->setVisible(false);
    m_pSlidBallDisabledRenderer = CCSprite::create();
    m_pSlidBallDisabledRenderer->setVisible(false);
    m_pSlidBallRenderer = CCNode::create();
    m_pSlidBallRenderer->addChild(m_pSlidBallNormalRenderer);
    m_pSlidBallRenderer->addChild(m_pSlidBallPressedRenderer);
    m_pSlidBallRenderer->addChild(m_pSlidBallDisabledRenderer);
    m_pRenderer->addChild(m_pSlidBallRenderer);
}

void UISlider::loadBarTexture(const char* fileName, TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    m_strTextureFile = fileName;
    m_eBarTexType = texType;
    switch (m_eBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (m_bScale9Enabled)
            {
                dynamic_cast<CCScale9Sprite*>(m_pBarNode)->initWithFile(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pBarNode)->initWithFile(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (m_bScale9Enabled)
            {
                dynamic_cast<CCScale9Sprite*>(m_pBarNode)->initWithSpriteFrameName(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pBarNode)->initWithSpriteFrameName(fileName);
            }
            break;
        default:
            break;
    }
    if (m_bScale9Enabled)
    {
        dynamic_cast<CCScale9Sprite*>(m_pBarNode)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pBarNode)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pBarNode)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pBarNode)->setOpacity(getOpacity());
    }
    barRendererScaleChangedWithSize();
}

void UISlider::loadProgressBarTexture(const char *fileName, TextureResType texType)
{
    if (!fileName || strcmp(fileName, "") == 0)
    {
        return;
    }
    m_strProgressBarTextureFile = fileName;
    m_eProgressBarTexType = texType;
    switch (m_eBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            if (m_bScale9Enabled)
            {
                dynamic_cast<CCScale9Sprite*>(m_pProgressBarNode)->initWithFile(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pProgressBarNode)->initWithFile(fileName);
            }
            break;
        case UI_TEX_TYPE_PLIST:
            if (m_bScale9Enabled)
            {
                dynamic_cast<CCScale9Sprite*>(m_pProgressBarNode)->initWithSpriteFrameName(fileName);
            }
            else
            {
                dynamic_cast<CCSprite*>(m_pProgressBarNode)->initWithSpriteFrameName(fileName);
            }
            break;
        default:
            break;
    }
    if (m_bScale9Enabled)
    {
        dynamic_cast<CCScale9Sprite*>(m_pProgressBarNode)->setColor(getColor());
        dynamic_cast<CCScale9Sprite*>(m_pProgressBarNode)->setOpacity(getOpacity());
    }
    else
    {
        dynamic_cast<CCSprite*>(m_pProgressBarNode)->setColor(getColor());
        dynamic_cast<CCSprite*>(m_pProgressBarNode)->setOpacity(getOpacity());
    }
    setPercent(m_nPercent);
}

void UISlider::setScale9Enabled(bool able)
{
    if (m_bScale9Enabled == able)
    {
        return;
    }
    
    m_bScale9Enabled = able;
    if (m_bScale9Enabled)
    {
        m_bIgnoreSize = false;
    }
    m_pRenderer->removeChild(m_pBarNode, true);
    m_pRenderer->removeChild(m_pProgressBarNode, true);
    m_pBarNode = NULL;
    m_pProgressBarNode = NULL;
    if (m_bScale9Enabled)
    {
        m_pBarNode = CCScale9Sprite::create();
        m_pProgressBarNode = CCScale9Sprite::create();
    }
    else
    {
        m_pBarNode = CCSprite::create();
        m_pProgressBarNode = CCSprite::create();
    }
    loadBarTexture(m_strTextureFile.c_str(), m_eBarTexType);
    loadProgressBarTexture(m_strProgressBarTextureFile.c_str(), m_eProgressBarTexType);
    setCapInsets(m_capInsets);
    m_pRenderer->addChild(m_pBarNode, -1);
    m_pRenderer->addChild(m_pProgressBarNode, -1);
}

void UISlider::setCapInsets(const CCRect &capInsets)
{
    m_capInsets = capInsets;
    if (!m_bScale9Enabled)
    {
        return;
    }
    dynamic_cast<CCScale9Sprite*>(m_pBarNode)->setCapInsets(capInsets);
}

void UISlider::loadSlidBallTextures(const char* normal,const char* pressed,const char* disabled,TextureResType texType)
{
    loadSlidBallNormalTexture(normal, texType);
    loadSlidBallPressedTexture(pressed,texType);
    loadSlidBallDisabledTexture(disabled,texType);
}

void UISlider::loadSlidBallNormalTexture(const char* normal,TextureResType texType)
{
    if (!normal || strcmp(normal, "") == 0)
    {
        return;
    }
    m_strSlidBallNormalTextureFile = normal;
    m_eBallNTexType = texType;
    switch (m_eBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pSlidBallNormalRenderer->initWithFile(normal);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pSlidBallNormalRenderer->initWithSpriteFrameName(normal);
            break;
        default:
            break;
    }
    m_pSlidBallNormalRenderer->setColor(getColor());
    m_pSlidBallNormalRenderer->setOpacity(getOpacity());
}

void UISlider::loadSlidBallPressedTexture(const char* pressed,TextureResType texType)
{
    if (!pressed || strcmp(pressed, "") == 0)
    {
        return;
    }
    m_strSlidBallPressedTextureFile = pressed;
    m_eBallPTexType = texType;
    switch (m_eBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pSlidBallPressedRenderer->initWithFile(pressed);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pSlidBallPressedRenderer->initWithSpriteFrameName(pressed);
            break;
        default:
            break;
    }
    m_pSlidBallPressedRenderer->setColor(getColor());
    m_pSlidBallPressedRenderer->setOpacity(getOpacity());
}

void UISlider::loadSlidBallDisabledTexture(const char* disabled,TextureResType texType)
{
    if (!disabled || strcmp(disabled, "") == 0)
    {
        return;
    }
    m_strSlidBallDisabledTextureFile = disabled;
    m_eBallDTexType = texType;
    switch (m_eBarTexType)
    {
        case UI_TEX_TYPE_LOCAL:
            m_pSlidBallDisabledRenderer->initWithFile(disabled);
            break;
        case UI_TEX_TYPE_PLIST:
            m_pSlidBallDisabledRenderer->initWithSpriteFrameName(disabled);
            break;
        default:
            break;
    }
    m_pSlidBallDisabledRenderer->setColor(getColor());
    m_pSlidBallDisabledRenderer->setOpacity(getOpacity());
}

void UISlider::setPercent(int percent)
{
    m_nPercent = percent;
    float dis = m_fBarLength*(percent/100.0f);
    m_pSlidBallRenderer->setPosition(ccp(-m_fBarLength/2.0f + dis, 0.0f));
}

void UISlider::checkSlidBoundary()
{
    if (m_pSlidBallRenderer->getPosition().x > m_fBarLength/2.0f)
    {
        m_pSlidBallRenderer->setPosition(ccp(m_fBarLength/2.0f,0.0f));
    }
    else if(m_pSlidBallRenderer->getPosition().x < -m_fBarLength/2.0f)
    {
        m_pSlidBallRenderer->setPosition(ccp(-m_fBarLength/2.0f,0.0f));
    }
}

bool UISlider::onTouchBegan(const CCPoint &touchPoint)
{
    bool pass = UIWidget::onTouchBegan(touchPoint);
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    m_pSlidBallRenderer->setPosition(ccp(nsp.x,0));
//    m_pSlidBallRenderer->setPressState(WidgetStateSelected);
    m_nPercent = getPercentWithBallPos(m_pSlidBallRenderer->getPosition().x,0);
    percentChangedEvent();
    return pass;
}

void UISlider::onTouchMoved(const CCPoint &touchPoint)
{
    CCPoint nsp = m_pRenderer->convertToNodeSpace(touchPoint);
    m_pSlidBallRenderer->setPosition(ccp(nsp.x,0));
    checkSlidBoundary();
    m_nPercent = getPercentWithBallPos(m_pSlidBallRenderer->getPosition().x,0);
    percentChangedEvent();
}

void UISlider::onTouchEnded(const CCPoint &touchPoint)
{
    UIWidget::onTouchEnded(touchPoint);
//    m_pSlidBall->setPressState(WidgetStateNormal);
}

void UISlider::onTouchCancelled(const CCPoint &touchPoint)
{
    UIWidget::onTouchCancelled(touchPoint);
//    m_pSlidBall->setPressState(WidgetStateNormal);
}

float UISlider::getPercentWithBallPos(float px,float py)
{
    return (((px-(-m_fBarLength/2.0f))/m_fBarLength)*100.0f);
}

void UISlider::addPercentChangedEvent(CCObject *target, SEL_PushEvent selector)
{
    m_pPercentListener = target;
    m_pfnPercentSelector = selector;
}

void UISlider::percentChangedEvent()
{
    if (m_pPercentListener && m_pfnPercentSelector)
    {
        (m_pPercentListener->*m_pfnPercentSelector)(this);
    }
}

int UISlider::getPercent()
{
    return m_nPercent;
}

void UISlider::onSizeChanged()
{
    barRendererScaleChangedWithSize();
}

const CCSize& UISlider::getContentSize() const
{
    return m_pBarNode->getContentSize();
}

void UISlider::barRendererScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_size = m_pBarNode->getContentSize();
        m_fBarLength = m_size.width;
        m_pBarNode->setScale(1.0f);
    }
    else
    {
        m_fBarLength = m_size.width;
        if (m_bScale9Enabled)
        {
            dynamic_cast<CCScale9Sprite*>(m_pBarNode)->setPreferredSize(m_size);
        }
        else
        {
            CCSize textureSize = m_pBarNode->getContentSize();
            float scaleX = m_size.width / textureSize.width;
            float scaleY = m_size.height / textureSize.height;
            m_pBarNode->setScaleX(scaleX);
            m_pBarNode->setScaleY(scaleY);
        }
    }
    setPercent(m_nPercent);
}

void UISlider::onPressStateChangedToNormal()
{
    m_pSlidBallNormalRenderer->setVisible(true);
    m_pSlidBallPressedRenderer->setVisible(false);
    m_pSlidBallDisabledRenderer->setVisible(false);
}

void UISlider::onPressStateChangedToPressed()
{
    m_pSlidBallNormalRenderer->setVisible(false);
    m_pSlidBallPressedRenderer->setVisible(true);
    m_pSlidBallDisabledRenderer->setVisible(false);
}

void UISlider::onPressStateChangedToDisabled()
{
    m_pSlidBallNormalRenderer->setVisible(false);
    m_pSlidBallPressedRenderer->setVisible(false);
    m_pSlidBallDisabledRenderer->setVisible(true);
}
NS_CC_EXT_END