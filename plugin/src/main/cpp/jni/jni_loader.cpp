#include "api/ovrpl_loader.h"
#include "jni_common.h"
#include <jni.h>

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_mobile_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrSystem

extern "C" {

JNIEXPORT jstring JNICALL JNI_METHOD(Initialize_standalone)(JNIEnv *env, jclass) {
    return ovrplatform::Initialize_standalone());
}
};