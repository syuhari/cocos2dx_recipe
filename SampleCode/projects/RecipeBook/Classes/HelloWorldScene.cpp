#include "HelloWorldScene.h"
#include "scenes.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::~HelloWorld()
{
    CC_SAFE_RELEASE(m_pRecipes);
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    m_pRecipes = CCArray::createWithContentsOfFile("recipes.plist");
    m_pRecipes->retain();

    CCTableView* tableView = CCTableView::create(this, visibleSize);
    tableView->setDirection(kCCScrollViewDirectionVertical);
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setPosition(origin);
    tableView->setDelegate(this);
    this->addChild(tableView);
    tableView->reloadData();
    
    return true;
}

void HelloWorld::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CCDictionary* pRecipe = (CCDictionary*)m_pRecipes->objectAtIndex(cell->getIdx());
    CCString* pNo   = (CCString*)pRecipe->objectForKey("recipe");
    this->nextScene(pNo->intValue());
}

CCSize HelloWorld::cellSizeForTable(CCTableView *table)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    float height = visibleSize.height/5;
    return CCSizeMake(visibleSize.width, height);
}

CCTableViewCell* HelloWorld::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCDictionary* pRecipe = (CCDictionary*)m_pRecipes->objectAtIndex(idx);
    CCString* pName = (CCString*)pRecipe->objectForKey("name");
    CCString* pNo   = (CCString*)pRecipe->objectForKey("recipe");
    
    CCString* string = CCString::createWithFormat("レシピ %s : %s", pNo->getCString(), pName->getCString());
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CCTableViewCell();
        cell->autorelease();
        
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        
        int fontSize = CCEGLView::sharedOpenGLView()->getDesignResolutionSize().height/320.0f * 20;
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Helvetica", fontSize, CCSizeMake(visibleSize.width, visibleSize.height/5), kCCTextAlignmentCenter);
        label->setPosition(CCPointZero);
		label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        cell->addChild(label);
    }
    else
    {
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    
    
    return cell;
}

unsigned int HelloWorld::numberOfCellsInTableView(CCTableView *table)
{
    return m_pRecipes->count();
}

void HelloWorld::nextScene(int nIndex) {
    CCScene* scene = NULL;
    switch (nIndex) {
        case 19:
            scene = Recipe19::scene();
            break;
        case 25:
            // TODO
            //scene = Recipe25::scene();
            break;
        case 26:
            scene = Recipe26::scene();
            break;
        case 27:
            // TODO
            //scene = Recipe27::scene();
            break;
        case 28:
            scene = Recipe28::scene();
            break;
        case 30:
            scene = Recipe30::scene();
            break;
        case 31:
            scene = Recipe31::scene();
            break;
        case 32:
            scene = Recipe32::scene();
            break;
        case 33:
            scene = Recipe33::scene();
            break;
        case 34:
            scene = Recipe34::scene();
            break;
        case 37:
            scene = Recipe37::scene();
            break;
        case 38:
        {
            ModalLayer* layer = ModalLayer::create();
            this->addChild(layer);
            break;
        }
        case 39:
            // TODO
            //scene = Recipe39::scene();
            break;
        case 40:
            scene = Recipe40::scene();
            break;
        case 41:
            // TODO
            break;
        case 42:
            scene = Recipe42::scene();
            break;
        case 43:
            scene = Recipe43::scene();
            break;
        case 44:
            scene = Recipe44::scene();
            break;
        default:
            break;
    }
    
    if (scene!=NULL) {
        CCDirector::sharedDirector()->replaceScene(scene);
    }
}