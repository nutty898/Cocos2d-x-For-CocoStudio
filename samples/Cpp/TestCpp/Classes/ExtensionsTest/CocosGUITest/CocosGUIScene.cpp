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
    
    UISlider* sd = UISlider::create();
    sd->loadBarTexture("cocosgui/slidbar.png");
    sd->loadProgressBarTexture("cocosgui/slider_bar_active_9patch.png");
    sd->setSlidBallTextures("cocosgui/sliderballnormal.png", "cocosgui/sliderballpressed.png", "");
    ul->addWidget(sd);
    sd->setPosition(ccp(240, 100));
    sd->setTouchEnable(true);
    sd->setScale9Enable(true);
    sd->setSize(CCSizeMake(480, 10));
    sd->setScale9Enable(false);
    sd->ignoreContentAdaptWithSize(true);
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
