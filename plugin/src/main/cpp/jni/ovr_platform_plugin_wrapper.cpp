/**
 * Created by Fredia Huya-Kouadio.
 */

#include "ovr_platform_plugin_wrapper.h"
#include "common.h"
#include <core/GodotGlobal.hpp>


namespace ovrplatform {

jobject OvrPlatformPluginWrapper::ovr_platform_plugin_instance = nullptr;

OvrPlatformPluginWrapper::OvrPlatformPluginWrapper() {
    // does not work here // godot::register_method("initEntitlement", &OvrPlatformPluginWrapper::initEntitlement);
}

OvrPlatformPluginWrapper::~OvrPlatformPluginWrapper() {}

void OvrPlatformPluginWrapper::initializeWrapper(JNIEnv *env, jobject ovr_platform_plugin) {
    ovr_platform_plugin_instance = env->NewGlobalRef(ovr_platform_plugin);
    ALOG_ASSERT(ovr_platform_plugin_instance != nullptr, "Invalid jobject value.");

    jclass ovr_platform_plugin_class = env->GetObjectClass(ovr_platform_plugin_instance);
    ALOG_ASSERT(ovr_platform_plugin_class != nullptr, "Invalid jclass value.");

    jmethodID get_activity = env->GetMethodID(ovr_platform_plugin_class, "getMainActivity", "()Landroid/app/Activity;");
    jobject activity_object = env->CallObjectMethod(ovr_platform_plugin_instance, get_activity);
    ALOGV("Trying to initialize OVR Platform");
    if (activity_object) {  
        ALOGV("Yes we are initializing");      
        const char *appId = "org.godotengine.oculusplatformtest"; //TODO: let the user set it manually
        ovr_PlatformInitializeAndroid(appId, activity_object, env);
        ALOGV("Finished initializing");      

    } else {
        ALOGV("OVR Platform can not be initialized");
    }
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
