@file:JvmName("OvrSystem")

package org.godotengine.plugin.vr.oculus.platform.api

import org.godotengine.plugin.vr.oculus.platform.OvrPlatformPlugin

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

private external fun nativeGetDriverVersion(): String
