

#include "UIScene.h"
#include "UISceneManager.h"
#include "../ExtensionsTest.h"

UIScene::UIScene()
//: m_pSceneTitleLabel(NULL)
: m_pSceneTitle(NULL)
, m_pUiLayer(NULL)
{
    
}

UIScene::~UIScene()
{
    m_pUiLayer->removeFromParent();
//    CC_SAFE_RELEASE_NULL(m_pSceneTitleLabel);
}

bool UIScene::init()
{
    if (CCLayer::init())
    {
        m_pUiLayer = UILayer::create();
        m_pUiLayer->scheduleUpdate();
        addChild(m_pUiLayer);
        
        m_pWidget = CCUIHELPER->createWidgetFromJsonFile("cocosgui/UIButton_test_1/UIButton_test_1.json");
        m_pUiLayer->addWidget(m_pWidget);
        
        m_pSceneTitle = dynamic_cast<UILabel*>(m_pUiLayer->getWidgetByName("UItest"));
        
        UILabel *back_label = dynamic_cast<UILabel*>(m_pUiLayer->getWidgetByName("back"));
        back_label->addReleaseEvent(this, coco_releaseselector(UIScene::toExtensionsMainLayer));
        
        UIButton *left_button = dynamic_cast<UIButton*>(m_pUiLayer->getWidgetByName("left_Button"));
        left_button->addReleaseEvent(this, coco_releaseselector(UIScene::previousCallback));
        
        UIButton *middle_button = dynamic_cast<UIButton*>(m_pUiLayer->getWidgetByName("middle_Button"));
        middle_button->addReleaseEvent(this, coco_releaseselector(UIScene::restartCallback));
        
        UIButton *right_button = dynamic_cast<UIButton*>(m_pUiLayer->getWidgetByName("right_Button"));
        right_button->addReleaseEvent(this, coco_releaseselector(UIScene::nextCallback));
        
        return true;
    }
    return false;
}

void UIScene::toExtensionsMainLayer(CCObject* sender)
{
    ExtensionsTestScene* pScene = new ExtensionsTestScene();
    pScene->runThisTest();
    pScene->release();
}

void UIScene::previousCallback(CCObject* sender)
{
    CCDirector::sharedDirector()->replaceScene(UISceneManager::sharedUISceneManager()->previousUIScene());
}

void UIScene::restartCallback(CCObject* sender)
{
    CCDirector::sharedDirector()->replaceScene(UISceneManager::sharedUISceneManager()->currentUIScene());
}

void UIScene::nextCallback(CCObject* sender)
{
    CCDirector::sharedDirector()->replaceScene(UISceneManager::sharedUISceneManager()->nextUIScene());
}