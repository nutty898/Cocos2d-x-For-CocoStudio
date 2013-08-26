
#ifndef __TestCpp__CompatibleClasses__
#define __TestCpp__CompatibleClasses__

//#include "../../Layouts/Layout.h"
//#include "../UILabel.h"

NS_CC_EXT_BEGIN

class UIPanel : public Layout
{
    
    
public:
    static UIPanel* create()
    {
        UIPanel* widget = new UIPanel();
        if (widget && widget->init())
        {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    };
};

class UITextArea : public UILabel
{
    
    
public:
    static UITextArea* create()
    {
        UITextArea* widget = new UITextArea();
        if (widget && widget->init())
        {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    };
};

class UIContainerWidget : public Layout {
    
    
public:
    static UIContainerWidget* create()
    {
        UIContainerWidget* widget = new UIContainerWidget();
        if (widget && widget->init())
        {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    };
};


class UIZoomButton : public UITextButton {
public:
    static UIZoomButton* create()
    {
        UIZoomButton* widget = new UIZoomButton();
        if (widget && widget->init())
        {
            return widget;
        }
        CC_SAFE_DELETE(widget);
        return NULL;
    };
protected:
    virtual bool init(){
        if (UITextButton::init())
        {
            setScale9Enabled(true);
            setPressedActionEnabled(true);
            return true;
        }
        return false;
    };
};

NS_CC_EXT_END

#endif /* defined(__TestCpp__CompatibleClasses__) */
