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

#ifndef __LAYOUTEXECUTANT_H__
#define __LAYOUTEXECUTANT_H__

#include "LayoutParameter.h"

NS_CC_EXT_BEGIN

typedef enum
{
    LAYOUT_DEFAULT,
    LAYOUT_LINEAR_VERTICAL,
    LAYOUT_LINEAR_HORIZONTAL,
    LAYOUT_RELATIVE
}LayoutType;

class LayoutExecutant : public CCObject
{
public:
    LayoutExecutant(){m_eLayoutType = LAYOUT_DEFAULT;};
    virtual ~LayoutExecutant(){};
    virtual void doLayout()=0;
    LayoutType getLayoutType(){return m_eLayoutType;};
protected:
    LayoutType m_eLayoutType;
};

class LinearVerticalLayoutExecutant : public LayoutExecutant
{
public:
    LinearVerticalLayoutExecutant(){m_eLayoutType = LAYOUT_LINEAR_VERTICAL;};
    virtual ~LinearVerticalLayoutExecutant(){};
    static LinearVerticalLayoutExecutant* create();
    virtual void doLayout();
};

class LinearHorizontalLayoutExecutant : public LayoutExecutant
{
public:
    LinearHorizontalLayoutExecutant(){m_eLayoutType = LAYOUT_LINEAR_HORIZONTAL;};
    virtual ~LinearHorizontalLayoutExecutant(){};
    static LinearHorizontalLayoutExecutant* create();
    virtual void doLayout();
protected:
    LayoutType m_eLayoutType;
};

class RelativeLayoutExecutant : public LayoutExecutant
{
public:
    RelativeLayoutExecutant(){m_eLayoutType = LAYOUT_RELATIVE;};
    virtual ~RelativeLayoutExecutant(){};
    static RelativeLayoutExecutant* create();
    virtual void doLayout();
protected:
    LayoutType m_eLayoutType;
};

NS_CC_EXT_END

#endif /* defined(__LayoutExecutant__) */
