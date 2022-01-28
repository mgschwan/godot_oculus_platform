#ifndef ovrpl_loader
#define ovrpl_loader

#include "nativescript_common.h"

#ifdef __cplusplus
extern "C" {
#endif

GDCALLINGCONV void *ovrpl_loader_constructor(godot_object *p_instance, void *p_method_data);
GDCALLINGCONV void ovrpl_loader_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data);
GDCALLINGCONV godot_variant standalone_initialize(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args);
}
#endif 