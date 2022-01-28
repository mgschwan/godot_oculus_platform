/**
 * Created by Fredia Huya-Kouadio.
 */

#include "api/ovrpl_utilities.h"
#include "jni_common.h"
#include <jni.h>

#undef JNI_PACKAGE_NAME
#define JNI_PACKAGE_NAME org_godotengine_plugin_vr_oculus_platform_api

#undef JNI_CLASS_NAME
#define JNI_CLASS_NAME OvrplUtilities

extern "C" {

JNIEXPORT jfloat JNICALL JNI_METHOD(nativeGetIpd)(JNIEnv *env, jclass clazz) {
    return ovrplatform::get_ipd(get_session());
}

JNIEXPORT jint JNICALL JNI_METHOD(nativeGetRenderTargetWidth)(JNIEnv *env, jclass) {
    return get_session()->get_render_target_width();
}

JNIEXPORT jfloatArray JNICALL JNI_METHOD(nativeGetEyeFov)(JNIEnv *env, jclass, jint eye) {
    ovrVector4f eye_fov = get_session()->get_eye_fov(static_cast<ovrEye>(eye));
    return from_ovrVector4f(env, eye_fov);
}

JNIEXPORT jboolean JNICALL JNI_METHOD(nativeSetDefaultLayerColorScale)(JNIEnv *env,
                                                                       jclass clazz,
                                                                       jfloat red,
                                                                       jfloat green,
                                                                       jfloat blue,
                                                                       jfloat alpha) {
    return static_cast<jboolean>(
            ovrplatform::set_default_layer_color_scale(get_session(), red, green, blue, alpha));
}

};
