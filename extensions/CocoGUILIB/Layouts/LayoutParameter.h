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

#ifndef __LAYOUTPARMETER_H__
#define __LAYOUTPARMETER_H__

#include "UILayoutDefine.h"

NS_CC_EXT_BEGIN

typedef enum
{
    LAYOUT_PARAMETER_NONE,
    LAYOUT_PARAMETER_LINEAR,
    LAYOUT_PARAMETER_RELATIVE
}LayoutParameterType;

class LayoutParameter : public CCObject
{
public:
    LayoutParameter() : m_margin(UIMargin()){m_eLayoutParameterType = LAYOUT_PARAMETER_NONE;};
    virtual ~LayoutParameter(){};
    static LayoutParameter* create();
    void setMargin(const UIMargin& margin);
    const UIMargin& getMargin() const;
    LayoutParameterType getLayoutType() const;
protected:
    UIMargin m_margin;
    LayoutParameterType m_eLayoutParameterType;
};

class LinearLayoutParameter : public LayoutParameter
{
public:
    LinearLayoutParameter() : m_eLinearGravity(LINEAR_GRAVITY_NONE){m_eLayoutParameterType = LAYOUT_PARAMETER_LINEAR;};
    virtual ~LinearLayoutParameter(){};
    static LinearLayoutParameter* create();
    void setGravity(UILinearGravity gravity);
    UILinearGravity getGravity() const;
protected:
    UILinearGravity m_eLinearGravity;
};

class RelativeLayoutParameter : public LayoutParameter
{
public:
    RelativeLayoutParameter() : m_eRelativeAlign(RELATIVE_ALIGN_NONE),m_strRelativeWidgetName(""),m_strRelativeLayoutName(""){m_eLayoutParameterType = LAYOUT_PARAMETER_RELATIVE;};
    virtual ~RelativeLayoutParameter(){};
    static RelativeLayoutParameter* create();
    void setAlign(UIRelativeAlign align);
    UIRelativeAlign getAlign() const;
    
    void setRelativeToWidgetName(const char* name);
    const char* getRelativeToWidgetName() const;
    
    void setRelativeName(const char* name);
    const char* getRelativeName() const;
protected:
    UIRelativeAlign m_eRelativeAlign;
    std::string m_strRelativeWidgetName;
    std::string m_strRelativeLayoutName;
};

NS_CC_EXT_END

#endif /* defined(__TestCpp__LayoutParameter__) */
