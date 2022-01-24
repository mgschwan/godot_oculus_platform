#include "api/ovr_utilities.h"
#include "ovr_utilities_ns.h"

static const char *kClassName = "OvrUtilities";

void register_gdnative_utilities(void *p_handle) {
    { // register the constructor and destructor of the OvrUtilitites class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_utilities_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_utilities_destructor;

		godot::nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // register all the functions that we want to expose via the OvrUtilities class in GDScript
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &get_ipd;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_ipd", attributes, method);

	}
}

GDCALLINGCONV void *ovr_utilities_constructor(godot_object *p_instance, void *p_method_data) {
	return nullptr;
}


GDCALLINGCONV void ovr_utilities_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {

}


GDCALLINGCONV godot_variant get_ipd(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	//CHECK_USER_DATA(
		godot::api->godot_variant_new_real(&ret, ovrmobile::get_ipd(ovr_mobile_session));
	//)
}

