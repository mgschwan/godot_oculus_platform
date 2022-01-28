#ifndef GODOT_OCULUS_PLATFORM_PLUGIN_OVR_SYSTEM_H
#define GODOT_OCULUS_PLATFORM_PLUGIN_OVR_SYSTEM_H

namespace ovrplatform {
namespace {
using namespace godot;
} // namespace

/// Return the version of the vrapi driver.
String get_driver_version();

class OvrplSystem : public Reference {
    GODOT_CLASS(OvrplSystem, Reference)

 public:
    OvrplSystem();

    ~OvrplSystem();

    static void _register_methods();

    void _init();

    inline String get_driver_version() { return ""; /* ovrmobile::get_driver_version(); */ }
};
} // namespace ovrmobile

#endif // GODOT_OCULUS_MOBILE_PLUGIN_OVR_SYSTEM_H
