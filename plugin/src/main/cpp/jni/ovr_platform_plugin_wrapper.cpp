/**
 * Created by Fredia Huya-Kouadio.
 */

#include "ovr_platform_plugin_wrapper.h"
#include "common.h"
#include <core/GodotGlobal.hpp>


namespace ovrplatform {

jobject OvrPlatformPluginWrapper::ovr_platform_plugin_instance = nullptr;

OvrPlatformPluginWrapper::OvrPlatformPluginWrapper() {}

OvrPlatformPluginWrapper::~OvrPlatformPluginWrapper() {}

void OvrPlatformPluginWrapper::initializeWrapper(JNIEnv *env, jobject ovr_platform_plugin) {
    ovr_platform_plugin_instance = env->NewGlobalRef(ovr_platform_plugin);
    ALOG_ASSERT(ovr_platform_plugin_instance != nullptr, "Invalid jobject value.");

    jclass ovr_platform_plugin_class = env->GetObjectClass(ovr_platform_plugin_instance);
    ALOG_ASSERT(ovr_platform_plugin_class != nullptr, "Invalid jclass value.");


    if (godot::android_api) {
        jobject activity_object = env->NewGlobalRef(godot::android_api->godot_android_get_activity());
        const char *appId = "org.godotengine.vrworkout";
        ovr_PlatformInitializeAndroid(appId, activity_object, env);
    }
    //  this_env =env;
}

void OvrPlatformPluginWrapper::uninitializeWrapper(JNIEnv *env) {
    if (ovr_platform_plugin_instance) {
        env->DeleteGlobalRef(ovr_platform_plugin_instance);
        ovr_platform_plugin_instance = nullptr;
    }
}

void OvrPlatformPluginWrapper::initEntitlement() {
    ovr_Entitlement_GetIsViewerEntitled();
}



} // namespace ovrplatform
