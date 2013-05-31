//
//  Recipe76.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/31.
//
//

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include "support/zip_support/unzip.h"
#include "platform/CCFileUtils.h"

#include "Recipe76.h"
#include "AppMacro.h"
#include "AppPlatform.h"
#include "VisibleRect.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// for getApkPath()
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#endif

USING_NS_CC;

Recipe76::Recipe76()
{
}

CCScene* Recipe76::scene(int step)
{
    CCScene *scene = CCScene::create();
    Recipe76 *layer = Recipe76::create();
    layer->setStepNo(step);
    scene->addChild(layer);
    return scene;
}

bool Recipe76::init()
{
    if ( !RecipeBase::init() )
    {
        return false;
    }
    CCPoint center = VisibleRect::center();
    CCLabelTTF *label = CCLabelTTF::create("", "Helvetica", FONT_SIZE(16));
    label->setPosition(center);
    addChild(label, 10, 10);
    return true;
}

void Recipe76::doStep1()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCMessageBox("iOS Only", "RecipeBook");
    return;
#else
    std::string zipFilename = "archive.zip";
    std::string filename = "test.txt";
    
    CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();
    // フルパスを取得
    std::string fullPath = fileUtils->fullPathForFilename(zipFilename.c_str());
    // archivezipファイルから test.txtデータをメモリに展開
    unsigned long size;
    unsigned char *data = fileUtils->getFileDataFromZip(fullPath.c_str(), filename.c_str(), &size);
    CCLOG("data:%08X, fullPath:%s", data, fullPath.c_str());
    std::string text;
    if (data!=NULL)
    {
        text.assign((const char*)data, size);
        //「delete [] data;」を忘れると、メモリーリークになるので注意
        delete [] data;
    }
    CCString *msg = CCString::createWithFormat("read from zip file'%s'", text.c_str());
    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString(msg->getCString());
#endif
}

void Recipe76::doStep2()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCMessageBox("iOS Only", "RecipeBook");
    return;
#else
    std::string zipFilename = "archive.zip";
    
    CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();
    // フルパスを取得
    std::string fullPath = fileUtils->fullPathForFilename(zipFilename.c_str());
    // 書き込み可能なディレクトリを取得
    std::string path = fileUtils->getWritablePath();
    std::string unzipdPath = path + "unzipd/";
    // zipの展開
    unzipFileToDir(fullPath.c_str(), unzipdPath.c_str());
    
    // 展開したzip中のテキストファイル取得
    std::string txtPath = unzipdPath + "test-step2.txt";
    unsigned long size;
    unsigned char* data = fileUtils->getFileData(txtPath.c_str(), "rb", &size);
    std::string text;
    if (data != NULL) {
        text.assign((const char*)data, size);
        delete [] data;
    }
    CCString *msg = CCString::createWithFormat("read from zip file'%s'", text.c_str());
    CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
    label->setString(msg->getCString());
#endif
}

void Recipe76::doStep3()
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
    CCMessageBox("Android Only", "RecipeBook");
    return;
#else
    unsigned long size;
    unsigned char *data;
    std::string filename = "res/drawable-mdpi/icon.png";
    std::string apkPath = getApkPath();
    CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();
    data = fileUtils->getFileDataFromZip(apkPath.c_str(),
                                         filename.c_str(), &size);
    if (data!=NULL)
    {
        // icon データ参照
        CCLabelTTF *label = (CCLabelTTF*)this->getChildByTag(10);
        label->setString("apk からアイコンデータを取得しました");
        delete [] data;
    }
#endif
}

#define UNZIP_BUF_SIZE      1024
#define MAX_ZIPFILE_NAME    512

void Recipe76::unzipFileToDir(const char *zipFullPath, const char* toDir)
{
    unzFile pFile = NULL;
    do {
        // 出力先ディレクトリ作成
        CC_BREAK_IF(!createDirectory(toDir));
        
        // zipの情報を取得
        pFile = unzOpen(zipFullPath);
        CC_BREAK_IF(!pFile);
        unz_global_info global_info;
        CC_BREAK_IF(unzGetGlobalInfo(pFile, &global_info) != UNZ_OK);
        
        char buff[UNZIP_BUF_SIZE];
        
        for (int i = 0; i < global_info.number_entry; ++i)
        {
            // zip内のファイル情報取得
            unz_file_info info;
            char fileName[MAX_ZIPFILE_NAME];
            CC_BREAK_IF(unzGetCurrentFileInfo(pFile, &info, fileName, MAX_ZIPFILE_NAME, NULL, 0, NULL, 0)!= UNZ_OK);
            
            std::string fullPath = toDir;
            fullPath += fileName;
            if (fullPath.at(fullPath.length()-1) == '/')
            {
                // ディレクトリ作成
                CC_BREAK_IF(!createDirectory(fullPath.c_str()));
            }
            else
            {
                // ファイル展開
                CC_BREAK_IF(unzOpenCurrentFile(pFile) != UNZ_OK);
                FILE *out = fopen(fullPath.c_str(), "wb");
                int unread = 0;
                if (out)
                {
                    do {
                        unread = unzReadCurrentFile(pFile, buff, UNZIP_BUF_SIZE);
                        if (unread > 0)
                        {
                            fwrite(buff, unread, 1, out);
                        }
                    } while(unread > 0);
                    fclose(out);
                }
                unzCloseCurrentFile(pFile);
                CC_BREAK_IF(unread < 0);
            }
            if ((i+1) < global_info.number_entry)
            {
                CC_BREAK_IF(unzGoToNextFile(pFile) != UNZ_OK);
            }
        } // i < global_info.number_entry
    } while (0);
    
    if (pFile)
    {
        unzClose(pFile);
    }
}

bool Recipe76::createDirectory(const char *path)
{
    int ret = mkdir(path, S_IRWXU);
    if (ret != 0 && (errno != EEXIST))
    {
        return false;
    }
    return true;
}