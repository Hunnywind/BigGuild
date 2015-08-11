LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/CompleteMissionScene.cpp \
				   ../../Classes/DetailScene.cpp \
				   ../../Classes/GameScene.cpp \
				   ../../Classes/GuildMemberManager.cpp \
				   ../../Classes/ID.cpp \
				   ../../Classes/MainScene.cpp \
				   ../../Classes/MapManager.cpp \
				   ../../Classes/Member.cpp \
				   ../../Classes/MemberScene.cpp \
				   ../../Classes/MenuManager.cpp \
				   ../../Classes/MenuScene.cpp \
				   ../../Classes/MissionDetailScene.cpp \
				   ../../Classes/MissionManager.cpp \
				   ../../Classes/MissionScene.cpp \
				   ../../Classes/RScrollViewController.cpp \
				   ../../Classes/RScrollViewItem.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += cocos_extension_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,extensions)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
