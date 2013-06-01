LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/GB2ShapeCache-x.cpp \
../../Classes/GLES-Render.cpp \
../../Classes/HelloWorldScene.cpp \
../../Classes/LevelHelper/CustomClasses/TemporaryDummyClass.cpp \
../../Classes/LevelHelper/LevelHelperLoader.cpp \
../../Classes/LevelHelper/Nodes/LHAnimationNode.cpp \
../../Classes/LevelHelper/Nodes/LHBatch.cpp \
../../Classes/LevelHelper/Nodes/LHBezier.cpp \
../../Classes/LevelHelper/Nodes/LHContactInfo.cpp \
../../Classes/LevelHelper/Nodes/LHContactListener.cpp \
../../Classes/LevelHelper/Nodes/LHContactNode.cpp \
../../Classes/LevelHelper/Nodes/LHCustomSpriteMgr.cpp \
../../Classes/LevelHelper/Nodes/LHCuttingEngineMgr.cpp \
../../Classes/LevelHelper/Nodes/LHFixture.cpp \
../../Classes/LevelHelper/Nodes/LHJoint.cpp \
../../Classes/LevelHelper/Nodes/LHLayer.cpp \
../../Classes/LevelHelper/Nodes/LHNode.cpp \
../../Classes/LevelHelper/Nodes/LHParallaxNode.cpp \
../../Classes/LevelHelper/Nodes/LHPathNode.cpp \
../../Classes/LevelHelper/Nodes/LHSettings.cpp \
../../Classes/LevelHelper/Nodes/LHSprite.cpp \
../../Classes/LevelHelper/Nodes/LHTouchMgr.cpp \
../../Classes/LevelHelper/Nodes/SHDocumentLoader.cpp \
../../Classes/LevelHelper/Utilities/LHArray.cpp \
../../Classes/LevelHelper/Utilities/LHDictionary.cpp \
../../Classes/LevelHelper/Utilities/LHObject.cpp \
../../Classes/CCBigImage/CCBigImage.cpp \
../../Classes/CCBigImage/CCBigImageLayer.cpp \
../../Classes/Player/SSPlayer.cpp \
../../Classes/recipes/AppPlatform.cpp \
../../Classes/recipes/CCTestLayer.cpp \
../../Classes/recipes/DeviceCamera.cpp \
../../Classes/recipes/DictationManager.cpp \
../../Classes/recipes/ModalLayer.cpp \
../../Classes/recipes/MyTableViewCell.cpp \
../../Classes/recipes/Recipe03to16.cpp \
../../Classes/recipes/Recipe15.cpp \
../../Classes/recipes/Recipe19.cpp \
../../Classes/recipes/Recipe21.cpp \
../../Classes/recipes/Recipe22.cpp \
../../Classes/recipes/Recipe24.cpp \
../../Classes/recipes/Recipe25.cpp \
../../Classes/recipes/Recipe26.cpp \
../../Classes/recipes/Recipe28.cpp \
../../Classes/recipes/Recipe30.cpp \
../../Classes/recipes/Recipe31.cpp \
../../Classes/recipes/Recipe32.cpp \
../../Classes/recipes/Recipe33.cpp \
../../Classes/recipes/Recipe34.cpp \
../../Classes/recipes/Recipe37.cpp \
../../Classes/recipes/Recipe39.cpp \
../../Classes/recipes/Recipe39_3.cpp \
../../Classes/recipes/Recipe40.cpp \
../../Classes/recipes/Recipe42.cpp \
../../Classes/recipes/Recipe43.cpp \
../../Classes/recipes/Recipe44.cpp \
../../Classes/recipes/Recipe45.cpp \
../../Classes/recipes/Recipe46.cpp \
../../Classes/recipes/Recipe52.cpp \
../../Classes/recipes/Recipe54.cpp \
../../Classes/recipes/Recipe55.cpp \
../../Classes/recipes/Recipe57.cpp \
../../Classes/recipes/Recipe58_2.cpp \
../../Classes/recipes/Recipe58_3.cpp \
../../Classes/recipes/Recipe60.cpp \
../../Classes/recipes/Recipe64.cpp \
../../Classes/recipes/Recipe67.cpp \
../../Classes/recipes/Recipe70.cpp \
../../Classes/recipes/Recipe72.cpp \
../../Classes/recipes/Recipe74.cpp \
../../Classes/recipes/Recipe75.cpp \
../../Classes/recipes/Recipe76.cpp \
../../Classes/recipes/Recipe77.cpp \
../../Classes/recipes/Recipe78.cpp \
../../Classes/recipes/Recipe80.cpp \
../../Classes/recipes/Recipe81.cpp \
../../Classes/recipes/Recipe82.cpp \
../../Classes/recipes/Recipe83.cpp \
../../Classes/recipes/Recipe84.cpp \
../../Classes/recipes/Recipe85.cpp \
../../Classes/recipes/Recipe86.cpp \
../../Classes/recipes/Recipe87.cpp \
../../Classes/recipes/Recipe88.cpp \
../../Classes/recipes/RecipeBase.cpp \
../../Classes/recipes/TapSprite.cpp \
../../Classes/VisibleRect.cpp \
../../Classes/3rd/sqlite/sqlite3.c \
../../Classes/recipes/outfile.c

LOCAL_C_INCLUDES := ${shell find $(LOCAL_PATH)/../../Classes -type d}
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../external/Box2D

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_curl_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
