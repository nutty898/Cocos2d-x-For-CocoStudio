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

#include "UILabelBMFont.h"

NS_CC_EXT_BEGIN
    
UILabelBMFont::UILabelBMFont():
m_pLabelBMFont(NULL)
{
}

UILabelBMFont::~UILabelBMFont()
{
    
}

UILabelBMFont* UILabelBMFont::create()
{
    UILabelBMFont* widget = new UILabelBMFont();
    if (widget && widget->init())
    {
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return NULL;
}

void UILabelBMFont::initNodes()
{
    UIWidget::initNodes();
    m_pLabelBMFont = CCLabelBMFont::create();
    m_pRenderer->addChild(m_pLabelBMFont);
}

void UILabelBMFont::setFntFile(const char *fileName)
{
    m_pLabelBMFont->initWithString("", fileName);
    updateAnchorPoint();
    labelBMFontScaleChangedWithSize();
}

void UILabelBMFont::setText(const char* value)
{
	if (!value)
	{
		return;
	}
	m_pLabelBMFont->setString(value);
    labelBMFontScaleChangedWithSize();
}

const char* UILabelBMFont::getStringValue()
{
    return m_pLabelBMFont->getString();
}

void UILabelBMFont::setAnchorPoint(const CCPoint &pt)
{
    UIWidget::setAnchorPoint(pt);
    m_pLabelBMFont->setAnchorPoint(pt);
}

void UILabelBMFont::onSizeChanged()
{
    m_pLabelBMFont->setScaleX(0.5f);
//    CCLOG("cs w %f, cs h %f",m_pLabelBMFont->getContentSize().width,m_pLabelBMFont->getContentSize().height);
    labelBMFontScaleChangedWithSize();
}

void UILabelBMFont::labelBMFontScaleChangedWithSize()
{
    CCSize textureSize = m_pLabelBMFont->getContentSize();
    float scaleX = m_size.width / textureSize.width;
    float scaleY = m_size.height / textureSize.height;
    m_pLabelBMFont->setScaleX(scaleX);
    m_pLabelBMFont->setScaleY(scaleY);
}

NS_CC_EXT_END