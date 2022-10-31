////////////////////////////////////////////////////////////////
// Common includes for OVR code, mostly copied from samples
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#ifndef OVRMOBILE_COMMON_H
#define OVRMOBILE_COMMON_H

// Some android includes
#include <android/log.h>

#include <gdnative_api_struct.gen.h>
#include <core/Godot.hpp>
#include <core/GodotGlobal.hpp>
#include <string>
#include <cstdlib>
// Include the OVR SDK
#define DEBUG 1
#define LOG_TAG "GodotOVRPlatform"

#define ALOG_ASSERT(_cond, ...)                                                                    \
    if (!(_cond)) __android_log_assert("conditional", LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif

#define MULTI_THREADED 0

namespace ovrplatform {

inline bool check_bit(uint32_t in, uint32_t bits) {
    return (in & bits) != 0;
}

} // namespace ovrmobile


#endif // OVRMOBILE_COMMON_H
