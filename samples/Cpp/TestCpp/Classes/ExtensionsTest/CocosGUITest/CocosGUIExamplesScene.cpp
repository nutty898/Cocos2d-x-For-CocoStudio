

#include "CocosGUIExamplesScene.h"
#include "CocosGUIScene.h"


const char* weapon_introduce_text[31] =
{
	"Chinese: 1",
	"Japanese: 2",
	"Korean: 3",
	"English: 4",
	"French: 5",
	"Russian: 6",
	"German: 7",
	"Spanish: 8",
	"Portuguese: 9",
	"Italian: 10",
	"Greek: 11",
	"Dutch: 12",
	"Swedish: 13",
	"Arabic: 14",
	"Czech: 15",
	"Danish: 16",
	"Finnish: 17",
	"Norwegian:18",
	"Bulgarian: 19",
	"Persian: 20",
	"Hausa: 21",
	"Schieber Lai: 22",
	"Hindi: 23",
	"Hungarian: 24",
	"Pushtu: 25",
	"Polish: 26",
	"Romanian: 27",
	"Serbian: 28",
	"Thai: 29",
	"Turkish: 30",
	"Urdu: 31",
};


CocosGUIExamplesScene::CocosGUIExamplesScene(bool bPortrait)
{
	TestScene::init();
}

CocosGUIExamplesScene::~CocosGUIExamplesScene()
{
	cocos2d::extension::CCJsonReader::purgeJsonReader();
//	cocos2d::extension::UIActionManager::purgeUIActionManager();
	cocos2d::extension::UIHelper::purgeUIHelper();
}

void CocosGUIExamplesScene::onEnter()
{
    TestScene::onEnter();
    
    ul = UILayer::create();
    ul->scheduleUpdate();
    this->addChild(ul);
    
    // ui init
    ExamplesInit();
    
    // exit
    UIButton* exit = UIButton::create();
    exit->loadTextures("cocosgui/CloseNormal.png", "cocosgui/CloseSelected.png", "");
    exit->setPosition(ccp(430, 60));
    exit->setTouchEnabled(true);
    exit->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::toCocosGUITestScene));
    ul->addWidget(exit);
}

void CocosGUIExamplesScene::onExit()
{
    TestScene::onExit();
}

void CocosGUIExamplesScene::runThisTest()
{    
	CCDirector::sharedDirector()->replaceScene(this);
}

void CocosGUIExamplesScene::MainMenuCallback(CCObject* pSender)
{
    ul->removeFromParent();
	TestScene::MainMenuCallback(pSender);
}

void CocosGUIExamplesScene::toCocosGUITestScene(CCObject *pSender)
{
    ul->removeFromParent();
    
    CocosGUITestScene *pScene = new CocosGUITestScene();
    if (pScene)
    {
        pScene->runThisTest();
        pScene->release();
    }
}

// ui
void CocosGUIExamplesScene::ExamplesInit()
{
    // example root
    UIWidget* example_root = CCUIHELPER->createWidgetFromJsonFile("cocosgui/examples/examples_1.json");
    example_root->setWidgetTag(EXAMPLE_PANEL_TAG_ROOT);
    ul->addWidget(example_root);
    
    // example button initialize
    ExamplesButtonPanelInit();
    
    // equip initialize
    EquipInit();
    
    // weapon initialize
    WeaponInit();
}

// ui button
void CocosGUIExamplesScene::ExamplesButtonPanelInit()
{
    // examples root
//    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
//    
//    // examples initialize
//    UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("button_panel")); 
//    
//    UIButton* equip_btn = dynamic_cast<UIButton*>(button_panel->getChildByName("equip_button"));
//    equip_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::ExamplesShowEquip));
//    
//    UIButton* weapon_btn = dynamic_cast<UIButton*>(button_panel->getChildByName("weapon_button"));
//    weapon_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::ExamplesShowWeapon));
}

void CocosGUIExamplesScene::ExamplesShowEquip(CCObject* pSender)
{    
//    // examples root
//    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
//    
//    // equip
//    UIPanel* equip_root = dynamic_cast<UIPanel*>(example_root->getChildByName("equip_root"));
//    equip_root->setVisible(true);
//    
//    // button panel
//    UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("button_panel"));
//    //button_panel->disable(true);
}

void CocosGUIExamplesScene::ExamplesShowWeapon(CCObject* pSender)
{
//    // examples root
//    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
//    
//    // examples button panel
//    UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("button_panel"));
//    //button_panel->disable(true);
//    
//    // weapon root
//    UIPanel* weapon_root = dynamic_cast<UIPanel*>(example_root->getChildByName("weapon_root"));
//    weapon_root->setVisible(true);
//    
//    // weapon reset
//    // introduce panel
//    UIPanel* weapon_introduce_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("introduce_panel"));
//    UITextArea* weapon_introduce_text = dynamic_cast<UITextArea*>(weapon_introduce_panel->getChildByName("introduce_text"));
//    weapon_introduce_text->setText("Please touch weapon icon to watch introduce,and scroll panel to check more");
//    
//    // weapon panel
//    UIPanel* weapon_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("weapon_panel"));
//    
//    // weapon scrollview
//    UIScrollView* weapon_scrlv = dynamic_cast<UIScrollView*>(weapon_panel->getChildByName("weapon_scrollview"));    
//    CCObject* obj = NULL;
//    CCARRAY_FOREACH(weapon_scrlv->getChildren(), obj)
//    {
//        UIPanel* item = dynamic_cast<UIPanel*>(obj);
//        
//        UIImageView* normal = dynamic_cast<UIImageView*>(item->getChildByName("normal"));
//        normal->setVisible(true);
//        
//        UIImageView* selected = dynamic_cast<UIImageView*>(item->getChildByName("selected"));
//        selected->setVisible(false);
//    }
}

// equip
void CocosGUIExamplesScene::EquipInit()
{}

void CocosGUIExamplesScene::EquipCreate()
{
    EquipCreateClothes();
    EquipCreateWeapons();
    EquipCreatePets();
}

void CocosGUIExamplesScene::EquipCreateClothes()
{}

void CocosGUIExamplesScene::EquipCreateWeapons()
{}

void CocosGUIExamplesScene::EquipCreatePets()
{}

void CocosGUIExamplesScene::EquipSwitchBtnCallBack(CCObject *pSender)
{}

void CocosGUIExamplesScene::EquipTouch(CCObject *pSender)
{
//    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
//    CCPoint worldSpace = widget->getContainerNode()->convertToWorldSpace(CCPointZero);
//    
//    widgetLastWorldSpace = worldSpace;
//    widgetLastNodeSpace = widget->getPosition();
//    
//    lastWidgetParent = widget->getWidgetParent();
//    widget->removeFromParentAndCleanup(false);
//    
//    ul->addWidget(widget);
//    
//    widget->setPosition(widget->getTouchStartPos());
//    movePoint = widget->getTouchStartPos();
}

void CocosGUIExamplesScene::EquipMove(CCObject* pSender)
{
    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
    
    lastPoint = movePoint;
    movePoint = widget->getTouchMovePos();
    CCPoint offset = ccpSub(movePoint, lastPoint);
    CCPoint toPoint = ccpAdd(widget->getPosition(), offset);    
    widget->setPosition(toPoint);
}

void CocosGUIExamplesScene::EquipDrop(CCObject *pSender)
{
//    bool isInUsedSlot = false;
//    bool isInEquipSlot = false;
//    
//    UIWidget* widget = dynamic_cast<UIWidget*>(pSender);
////    CCRect widget_rect = widget->getRect();
//    
//    CCDictElement* element = NULL;
//    
//    // usedSlot
//    CCDICT_FOREACH(m_dicBeUsedSlot, element)
//    {
//        UIWidget* usedSlot_wigt = dynamic_cast<UIWidget*>(element->getObject());
//        if (usedSlot_wigt->getChildren()->count() > 0)
//        {
//            continue;
//        }
//        CCRect slot_rect = usedSlot_wigt->getRect();
//        if (slot_rect.containsPoint(widget->getPosition()))
//        {
//            widget->removeFromParentAndCleanup(false);
//            widget->setPosition(CCPointZero);
//            usedSlot_wigt->addChild(widget);
//            
//            isInUsedSlot = true;
//            break;
//        }
//    }
//    
//    // equipSlot
//    CCDictionary* equipSlot_dic = NULL;
//    CCDictionary* equip_dic = NULL;
//    switch (m_eEquipType)
//    {
//        case EQUIP_TYPE_CLOTHES:
//            equipSlot_dic = m_dicEquipClothesSlot;
//            equip_dic = m_dicEquipClothes;
//            break;
//            
//        case EQUIP_TYPE_WEAPONS:
//            equipSlot_dic = m_dicEquipWeaponsSlot;
//            equip_dic = m_dicEquipWeapons;
//            break;
//            
//        case EQUIP_TYPE_PETS:
//            equipSlot_dic = m_dicEquipPetsSlot;
//            equip_dic = m_dicEquipPets;
//            break;
//            
//        default:
//            break;
//    }
//    
//    CCDICT_FOREACH(equipSlot_dic, element)
//    {
//        UIWidget* equipSlot = dynamic_cast<UIWidget*>(element->getObject());
//        if (equipSlot->getChildren()->count() > 0)
//        {
//            continue;
//        }
//        
//        CCRect slot_rect = equipSlot->getRect();
//        if (slot_rect.containsPoint(widget->getPosition()))
//        {            
//            CCObject* obj = equip_dic->objectForKey(widget->getName());
//            if (obj)
//            {
//                widget->removeFromParentAndCleanup(false);
//                widget->setPosition(CCPointZero);
//                equipSlot->addChild(widget);
//                
//                isInEquipSlot = true;
//            }            
//            break;
//        }
//    }
//    
//    // back to last position
//    if (!isInUsedSlot && !isInEquipSlot)
//    {
//        CCPoint point = widgetLastWorldSpace;
//        CCMoveTo* moveTo = CCMoveTo::create(1.0f, point);
//        CCEaseExponentialOut* ease = CCEaseExponentialOut::create(moveTo);
//        CCCallFuncO* calllFunc0 = CCCallFuncO::create(this, callfuncO_selector(CocosGUIExamplesScene::EquipBackOver), widget);
//        CCSequence* seq = CCSequence::create(ease, calllFunc0, NULL);
//        widget->runAction(seq);
//        
//        // widget in equip slot
//        CCDICT_FOREACH(equip_dic, element)
//        {
//            UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
//            widget->setTouchEnabled(false, true);
//        }
//        
//        // equip up panel
//        UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
//        UIPanel* equipe_root = dynamic_cast<UIPanel*>(example_root->getChildByName("equip_root"));
//        UIPanel* up_panel = dynamic_cast<UIPanel*>(equipe_root->getChildByName("UP"));
//        up_panel->setTouchEnabled(false, true);        
//    }
}

void CocosGUIExamplesScene::EquipBackOver(CCObject *pObject)
{
//    UIWidget* widget = dynamic_cast<UIWidget*>(pObject);
//    
//    widget->removeFromParentAndCleanup(false);
//    lastWidgetParent->addChild(widget);
//    widget->setPosition(widgetLastNodeSpace);
//    
//    CCDictElement* element = NULL;
//    
//    // equip
//    CCDictionary* equip_dic = NULL;
//    switch (m_eEquipType)
//    {
//        case EQUIP_TYPE_CLOTHES:
//            equip_dic = m_dicEquipClothes;
//            break;
//            
//        case EQUIP_TYPE_WEAPONS:
//            equip_dic = m_dicEquipWeapons;
//            break;
//            
//        case EQUIP_TYPE_PETS:
//            equip_dic = m_dicEquipPets;
//            break;
//            
//        default:
//            break;
//    }
//    CCDICT_FOREACH(equip_dic, element)
//    {
//        UIWidget* widget = dynamic_cast<UIWidget*>(element->getObject());
//        widget->setTouchEnabled(true, true);
//    }
//    
//    // equip up panel
//    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
//    UIPanel* equipe_root = dynamic_cast<UIPanel*>(example_root->getChildByName("equip_root"));
//    UIPanel* up_panel = dynamic_cast<UIPanel*>(equipe_root->getChildByName("UP"));
//    up_panel->setTouchEnabled(true, true);
}

void CocosGUIExamplesScene::EquipClose(CCObject* pObject)
{
    // examples root
//    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
//    
//    // equip
//    UIPanel* equip_root = dynamic_cast<UIPanel*>(example_root->getChildByName("equip_root"));
//    equip_root->setVisible(false);
//    
//    // button panel
//    UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("button_panel"));    
   // button_panel->active(true);
}

// weapon
void CocosGUIExamplesScene::WeaponInit()
{
    // examples root
//    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
//    
//    // weapon
//    UIPanel* weapon_root = dynamic_cast<UIPanel*>(example_root->getChildByName("weapon_root"));
//    weapon_root->setWidgetTag(WEAPON_PANEL_TAG_ROOT);
//    
//    // title panel
//    UIPanel* title_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("Title"));
//    UIButton* close_btn = dynamic_cast<UIButton*>(title_panel->getChildByName("Button"));
//    close_btn->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::WeaponClose));
//    
//    // introduce panel
//    UIPanel* introduce_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("introduce_panel"));
//    UITextArea* introduce_text = dynamic_cast<UITextArea*>(introduce_panel->getChildByName("introduce_text"));
//    introduce_text->setText("点击武器图标查看武器介绍，滑动武器库查看更多武器");        
//    
//    // weapon panel create
//    WeaponCreate();
}

void CocosGUIExamplesScene::WeaponCreate()
{
//    // examples root
//    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
//    
//    // weapon root
//    UIPanel* weapon_root = dynamic_cast<UIPanel*>(example_root->getChildByName("weapon_root"));
//    weapon_root->setWidgetTag(WEAPON_PANEL_TAG_ROOT);    
//    
//    // weapon panel
//    UIPanel* weapon_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("weapon_panel"));
//    
//    // weapon scrollview
//    UIScrollView* weapon_scrlv = dynamic_cast<UIScrollView*>(weapon_panel->getChildByName("weapon_scrollview"));
//    float weapon_scrlv_width = weapon_scrlv->getRect().size.width;
//    float weapon_scrlv_height = weapon_scrlv->getRect().size.height;
//    
//    // weapon item create
//    int dataLength = sizeof(weapon_introduce_text) / sizeof(weapon_introduce_text[0]);
//    int columnMax = 4;
//    int mod = dataLength % columnMax;
//    int rowMax = dataLength / columnMax;
//    if (mod != 0)
//    {
//        rowMax += 1;
//    }
//    
//    for (int i = 0; i  < rowMax; ++i)
//    {
//        bool isBreak_i = false;
//        
//        for (int j = 0; j < columnMax; ++j)
//        {
//            bool isBreak_j = false;
//            
//            if (i * columnMax + j == dataLength)
//            {
//                isBreak_i = true;
//                isBreak_j = true;
//            }
//            
//            if (isBreak_j)
//            {
//                break;
//            }
//            
//            
//            UIPanel* item = dynamic_cast<UIPanel*>(CCUIHELPER->createWidgetFromJsonFile("cocosgui/examples/weapon_introduce/weapon_item/weapon_item_1.json"));
//            item->setWidgetTag(WEAPON_ITEM_PANEL_TAG + i * columnMax + j);
//            
//            float width = item->getRect().size.width;
//            float height = item->getRect().size.height;
//            float interval_x = width / 10;
//            float interval_y = height / 10;
//            float start_x = weapon_scrlv_width / 25;
//            float start_y = weapon_scrlv_height - height;
//            float x = start_x + j * (width + interval_x);
//            float y = start_y - i * (height + interval_y);
//            item->setPosition(ccp(x, y));
//            
//            weapon_scrlv->addChild(item);
//            
//            // weapon item normal
//            UIImageView* normal = dynamic_cast<UIImageView*>(item->getChildByName("normal"));
//            normal->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::WeaponItemTouch));
//            // weapon item selected
//            UIImageView* selected = dynamic_cast<UIImageView*>(item->getChildByName("selected"));
//            selected->setVisible(false);
//            // weapon item weapon
//            UIImageView* weapon = dynamic_cast<UIImageView*>(item->getChildByName("weapon"));
//            weapon->addReleaseEvent(this, coco_releaseselector(CocosGUIExamplesScene::WeaponItemTouch));
//        }
//        
//        if (isBreak_i)
//        {
//            break;
//        }
//    }        
}

void CocosGUIExamplesScene::WeaponItemTouch(CCObject* pObject)
{
    // weapon item child
//    UIImageView* widget = dynamic_cast<UIImageView*>(pObject);
//    
//    // weapon item
//    UIPanel* item = dynamic_cast<UIPanel*>(widget->getWidgetParent());
//    
//    // weapon scrollview
//    UIScrollView* scrollview = dynamic_cast<UIScrollView*>(item->getWidgetParent());
//    CCObject* obj = NULL;
//    CCARRAY_FOREACH(scrollview->getChildren(), obj)
//    {
//        UIPanel* item = dynamic_cast<UIPanel*>(obj);
//        
//        UIImageView* normal = dynamic_cast<UIImageView*>(item->getChildByName("normal"));
//        normal->setVisible(true);
//        
//        UIImageView* selected = dynamic_cast<UIImageView*>(item->getChildByName("selected"));
//        selected->setVisible(false);
//    }
//    
//    // weapon item normal
//    UIImageView* normal = dynamic_cast<UIImageView*>(item->getChildByName("normal"));
//    normal->setVisible(false);
//    
//    // weapon item selected
//    UIImageView* selected = dynamic_cast<UIImageView*>(item->getChildByName("selected"));
//    selected->setVisible(true);
//    
//    WeaponItemShowDetail(item);
}

void CocosGUIExamplesScene::WeaponItemShowDetail(UIWidget* widget)
{
    // examples root
//    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
//    
//    // weapon
//    UIPanel* weapon_root = dynamic_cast<UIPanel*>(example_root->getChildByName("weapon_root"));
//    // introduce panel
//    UIPanel* introduce_panel = dynamic_cast<UIPanel*>(weapon_root->getChildByName("introduce_panel"));
//    UITextArea* introduce_text = dynamic_cast<UITextArea*>(introduce_panel->getChildByName("introduce_text"));
//        
//    introduce_text->setText(weapon_introduce_text[widget->getWidgetTag() - WEAPON_ITEM_PANEL_TAG]);
}

void CocosGUIExamplesScene::WeaponClose(CCObject* pObject)
{
//    // examples root
//    UIWidget* example_root = dynamic_cast<UIPanel*>(ul->getWidgetByTag(EXAMPLE_PANEL_TAG_ROOT));
//    
//    // weapon
//    UIPanel* weapon_root = dynamic_cast<UIPanel*>(example_root->getChildByName("weapon_root"));
//    weapon_root->setVisible(false);
//    
//    // button panel
//    UIPanel* button_panel = dynamic_cast<UIPanel*>(example_root->getChildByName("button_panel"));
//    //button_panel->active(true);
}
