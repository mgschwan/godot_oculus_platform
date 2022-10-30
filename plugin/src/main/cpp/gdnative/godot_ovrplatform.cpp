////////////////////////////////////////////////////////////////////////////
// OVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "godot_ovrplatform.h"
#include "gdnative/OculusPlatformCore.h"
#include <core/Godot.hpp>
#include <core/GodotGlobal.hpp>

using namespace godot;

void GDN_EXPORT godot_ovrplatform_gdnative_init(godot_gdnative_init_options *options) {
    Godot::gdnative_init(options);
}

void GDN_EXPORT godot_ovrplatform_gdnative_singleton() {
    //something
}

void GDN_EXPORT godot_ovrplatform_nativescript_init(void *handle) {
    Godot::nativescript_init(handle);
    register_class<OculusPlatformCore>();
}

void GDN_EXPORT godot_ovrplatform_nativescript_terminate(void *handle) {
    Godot::nativescript_terminate(handle);
}

void GDN_EXPORT godot_ovrplatform_gdnative_terminate(godot_gdnative_terminate_options *options) {
    Godot::gdnative_terminate(options);
}
