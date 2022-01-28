@file:JvmName("OvrplLoader")

package org.godotengine.plugin.vr.oculus.platform.api

import org.godotengine.plugin.vr.oculus.platform.OvrPlatformPlugin

/**
 * intialize the plugin
 */
fun OvrPlatformPlugin.Initialize_standalone(): String {
    return if (isSharedLibLoaded()) {
        nativeInitialize_standalone()
    } else {
        ""
    }
}

private external fun nativeInitialize_standalone(): String
