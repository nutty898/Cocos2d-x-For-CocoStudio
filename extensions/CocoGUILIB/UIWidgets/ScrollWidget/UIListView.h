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

#ifndef __UILISTVIEW_H__
#define __UILISTVIEW_H__

#include "Layout.h"

NS_CC_EXT_BEGIN

typedef enum LISTVIEW_DIR
{
    LISTVIEW_DIR_NONE,
    LISTVIEW_DIR_VERTICAL,
    LISTVIEW_DIR_HORIZONTAL
}ListViewDirection;

typedef enum LISTVIEW_MOVE_DIR
{
    LISTVIEW_MOVE_DIR_NONE,
    LISTVIEW_MOVE_DIR_UP,
    LISTVIEW_MOVE_DIR_DOWN,
    LISTVIEW_MOVE_DIR_LEFT,
    LISTVIEW_MOVE_DIR_RIGHT,
}ListViewMoveDirection;

typedef void (cocos2d::CCObject::*SEL_ListViewInitChildEvent)(cocos2d::CCObject*);
typedef void (cocos2d::CCObject::*SEL_ListViewUpdateChildEvent)(cocos2d::CCObject*);
#define coco_ListView_InitChild_selector(_SELECTOR) (SEL_ListViewInitChildEvent)(&_SELECTOR)
#define coco_ListView_UpdateChild_selector(_SELECTOR) (SEL_ListViewUpdateChildEvent)(&_SELECTOR)

class UIListView : public Layout
{
public:
    UIListView();
    virtual ~UIListView();
    static UIListView* create();
    virtual bool addChild(UIWidget* widget);
    virtual void removeAllChildrenAndCleanUp(bool cleanup);
    virtual bool removeChild(UIWidget* child, bool cleanup);
    
    virtual bool onTouchBegan(const CCPoint &touchPoint);
    virtual void onTouchMoved(const CCPoint &touchPoint);
    virtual void onTouchEnded(const CCPoint &touchPoint);
    virtual void onTouchCancelled(const CCPoint &touchPoint);
    virtual void onTouchLongClicked(const CCPoint &touchPoint);
    
    void setDirection(ListViewDirection dir);
    ListViewDirection getDirection();
    
    void initChildWithDataLength(int length);
    int getDataLength();
    
    UIWidget* getUpdateChild();
    int getUpdateDataIndex();
    bool getUpdateSuccess();
    void setUpdateSuccess(bool sucess);
    
    void addInitChildEvent(cocos2d::CCObject* target, SEL_ListViewInitChildEvent seletor);
    void addUpdateChildEvent(cocos2d::CCObject* target, SEL_ListViewUpdateChildEvent selector);
    
protected:
    virtual bool init();
    virtual void update(float dt);
    virtual void onSizeChanged();
    
    void setMoveDirection(ListViewMoveDirection dir);
    ListViewMoveDirection getMoveDirection();
    
    virtual void resetProperty();
    
    virtual void handlePressLogic(const CCPoint &touchPoint);
    virtual void handleMoveLogic(const CCPoint &touchPoint);
    virtual void handleReleaseLogic(const CCPoint &touchPoint);
    virtual void interceptTouchEvent(int handleState,UIWidget* sender,const CCPoint &touchPoint);
    virtual void checkChildInfo(int handleState,UIWidget* sender,const CCPoint &touchPoint);
    
    void moveChildren(float offset);
    virtual bool scrollChildren(float touchOffset);
    void autoScrollChildren(float dt);
    float getCurAutoScrollDistance(float time);
    void startAutoScrollChildren(float v);
    void stopAutoScrollChildren();
    void recordSlidTime(float dt);
    void startRecordSlidAction();
    virtual void endRecordSlidAction();
    
    UIWidget* getCheckPositionChild();
    UIWidget* getChildFromUpdatePool();
    void pushChildToPool();
    void getAndCallback();
    
    void setUpdateChild(UIWidget* child);
    void setUpdateDataIndex(int index);
    void clearCollectOverArray();
    void collectOverTopChild();
    void collectOverBottomChild();
    void collectOverLeftChild();
    void collectOverRightChild();
    void setLoopPosition();
    void updateChild();
    
    void initChildEvent();
    void updateChildEvent();
protected:
    ListViewDirection m_eDirection;
    ListViewMoveDirection m_eMoveDirection;
    
    float m_fTouchStartLocation;
    float m_fTouchEndLocation;
    float m_fTouchMoveStartLocation;
    float m_fTopBoundary;//test
    float m_fBottomBoundary;//test
    float m_fLeftBoundary;
    float m_fRightBoundary;                
    
    bool m_bAutoScroll;
    
    float m_fAutoScrollOriginalSpeed;
    float m_fAutoScrollAcceleration;
    
    bool m_bBePressed;
    float m_fSlidTime;
    CCPoint moveChildPoint;
    float m_fChildFocusCancelOffset;    
    
    cocos2d::CCObject* m_pInitChildListener;
    SEL_ListViewInitChildEvent m_pfnInitChildSelector;
    cocos2d::CCObject* m_pUpdateChildListener;
    SEL_ListViewUpdateChildEvent m_pfnUpdateChildSelector;
    
    CCArray* m_pChildPool;
    CCArray* m_pUpdatePool;
    
    int m_nDataLength;
    int m_nBegin;
    int m_nEnd;
    UIWidget* m_pUpdateChild;
    int m_nUpdateDataIndex;
    bool m_bUpdateSuccess;
    
    cocos2d::CCArray* m_overTopArray;
    cocos2d::CCArray* m_overBottomArray;
    cocos2d::CCArray* m_overLeftArray;
    cocos2d::CCArray* m_overRightArray;
    
    float m_fDisBoundaryToChild_0;
    float m_fDisBetweenChild;
};

NS_CC_EXT_END


#endif /* defined(__Test__UIListView__) */