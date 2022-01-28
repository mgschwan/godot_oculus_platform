////////////////////////////////////////////////////////////////////////////
// OVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#ifndef GODOT_OVRPLATFORM_H
#define GODOT_OVRPLATFORM_H

#include <gdnative_api_struct.gen.h>

#ifdef __cplusplus
extern "C" {
#endif

void GDN_EXPORT godot_ovrplatform_gdnative_init(godot_gdnative_init_options *options);
void GDN_EXPORT godot_ovrplatform_gdnative_singleton();
void GDN_EXPORT godot_ovrplatform_nativescript_init(void *handle);
void GDN_EXPORT godot_ovrplatform_nativescript_terminate(void *handle);
void GDN_EXPORT godot_ovrplatform_gdnative_terminate(godot_gdnative_terminate_options *options);

#ifdef __cplusplus
}
#endif

#endif /* !godot_ovrplatform_H */
