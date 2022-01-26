@file:JvmName("OvrSystem")

package org.godotengine.plugin.vr.oculus.platform.api

import org.godotengine.plugin.vr.oculus.platform.OvrPlatformPlugin

/**
 * Oculus device type.
 */
enum class DeviceType(internal val rangeStart: Int, internal val rangeEnd: Int = rangeStart) {
    /**
     * Unknwon device type.
     */
    UNKNOWN(-1),
    
    /**
     * Device type for the Oculus Quest 1.
     */
    OCULUS_QUEST(256, 319),

    /**
     * Device type for the Oculus Quest 2.
     */
    OCULUS_QUEST2(320, 383);

    companion object {
        fun toDeviceType(value: Int): DeviceType {
            for(deviceType in values()) {
                if (deviceType.rangeStart <= value && value <= deviceType.rangeEnd) {
                    return deviceType;
                }
            }
            return UNKNOWN
        }
    }
}

/**
 * Return the current [DeviceType] type.
 */
fun OvrPlatformPlugin.getDeviceType(): DeviceType {
    return if (isSharedLibLoaded()) {
        DeviceType.toDeviceType(nativeGetDeviceType())
    } else {
        DeviceType.UNKNOWN
    }
}

/**
 * Return the current driver version.
 */
fun OvrPlatformPlugin.getDriverVersion(): String {
    return if (isSharedLibLoaded()) {
        nativeGetDriverVersion()
    } else {
        ""
    }
}
private external fun nativeGetDeviceType(): Int

private external fun nativeGetDriverVersion(): String
