////////////////////////////////////////////////////////////////////////////
// OVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "godot_ovrplatform.h"
#include "gdnative/OculusPlatformCore.h"
#include <core/Godot.hpp>
#include <core/GodotGlobal.hpp>

void GDN_EXPORT godot_ovrplatform_gdnative_init(godot_gdnative_init_options *options) {
    godot::Godot::gdnative_init(options);
}

void GDN_EXPORT godot_ovrplatform_gdnative_singleton() {
    //something
}

void GDN_EXPORT godot_ovrplatform_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<godot::OculusPlatformCore>();

}

void GDN_EXPORT godot_ovrplatform_nativescript_terminate(void *handle) {
    godot::Godot::nativescript_terminate(handle);
}

void GDN_EXPORT godot_ovrplatform_gdnative_terminate(godot_gdnative_terminate_options *options) {
    godot::Godot::gdnative_terminate(options);
}
