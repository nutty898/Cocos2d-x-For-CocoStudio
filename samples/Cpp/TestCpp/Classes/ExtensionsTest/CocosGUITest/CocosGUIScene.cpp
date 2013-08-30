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
    
//    UIButton* btn = UIButton::create();
////    btn->ignoreContentAdaptWithSize(false);
//    btn->loadTextures("cocosgui/sliderballnormal.png", "cocosgui/sliderballpressed.png", "");
//    btn->setPosition(ccp(100, 100));
//    ul->addWidget(btn);
//    btn->setTouchEnabled(true);
//    btn->setSize(CCSizeMake(100, 100));
//    CCSize s = btn->getSize();
//    CCLOG("s w %f s h %f",s.width,s.height);
//    
////    btn->ignoreContentAdaptWithSize(false);
//    
//    btn->setScale9Enabled(true);
//    s = btn->getSize();
//    CCLOG("9 s w %f s h %f",s.width,s.height);
//
//    btn->setSize(CCSizeMake(100, 100));
//    s = btn->getSize();
//    CCLOG("s9 s w %f s h %f",s.width,s.height);
//
//    btn->setScale9Enabled(false);
//    s = btn->getSize();
//    CCLOG("s9f s w %f s h %f",s.width,s.height);
//    CCLOG("is == %d",btn->isIgnoreContentAdaptWithSize());
//
//    btn->ignoreContentAdaptWithSize(false);
//    btn->setSize(CCSizeMake(150, 150));
    
//    UIScrollView* sc = UIScrollView::create();
//    sc->setBackGroundColor(ccGREEN);
//    sc->setBackGroundColorType(LAYOUT_COLOR_SOLID);
//    sc->setSize(CCSizeMake(100, 100));
//    sc->setInnerContainerSize(CCSizeMake(100, 600));
//    LinearVerticalLayoutExecutant * exe = LinearVerticalLayoutExecutant::create();
//    sc->setLayoutExecutant(exe);
//    
//    for (int i=0; i<80; i++)
//    {
//        UIButton* btn = UIButton::create();
//        btn->loadTextures("cocosgui/sliderballnormal.png", "cocosgui/sliderballpressed.png", "");
//        btn->setTouchEnabled(true);
//        LinearLayoutParameter* lp = LinearLayoutParameter::create();
//        lp->setGravity(LINEAR_GRAVITY_CENTER_HORIZONTAL);
//        btn->setLayoutParameter(lp);
//        sc->addChild(btn);
//    }
//    exe->doLayout();
//    
//    ul->addWidget(sc);
//    
//    sc->setPosition(ccp(100, 100));
    
    
//    UISlider* lb = UISlider::create();
//    lb->setTouchEnabled(true);
//    lb->loadBarTexture("cocosgui/slidbar.png");
//    lb->loadSlidBallTextures("cocosgui/sliderballnormal.png", "cocosgui/sliderballpressed.png", "");
//    ul->addWidget(lb);
//    lb->setPosition(ccp(100, 100));
//    lb->ignoreContentAdaptWithSize(false);
//    lb->setSize(CCSizeMake(200, 50));
//    
//    
//    lb->setScale9Enabled(true);
//    lb->loadProgressBarTexture("cocosgui/sliderThumb.png");
//    
//    lb->setScale9Enabled(false);
    
//    CCSize s = lb->getSize();
//    CCLOG("s w %f s h %f",s.width,s.height);
//    lb->ignoreContentAdaptWithSize(false);
//    s = lb->getSize();
//    CCLOG("ig s w %f s h %f",s.width,s.height);
//
//    lb->setScale9Enabled(true);
//    s = lb->getSize();
//    CCLOG("s9 s w %f s h %f",s.width,s.height);

//    lb->setScale9Enabled(false);
//    s = lb->getSize();
//    CCLOG("s9f s w %f s h %f",s.width,s.height);

//    lb->ignoreContentAdaptWithSize(true);
//    s = lb->getSize();
//    CCLOG("ssss s w %f s h %f",s.width,s.height);
//
//    btn->setScale9Enabled(true);
    
//    btn->setScale9Enable(true);
//    s = btn->getSize();
//    CCLOG("s9f ag s w %f s h %f",s.width,s.height);
//    CCLOG("is == %d",btn->isIgnoreContentAdaptWithSize());
    
    UIWidget* w = CCUIHELPER->createWidgetFromJsonFile("cocosgui/NewProject_U1_1/NewProject_U1_1.json");
    ul->addWidget(w);
    
//    UIButton* btn = UIButton::create();
//    btn->loadTextures("cocosgui/sliderballnormal.png", "cocosgui/sliderballpressed.png", "");
//    
//    ul->addWidget(btn);
//    btn->setPosition(ccp(100, 100));
//    btn->ignoreContentAdaptWithSize(false);
//    
//    btn->setSize(CCSizeMake(100, 100));
//    btn->setScale9Enabled(true);
//    btn->setTouchEnabled(true);
    

//    UISlider* sd = UISlider::create();
//    sd->loadBarTexture("cocosgui/slidbar.png");
//    sd->loadProgressBarTexture("cocosgui/slider_bar_active_9patch.png");
//    sd->setSlidBallTextures("cocosgui/sliderballnormal.png", "cocosgui/sliderballpressed.png", "");
//    ul->addWidget(sd);
//    sd->setPosition(ccp(240, 100));
//    sd->setTouchEnable(true);
//    sd->setScale9Enable(true);
//    sd->setSize(CCSizeMake(480, 10));
//    sd->setScale9Enable(false);
//    sd->ignoreContentAdaptWithSize(true);
}

void CocosGUITestScene::MainMenuCallback(CCObject* pSender)
{
    CCLOG("fuck");
//    ((UIWidget*)pSender)->setBright(false);
//    UISlider* sl = (UISlider*)pSender;
//    char aa[128];
//    sprintf(aa, "percent %d",sl->getPercent());
//    ((UILabel*)(ul->getWidgetByName("nnn")))->setText(aa);
//    ul->removeFromParent();
//    TestScene::MainMenuCallback(pSender);
    UILoadingBar* lb = ((UILoadingBar*)ul->getWidgetByName("aaa"));
    if (lb)
    {
        
        CCLOG("mabi position x %f y %f",lb->getPosition().x,lb->getPosition().y);  
    }
    else
    {
        CCLOG("nimabi");
    }
//
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
