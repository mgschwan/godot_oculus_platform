#include "common.h"
#include "gdnative/OculusPlatformCore.h"
#include "jni/ovr_platform_plugin_wrapper.h"

using namespace godot;

void OculusPlatformCore::_register_methods() {
	register_method("_ready", &OculusPlatformCore::_ready);
	register_method("initEntitlement", &OculusPlatformCore::initEntitlement);
	//register_property<OpenXRHand, int>("relative_transform", &OpenXRHand::set_relative_transform, &OpenXRHand::get_relative_transform, 0, GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_ENUM, "Global,Local");
}

OculusPlatformCore::OculusPlatformCore() {
}

OculusPlatformCore::~OculusPlatformCore() {
}

void OculusPlatformCore::_init() {
	// nothing to do here
}

void OculusPlatformCore::_ready() {
}


void OculusPlatformCore::initEntitlement(const String appId) {
    char *c_appId = appId.alloc_c_string();
    ALOGV("Trying to initialize OVR Platform");
    if (ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment && ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_activity) {  
        ALOGV("Yes we are initializing");      
        
        jclass ovr_platform_plugin_class = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->GetObjectClass(ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_instance);
        ALOG_ASSERT(ovr_platform_plugin_class != nullptr, "Invalid jclass value.");

        jmethodID get_activity = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->GetMethodID(ovr_platform_plugin_class, "getMainActivity", "()Landroid/app/Activity;");
        jobject activity = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->CallObjectMethod(ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_instance, get_activity);
        
        ALOGV("Got all objects");      
        
        ovr_PlatformInitializeAndroid(c_appId, activity, ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment);
        ALOGV("Finished initializing");      
        
        ovr_Entitlement_GetIsViewerEntitled();
        ALOGV("Entitlement checked");      
        
    } else {
        ALOGV("OVR Platform can not be initialized");
    }

}
