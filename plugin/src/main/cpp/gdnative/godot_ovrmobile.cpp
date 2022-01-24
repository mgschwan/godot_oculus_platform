////////////////////////////////////////////////////////////////////////////
// OVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "godot_ovrmobile.h"
#include "api/ovr_system.h"
#include "gdnative/nativescript/ovr_utilities_ns.h"
#include <core/Godot.hpp>
#include <core/GodotGlobal.hpp>

void GDN_EXPORT godot_ovrmobile_gdnative_init(godot_gdnative_init_options *options) {
    godot::Godot::gdnative_init(options);
}

void GDN_EXPORT godot_ovrmobile_gdnative_singleton() {
    if (godot::arvr_api != nullptr) {
        godot::arvr_api->godot_arvr_register_interface(&interface_struct);
    }
}

void GDN_EXPORT godot_ovrmobile_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    register_gdnative_utilities(handle);

    godot::register_class<ovrmobile::OvrSystem>();
}

void GDN_EXPORT godot_ovrmobile_nativescript_terminate(void *handle) {
    godot::Godot::nativescript_terminate(handle);
}

void GDN_EXPORT godot_ovrmobile_gdnative_terminate(godot_gdnative_terminate_options *options) {
    godot::Godot::gdnative_terminate(options);
}
