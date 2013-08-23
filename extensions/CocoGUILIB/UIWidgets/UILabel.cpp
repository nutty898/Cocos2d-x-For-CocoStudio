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

#include "UILabel.h"

NS_CC_EXT_BEGIN

UILabel::UILabel():
m_bTouchScaleChangeAble(false),
m_sFontName("Thonburi"),
m_nFontSize(10),
m_fOnSelectedScaleOffset(0.5),
m_fNormalScaleValue(1),
m_pRenderLabel(NULL)
{
}

UILabel::~UILabel()
{
    
}

UILabel* UILabel::create()
{
    UILabel* widget = new UILabel();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

bool UILabel::init()
{
    if (UIWidget::init())
    {
        return true;
    }
    return false;
}

void UILabel::initRenderer()
{
    UIWidget::initRenderer();
    m_pRenderLabel = CCLabelTTF::create();
    m_pRenderer->addChild(m_pRenderLabel);
}

void UILabel::setText(const char* text)
{
	if (!text)
	{
		return;
	}
    std::string strText(text);
    m_pRenderLabel->setString(strText.c_str());
    labelScaleChangedWithSize();
}

const char* UILabel::getStringValue()
{
    return m_pRenderLabel->getString();
}

int UILabel::getStringLength()
{
    const char* str = m_pRenderLabel->getString();
    return strlen(str);
}

void UILabel::setFontSize(int size)
{
    m_pRenderLabel->setFontSize(size);
    labelScaleChangedWithSize();
}

void UILabel::setFontName(const char* name)
{
    m_pRenderLabel->setFontName(name);
    labelScaleChangedWithSize();
}

void UILabel::setTextAreaSize(const CCSize &size)
{
    m_pRenderLabel->setDimensions(size);
}

void UILabel::setTextHorizontalAlignment(CCTextAlignment alignment)
{
    m_pRenderLabel->setHorizontalAlignment(alignment);
}

void UILabel::setTextVerticalAlignment(CCVerticalTextAlignment alignment)
{
    m_pRenderLabel->setVerticalAlignment(alignment);
}

void UILabel::setTouchScaleChangeAble(bool able)
{
    m_bTouchScaleChangeAble = able;
    m_fNormalScaleValue = getScale();
}

bool UILabel::getTouchScaleChangeAble()
{
    return m_bTouchScaleChangeAble;
}

void UILabel::onPressStateChangedToNormal()
{
    if (!m_bTouchScaleChangeAble)
    {
        return;
    }
    clickScale(m_fNormalScaleValue);
}

void UILabel::onPressStateChangedToPressed()
{
    if (!m_bTouchScaleChangeAble)
    {
        return;
    }
    clickScale(m_fNormalScaleValue + m_fOnSelectedScaleOffset);
}

void UILabel::onPressStateChangedToDisabled()
{
    
}

void UILabel::clickScale(float scale)
{
    m_pRenderer->setScale(scale);
}

void UILabel::setFlipX(bool flipX)
{
    m_pRenderLabel->setFlipX(flipX);
}

void UILabel::setFlipY(bool flipY)
{
    m_pRenderLabel->setFlipY(flipY);
}

bool UILabel::isFlipX()
{
    return m_pRenderLabel->isFlipX();
}

bool UILabel::isFlipY()
{
    return m_pRenderLabel->isFlipY();
}

void UILabel::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pRenderLabel->setAnchorPoint(pt);
}

void UILabel::onSizeChanged()
{
    labelScaleChangedWithSize();
}

const CCSize& UILabel::getContentSize() const
{
    return m_pRenderLabel->getContentSize();
}

void UILabel::labelScaleChangedWithSize()
{
    if (m_bIgnoreSize)
    {
        m_pRenderLabel->setScale(1.0f);
        m_size = m_pRenderLabel->getContentSize();
    }
    else
    {
        CCSize textureSize = m_pRenderLabel->getContentSize();
        float scaleX = m_size.width / textureSize.width;
        float scaleY = m_size.height / textureSize.height;
        m_pRenderLabel->setScaleX(scaleX);
        m_pRenderLabel->setScaleY(scaleY);
    }
    
}

NS_CC_EXT_END