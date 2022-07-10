/**
* Created by Fredia Huya-Kouadio. 
*/

#include <jni.h>

#include "jni_common.h"
#include "ovr_platform_plugin_wrapper.h"

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_platform

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrPlatformPlugin

extern "C" {
JNIEXPORT void JNICALL JNI_METHOD(initializeWrapper)(JNIEnv* env,
                                                     jobject object) {
  ovrplatform::OvrPlatformPluginWrapper::initializeWrapper(env, object);
}

JNIEXPORT void JNICALL JNI_METHOD(uninitializeWrapper)(JNIEnv* env,
                                                       jobject object) {
  ovrplatform::OvrPlatformPluginWrapper::uninitializeWrapper(env);
}
};
