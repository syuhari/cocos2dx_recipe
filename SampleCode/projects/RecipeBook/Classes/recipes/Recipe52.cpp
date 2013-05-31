//
//  Recipe52.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include "Recipe52.h"
#include "AppMacro.h"

USING_NS_CC;

Recipe52::Recipe52()
{
}

CCScene* Recipe52::scene()
{
    CCScene *scene = CCScene::create();
    Recipe52 *layer = Recipe52::create();
    scene->addChild(layer);
    return scene;
}

bool Recipe52::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLabelTTF *label = CCLabelTTF::create("", "Helvetica", FONT_SIZE(16));
    label->setPosition(ccp(origin.x + visibleSize.width/2,
                           origin.y + visibleSize.height/2));
    addChild(label, 10, 10);
    
    return true;
}

void Recipe52::onEnter()
{
    RecipeBase::onEnter();
    
    sqliteCreateTable();
    sqliteSetValueForKey("first", "cocos2d-x");
    sqliteSetValueForKey("second", "cocos2d-iphone");
    
    CCLOG("key first is:%s", sqliteGetValueForKey("first"));
    CCLOG("key second is:%s", sqliteGetValueForKey("second"));

    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString("データベースの更新処理が完了しました。\nログとソースを確認してください");
}


int Recipe52::sqliteOpen(sqlite3 **database)
{
    std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath();
    fullpath += "sample.db";
    return sqlite3_open(fullpath.c_str(), database);
}

void Recipe52::sqliteCreateTable()
{
    // データベースファイルを作成する
    sqlite3 *db = NULL;
    if (sqliteOpen(&db) == SQLITE_OK)
    {
        const char *sql_createtable = "CREATE TABLE test1(key TEXT,value TEXT)";
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(db, sql_createtable, -1, &stmt, NULL) == SQLITE_OK)
        {
            if (sqlite3_step(stmt) == SQLITE_DONE)
            {
                CCLOG("create table done");
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}

const char* Recipe52::sqliteGetValueForKey(const char * key)
{
    // キー文字列に対応する文字列を取得する
    CCString *strValue = NULL;
    sqlite3 *db = NULL;
    if (sqliteOpen(&db) == SQLITE_OK)
    {
        const char *sql_select = "SELECT value FROM test1 WHERE key=?";
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK)
        {
            sqlite3_bind_text(stmt, 1, key, -1, SQLITE_TRANSIENT);
            int ret = sqlite3_step(stmt);
            if( ret == SQLITE_DONE || ret == SQLITE_ROW)
            {
                const char *val =
                (const char *)sqlite3_column_text(stmt, 0);
                strValue = CCString::create(val);
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
    
    if (strValue != NULL)
    {
        return strValue->getCString();
    }
    return NULL;
}


void Recipe52::sqliteSetValueForKey(const char * key,
                                      const char* value)
{
    // キー文字列に対応する文字列を設定する
    std::string fullpath = CCFileUtils::sharedFileUtils()->getWritablePath();
    fullpath += "sample.db";
    sqlite3 *db = NULL;
    if (sqlite3_open(fullpath.c_str(), &db) == SQLITE_OK)
    {
        const char *sql_select = "REPLACE INTO test1 (key, value) VALUES (?,?)";
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK)
        {
            sqlite3_bind_text(stmt, 1, key, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, value, -1, SQLITE_TRANSIENT);
            if( sqlite3_step(stmt) == SQLITE_DONE)
            {
                CCLOG("replace key:%s value:%s", key, value);
            }
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}