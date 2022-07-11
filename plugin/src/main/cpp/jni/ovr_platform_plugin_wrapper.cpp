/**
 * Created by Fredia Huya-Kouadio.
 */

#include "ovr_platform_plugin_wrapper.h"
#include "common.h"
#include <core/GodotGlobal.hpp>


namespace ovrplatform {

jobject OvrPlatformPluginWrapper::ovr_platform_plugin_instance = nullptr;
jobject OvrPlatformPluginWrapper::ovr_platform_plugin_activity = nullptr;
JNIEnv *OvrPlatformPluginWrapper::ovr_platform_plugin_environment = nullptr;

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
    ovr_platform_plugin_activity = env->CallObjectMethod(ovr_platform_plugin_instance, get_activity);

    ovr_platform_plugin_environment = env;
}

void OvrPlatformPluginWrapper::uninitializeWrapper(JNIEnv *env) {
    if (ovr_platform_plugin_instance) {
        env->DeleteGlobalRef(ovr_platform_plugin_instance);
        ovr_platform_plugin_instance = nullptr;
    }
}


} // namespace ovrplatform
