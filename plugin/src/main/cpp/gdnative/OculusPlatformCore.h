#ifndef OCULUS_PLATFORM_CORE_H
#define OCULUS_PLATFORM_CORE_H

#include <Godot.hpp>
#include <Ref.hpp>
#include <Spatial.hpp>

#include "OVR_Platform.h"

namespace godot {
class OculusPlatformCore : public Node {
	GODOT_CLASS(OculusPlatformCore, Node)

private:
    //

public:
	static void _register_methods();
	void _init();
	void _ready();

   void initEntitlement(const String appId);

	OculusPlatformCore();
	~OculusPlatformCore();

};
} // namespace godot

#endif // !OCULUS_PLATFORM_CORE_H



