#include "api/ovrpl_loader.h"
#include "ovrpl_loader_ns.h"

static const char *kClassName = "OvrplLoader";

oid register_gdnative_loader(void *p_handle) {
    { // register the constructor and destructor of the OvrGuardianSystem class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovrpl_loader_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovrpl_loader_destructor;

		godot::nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // now we register all the functions that we want to expose via OvrGuardianSystem class in GDScript; we use as method names the same names as in VrApi.h but without prefix
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &request_boundary_visible;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "initialize_platform", attributes, method);

	}
}

GDCALLINGCONV void *ovrpl_loader_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)godot::api->godot_alloc(sizeof(ovr_config_data_struct));
	if (ovr_config_data != NULL) {
		ovr_config_data->ovr_mobile_session = ovrplatform::OvrMobileSession::get_singleton_instance();
	}

	return ovr_config_data;
}

GDCALLINGCONV void ovrpl_loader_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {
	if (p_user_data != NULL) {
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data;
		if (ovr_config_data->ovr_mobile_session != NULL) {
			ovr_config_data->ovr_mobile_session = NULL;
		}
	}
}

GDCALLINGCONV godot_variant standalone_initialize(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	// need to write proper code to make this work later 
	CHECK_USER_DATA(
	    bool visible = godot::api->godot_variant_as_bool(p_args[0]);
		godot::api->godot_variant_new_bool(&ret, ovrplatform::request_boundary_visible(ovr_mobile_session, visible));
	)
}