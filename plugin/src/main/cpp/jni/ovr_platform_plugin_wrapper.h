/**
 * Created by Fredia Huya-Kouadio.
 */

#ifndef OVRMOBILE_OVR_PLATFORM_PLUGIN_WRAPPER_H
#define OVRMOBILE_OVR_PLATFORM_PLUGIN_WRAPPER_H

#include <jni.h>
#include "OVR_Platform.h"


namespace ovrplatform {

// Provide native access to the
// org.godotengine.plugin.vr.oculus.mobile.OvrPlatformPlugin instance.
class OvrPlatformPluginWrapper {
 public:
    static jobject ovr_platform_plugin_instance;
    static jobject ovr_platform_plugin_activity;
    static JNIEnv *ovr_platform_plugin_environment;


    static void initializeWrapper(JNIEnv *env, jobject ovr_mobile_plugin);
    static void uninitializeWrapper(JNIEnv *env);

 private:

    OvrPlatformPluginWrapper();
    ~OvrPlatformPluginWrapper();

};

} // namespace ovrplatform

#endif // OVRMOBILE_OVR_MOBILE_PLUGIN_WRAPPER_H
