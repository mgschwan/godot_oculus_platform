#include "gdnative/OculusPlatformCore.h"

using namespace godot;

void OculusPlatformCore::_register_methods() {
	register_method("_ready", &OculusPlatformCore::_ready);
	register_method("initEntitlement", &OculusPlatformCore::initEntitlement);
	//register_property<OpenXRHand, int>("relative_transform", &OpenXRHand::set_relative_transform, &OpenXRHand::get_relative_transform, 0, GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_DEFAULT, GODOT_PROPERTY_HINT_ENUM, "Global,Local");
}

OculusPlatformCore::OculusPlatformCore() {
}

OculusPlatformCore::~OculusPlatformCore() {
}

void OculusPlatformCore::_init() {
	// nothing to do here
}

void OculusPlatformCore::_ready() {
}


void OculusPlatformCore::initEntitlement() {
    ovr_Entitlement_GetIsViewerEntitled();
}
