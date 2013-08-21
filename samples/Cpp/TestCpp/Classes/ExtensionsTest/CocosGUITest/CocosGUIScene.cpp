#include "CocosGUIScene.h"
#include "CocosGUIExamplesScene.h"


CocosGUITestScene::CocosGUITestScene(bool bPortrait)
{
	TestScene::init();
}

CocosGUITestScene::~CocosGUITestScene()
{
	cocos2d::extension::CCJsonReader::purgeJsonReader();
//	cocos2d::extension::UIActionManager::purgeUIActionManager();
	cocos2d::extension::UIHelper::purgeUIHelper();
}

void CocosGUITestScene::runThisTest()
{
    
	CCDirector::sharedDirector()->replaceScene(this);
    
    ul = UILayer::create();
    ul->scheduleUpdate();
    this->addChild(ul);
    
//    ul->addWidget(CCUIHELPER->createWidgetFromJsonFile("cocosgui/UI_Register/UI_Register.json"));
    
    
//    UIPanel * p = (UIPanel*)CCUIHELPER->createWidgetFromJsonFile("cocosgui/CocoGUISample.json");
////        UIPanel * p = (UIPanel*)CCUIHELPER->createWidgetFromJsonFile("cocosgui/test/5_3/5_3.ExportJson");
//    ((UIScrollView*)p->getChildByName("scrollview"))->setInnerContainerSize(CCSizeMake(300, 275));
////    ((UIScrollView*)p->getChildByName("scrollview"))->setInnerContainerSize(CCSizeMake(300, 275));
////    ((UIScrollView*)p->getChildByName("scrollview"))->setLayoutType(UI_LAYOUT_LINEAR_VERTICAL);
//    ((UIScrollView*)p->getChildByName("scrollview"))->addScrollToBottomEvent(this, coco_ScrollToBottomSelector(CocosGUITestScene::toCocosGUIExampleScene));
////    UILabel* tl = UILabel::create();
////    tl->setText("111");
////    tl->setPosition(ccp(100, 200));
////    ((UIScrollView*)p->getChildByName("scrollview"))->addChild(tl);
////    p->setLayoutType(UI_LAYOUT_LINEAR_HORIZONTAL);
//    ul->addWidget(p);
////    UIButton* exitBtn = dynamic_cast<UIButton*>(ul->getWidgetByName("exitbutton"));
////    exitBtn->addReleaseEvent(this, coco_releaseselector(CocosGUITestScene::toCocosGUIExampleScene));
    
    
    Layout* l = Layout::create();
    l->setName("layout");
    ul->addWidget(l);
    l->setSize(CCSizeMake(300, 320));
    

//    LinearHorizontalLayoutExecutant* le = LinearHorizontalLayoutExecutant::create();
//    l->setLayoutExecutant(le);
//    
//    
//    for (int i=0; i<10; i++)
//    {
//        UIButton* btn = UIButton::create();
//        
//        btn->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "cocosgui/CloseNormal.png");
//        btn->setPosition(ccp(100, 100));
//        //    btn->setAnchorPoint(ccp(0, 0));
//        //    btn->setScale(0.5f);
//        btn->setSize(CCSizeMake(50, 50));
//        //    ul->addWidget(btn);
//        btn->setTouchEnabled(true);
//        btn->setScale9Enabled(true);
//        
//        //    btn->setBright(false);
//        
//        btn->addReleaseEvent(this, coco_releaseselector(CocosGUITestScene::MainMenuCallback));
//        LinearLayoutParameter* lp = LinearLayoutParameter::create();
//        lp->setGravity(LINEAR_GRAVITY_CENTER_VERTICAL);
//        btn->setLayoutParameter(lp);
//        l->addChild(btn);
//    }
//    l->getLayoutExecutant()->doLayout();
    
    
    RelativeLayoutExecutant* le = RelativeLayoutExecutant::create();
    l->setLayoutExecutant(le);
    
    UIButton* btn1 = UIButton::create();
    btn1->setScale9Enabled(true);
    btn1->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "cocosgui/CloseNormal.png");
    RelativeLayoutParameter* lp = RelativeLayoutParameter::create();
    lp->setAlign(RELATIVE_ALIGN_PARENT_RIGHT);
    lp->setRelativeName("btn1");
    lp->setMargin(UIMargin(10,0,0,10));
    btn1->setLayoutParameter(lp);
    l->addChild(btn1);
    
    UIButton* btn2 = UIButton::create();
    
    btn2->setSize(CCSizeMake(100, 100));
    btn2->loadTextures("cocosgui/animationbuttonnormal.png", "cocosgui/animationbuttonpressed.png", "cocosgui/CloseNormal.png");
    RelativeLayoutParameter* lp2 = RelativeLayoutParameter::create();
    lp2->setAlign(RELATIVE_CENTER_IN_PARENT);
    lp2->setRelativeToWidgetName("btn1");
    lp2->setAlign(RELATIVE_LOCATION_BELOW_RIGHTALIGN);
    lp2->setRelativeName("btn2");
    btn2->setLayoutParameter(lp2);
    lp2->setMargin(UIMargin(0,10,0,0));
    l->addChild(btn2);
    btn2->setScale9Enabled(true);
    
    
    
    l->setBackGroundColorType(LAYOUT_COLOR_SOLID);
    l->setBackGroundColor(ccGREEN);
    
    
    btn2->addReleaseEvent(this, coco_releaseselector(CocosGUITestScene::MainMenuCallback));
    
    l->setBackGroundImage("cocosgui/animationbuttonnormal.png");
    l->setBackGroundImageScale9Enabled(true);
//    l->disable(true);
    
    btn1->ignoreContentAdaptWithSize(true);
    btn2->ignoreContentAdaptWithSize(true);
    btn2->setSize(CCSizeMake(100, 100));
    btn2->ignoreContentAdaptWithSize(false);
    
    
//    UICheckBox* cb = UICheckBox::create();
//    cb->loadTextures("cocosgui/check_box_normal.png", "cocosgui/check_box_normal_press.png", "cocosgui/check_box_active.png", "cocosgui/check_box_normal_disable.png", "cocosgui/check_box_active_disable.png");
//    l->addChild(cb);
//    
//    RelativeLayoutParameter* lp3 = RelativeLayoutParameter::create();
//    cb->setLayoutParameter(lp3);
//    cb->ignoreContentAdaptWithSize(true);
    
//    UIImageView* iv = UIImageView::create();
//    iv->loadTexture("cocosgui/animationbuttonnormal.png");
//    RelativeLayoutParameter* lp3 = RelativeLayoutParameter::create();
//    iv->setLayoutParameter(lp3);
////    iv->setScale9Enabled(true);
//    iv->setSize(CCSizeMake(100, 100));
//    iv->setScale9Enabled(true);
////    iv->ignoreContentAdaptWithSize(true);
////    iv->setSize(CCSizeMake(100, 100));
////    iv->ignoreContentAdaptWithSize(false);
//    l->addChild(iv);
    
    UILoadingBar* lb = UILoadingBar::create();
    lb->loadTexture("cocosgui/backtotopnormal.png");
    l->addChild(lb);
//    lb->setDirection(LoadingBarTypeRight);
    RelativeLayoutParameter* lp3 = RelativeLayoutParameter::create();
    lb->setLayoutParameter(lp3);
    lb->setPercent(100);
//    lb->ignoreContentAdaptWithSize(true);
//    lb->setSize(CCSizeMake(50, 50));
//    lb->ignoreContentAdaptWithSize(false);
    
    
    le->doLayout();
    lb->setPosition(ccp(100, 100));
//    l->active(true);
//    l->setClippingEnabled(true);
    
//    UICheckBox* cb = UICheckBox::create();
//    cb->loadTextures("cocosgui/check_box_normal.png", "cocosgui/check_box_normal_press.png", "cocosgui/check_box_active.png", "cocosgui/check_box_normal_disable.png", "cocosgui/check_box_active_disable.png");
//    ul->addWidget(cb);
//    
//    cb->setPosition(ccp(100, 100));
//    cb->setTouchEnabled(true);
//    cb->setSize(CCSizeMake(200, 200));
    
//    UIImageView* iv = UIImageView::create();
//    iv->loadTexture("cocosgui/check_box_normal.png");
//    iv->setPosition(ccp(100, 100));
//    ul->addWidget(iv);
//    iv->setSize(CCSizeMake(100, 100));
//    iv->setScale9Enabled(true);
    
//    UILabel* lb = UILabel::create();
//    lb->setText("dsadsdsad");
//    ul->addWidget(lb);
//    lb->setPosition(ccp(100.0f, 100.0f));
    
//    UILabelAtlas* lba = UILabelAtlas::create();
//    lba->setProperty("123", "cocosgui/labelatlas.png", 17, 22, "0");
//    ul->addWidget(lba);
//    lba->setPosition(ccp(100, 100));
//    lba->setSize(CCSizeMake(100, 100));
//    lba->setAnchorPoint(ccp(0, 0));
    
//    UILabelBMFont* lbb = UILabelBMFont::create();
//    lbb->setFntFile("cocosgui/bitmapFontTest2.fnt");
//    lbb->setPosition(ccp(100, 100));
//    lbb->setText("dsadasdas");
//    ul->addWidget(lbb);
    
//    UILoadingBar* ldb = UILoadingBar::create();
//    ldb->loadTexture("cocosgui/loadingbar.png");
//    ldb->setPosition(ccp(100, 100));
//    ul->addWidget(ldb);
//    ldb->setPercent(50);
//    ldb->setSize(CCSizeMake(130, 17));
    
//    UIPanel* p = UIPanel::create();
//    p->setBackGroundColor(ccGREEN);
//    p->setBackGroundColorType(PANEL_COLOR_SOLID);
//    p->setSize(CCSizeMake(480, 320));
//    ul->addWidget(p);
//    
//    UISlider* sld = UISlider::create();
//    sld->loadBarTexture("cocosgui/loadingbar.png");
//    sld->loadSlidBallTextures("cocosgui/sliderballnormal.png", "cocosgui/sliderballpressed.png", "");
//    sld->setPosition(ccp(240, 100));
//    sld->setTouchEnabled(true);
//    ul->addWidget(sld);
//    sld->setSize(CCSizeMake(130, 17));
//    sld->addPercentChangedEvent(this, coco_percentchangedselector(CocosGUITestScene::MainMenuCallback));
////    sld->setScale(2);
//    sld->setScale9Enabled(true);
//    sld->setSize(CCSizeMake(480, 17));
////    sld->setVisible(false);
////    sld->setEnabled(false);
//    
//    UILabel* label = UILabel::create();
//    label->setName("nnn");
//    label->setPosition(ccp(100, 100));
//    ul->addWidget(label);
//    sld->setEnabled(false);
//    sld->setScale(0.5f);
    
//    CCDrawNode *shape = CCDrawNode::create();
//    static CCPoint rect[4];
//    rect[0] = ccp(0, 0);
//    rect[1] = ccp(100, 0);
//    rect[2] = ccp(100, 100);
//    rect[3] = ccp(0, 100);
//    
//    static ccColor4F green = {0, 1, 0, 1};
//    shape->drawPolygon(rect, 4, green, 0, green);
//    
//    CCClippingNode* cn = CCClippingNode::create(shape);
//    //content
//    
//    CCSprite* content = CCSprite::create("cocosgui/Hello.png");
//    content->setPosition(ccp(240, 160));
//    cn->addChild(content);
//    
////    cn->setPosition(ccp(<#__X__#>, <#__Y__#>))/
////    this->addChild(cn);
//    CCNode* st = CCSprite::create("cocosgui/Hello.png");
////    st->setContentSize(CCSizeMake(10, 10));
//    st->setPosition(ccp(240, 160));
////    cn->setStencil(st);
////    cn->ignoreAnchorPointForPosition(true);
//    cn->setPosition(ccp(100, 100));
////    cn->runAction(CCRepeatForever::create(CCRotateBy::create(3, 720)));
//    
////    cn->setScale(0.5f);
//    CCSprite* sp = CCSprite::create("cocosgui/animationbuttonnormal.png");
//    cn->addChild(sp);
//    
//    
//    CCDrawNode *shape2 = CCDrawNode::create();
//    static CCPoint rect2[4];
//    rect2[0] = ccp(0, 0);
//    rect2[1] = ccp(100, 0);
//    rect2[2] = ccp(100, 100);
//    rect2[3] = ccp(0, 100);
//    
//    static ccColor4F green2 = {0, 1, 0, 1};
//    shape2->drawPolygon(rect2, 4, green2, 0, green2);
//    CCClippingNode* cn1 = CCClippingNode::create(shape2);
//    
//    cn1->addChild(cn);
//    cn->setPosition(ccp(50, 50));
//    
//    cn1->setPosition(ccp(100, 100));
//    addChild(cn1);
    
}

void CocosGUITestScene::MainMenuCallback(CCObject* pSender)
{
    CCLOG("fuck");
    ((UIWidget*)pSender)->setBright(false);
//    UISlider* sl = (UISlider*)pSender;
//    char aa[128];
//    sprintf(aa, "percent %d",sl->getPercent());
//    ((UILabel*)(ul->getWidgetByName("nnn")))->setText(aa);
//    ul->removeFromParent();
//    TestScene::MainMenuCallback(pSender);
    ((Layout*)ul->getWidgetByName("layout"))->removeBackGroundImage();
}

void CocosGUITestScene::toCocosGUIExampleScene(CCObject* pSender)
{
    ((UIScrollView*)pSender)->setDirection(SCROLLVIEW_DIR_HORIZONTAL);
//    ((UIScrollView*)pSender)->getChildByName("backtotopbutton")->disable();
    return;
    CCLOG("p2 click");
    ul->removeFromParent();
    
    CocosGUIExamplesScene* pScene = new CocosGUIExamplesScene();
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
}
