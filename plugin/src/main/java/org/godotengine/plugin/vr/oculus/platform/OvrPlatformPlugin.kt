@file:JvmName("OvrPlatformPlugin")

package org.godotengine.plugin.vr.oculus.platform

import android.util.Log
import org.godotengine.godot.Godot
import org.godotengine.godot.plugin.GodotPlugin
import org.godotengine.godot.plugin.SignalInfo
import java.util.concurrent.ConcurrentLinkedQueue
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * Driver class for the Oculus Platform Godot plugin.
 */
class OvrPlatformPlugin(godot: Godot) : GodotPlugin(godot) {

    companion object {

        private val TAG = OvrPlatformPlugin::class.java.simpleName
        private var loadedSharedLib = false

        init {
            try {
                System.loadLibrary("godot_ovrplatform")
                loadedSharedLib = true
            } catch (e: UnsatisfiedLinkError) {
                Log.e(TAG, "Unable to load the godot_ovrplatform shared library")
                loadedSharedLib = false
            }
        }

        // Set of plugin signals
        private val SAMPLE_SIGNAL = SignalInfo("SampleSignal")
    }


    override fun getPluginGDNativeLibrariesPaths() =
        setOf("addons/godot_ovrplatform/godot_ovrplatform.gdnlib")

    override fun getPluginName() = "OVRPlatform"

    override fun getPluginSignals() = mutableSetOf(
        SAMPLE_SIGNAL,
    )

    internal fun isSharedLibLoaded() = loadedSharedLib

    override fun onGLSurfaceCreated(gl: GL10, config: EGLConfig) {
        super.onGLSurfaceCreated(gl, config)
        if (loadedSharedLib) {
            initializeWrapper()
        }
    }

    override fun onMainDestroy() {
        super.onMainDestroy()
        if (loadedSharedLib) {
            runOnRenderThread {
                uninitializeWrapper()
            }
        }
    }

    /*fun registerOvrEventListener(listener: OvrEventListener) {
        ovrEventListeners.add(listener)
    }

    fun unregisterOvrEventListener(listener: OvrEventListener) {
        ovrEventListeners.remove(listener)
    }
 */
    private external fun initializeWrapper()

    private external fun uninitializeWrapper()
}
