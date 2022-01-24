#include "jni_common.h"

godot::String jstring_to_string(JNIEnv *env, jstring source) {
    if (env && source) {
        const char *const source_utf8 = env->GetStringUTFChars(source, NULL);
        if (source_utf8) {
            godot::String result(source_utf8);
            env->ReleaseStringUTFChars(source, source_utf8);
            return result;
        }
    }
    return godot::String();
}

jstring string_to_jstring(JNIEnv *env, const godot::String& source) {
    if (env) {
        return env->NewStringUTF(source.utf8().get_data());
    }
    return nullptr;
}
