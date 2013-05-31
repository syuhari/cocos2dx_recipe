#include "HelloWorldScene.h"
#include "scenes.h"
#include <iomanip>

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
    CCString* pStep = (CCString*)pRecipe->objectForKey("step");
    int iStep = pStep==NULL?0:pStep->intValue();
    this->nextScene(pNo->intValue(), iStep);
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
    CCString* pStep = (CCString*)pRecipe->objectForKey("step");
    
    CCString* string;
    if (pStep!=NULL) {
        string = CCString::createWithFormat("レシピ %s （ステップ%s）: %s", pNo->getCString(), pStep->getCString(), pName->getCString());
    } else if (pNo->isEqual(CCString::create("0"))) {
        string = pName;
    } else {
        string = CCString::createWithFormat("レシピ %s : %s", pNo->getCString(), pName->getCString());
    }
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

void HelloWorld::nextScene(int nIndex, int iStep)
{
    // レシピ毎にリソースパスを変更
    stringstream ss;
    ss << "recipes/recipe" << setfill('0') << setw(2) << nIndex;
    std::vector<std::string> searchPath;
    searchPath.push_back(ss.str());
    CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);

    CCScene* scene = NULL;
    switch (nIndex) {
        case 0:
        {
            searchPath.clear();
            for (int i=3; i<=16; i++) {
                ss.str("");
                ss << "recipes/recipe" << setfill('0') << setw(2) << i;
                searchPath.push_back(ss.str());
            }
            CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
            // レシピ03-16 チュートリアル
            scene = Recipe03to16::scene();
            break;
        }
        case 15:
            searchPath.clear();
            searchPath.push_back("recipes/recipe03");
            CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
            // CCCallFunc アクションの使い方
            scene = Recipe15::scene();
            break;
        case 19:
            scene = Recipe19::scene();
            break;
        case 21:
            // 配列を使用する
            scene = Recipe21::scene();
            break;
        case 22:
            // 辞書を使用する
            scene = Recipe22::scene();
            break;
        case 24:
            // デバッグ用にログを出力する
            scene = Recipe24::scene();
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
            // 指でなぞったラインを描画
            if (iStep==2) {
                scene = Recipe39::scene();
            } else {
                scene = Recipe39_3::scene();
            }
            break;
        case 40:
            scene = Recipe40::scene();
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
        case 45:
            // TableView
            scene = Recipe45::scene();
            break;
        case 46:
            // DrawNode
            scene = Recipe46::scene();
            break;
        case 52:
            // SQLite
            scene = Recipe52::scene();
            break;
        case 54:
            // ダウンロード
            scene = Recipe54::scene();
            break;
        case 55:
            // ダウンロード進捗
            scene = Recipe55::scene();
            break;
        case 57:
            // plist
            scene = Recipe57::scene();
            break;
        case 58:
            // XML
            if (iStep == 2) {
                scene = Recipe58_2::scene();
            }else{
                scene = Recipe58_3::scene();
            }
            break;
        case 60:
            // iOS / Android
            scene = Recipe60::scene();
            break;
        case 64:
            // カメラ（デバイス）
            scene = Recipe64::scene();
            break;
        case 67:
            // ハードウェアキー
            scene = Recipe67::scene();
            break;
        case 70:
            // 物理エンジン
            scene = Recipe70::scene();
            break;
        case 72:
            // 簡易3D
            scene = Recipe72::scene();
            break;
        case 74:
            // タイルマップ
            scene = Recipe74::scene();
            break;
        case 75:
            // デリゲートメソッド
            scene = Recipe75::scene();
            break;
        case 76:
            // unzip
            scene = Recipe76::scene(iStep);
            break;
        case 77:
            // ローカライズ
            scene = Recipe77::scene();
            break;
        case 78:
            // 加速度センサー
            scene = Recipe78::scene();
            break;
        case 80:
            // テクスチャアトラス
            scene = Recipe80::scene();
            break;
        case 81:
            // 非同期テクスチャアトラス
            scene = Recipe81::scene();
            break;
        case 82:
            // PVR テクスチャアトラス
            scene = Recipe82::scene();
            break;
        case 83:
            // パーティクル
            scene = Recipe83::scene();
            break;
        case 84:
            // Physics Editor
            scene = Recipe84::scene();
            break;
        case 85:
            // LevelHelper
            scene = Recipe85::scene();
            break;
        case 86:
            // CocosBuilder
            scene = Recipe86::scene();
            break;
        case 87:
            // SpriteStudio
            scene = Recipe87::scene();
            break;
        case 88:
            // Glypy Designer
            scene = Recipe88::scene();
            break;
        default:
            break;
    }

    if (scene!=NULL) {
        CCDirector::sharedDirector()->replaceScene(scene);
    }else{
        CCMessageBox("not yet implemented", "RecipeBook");
    }
}