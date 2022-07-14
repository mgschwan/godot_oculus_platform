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
    bool initialized = false;

public:
	static void _register_methods();
	void _init();
	void _ready();
	void _process(float delta);
	
	void pumpOVRMessages();

	void getUser(ovrID userID);
	void processGetUser(ovrMessageHandle message);

	void checkEntitlement();
	void processCheckEntitlement(ovrMessageHandle message);

	void getLoggedInUser();
	void processGetLoggedInUser(ovrMessageHandle message);

    void initEntitlement(const String appId);

	OculusPlatformCore();
	~OculusPlatformCore();

};
} // namespace godot

#endif // !OCULUS_PLATFORM_CORE_H



