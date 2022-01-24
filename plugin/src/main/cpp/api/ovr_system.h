#ifndef GODOT_OCULUS_MOBILE_PLUGIN_OVR_SYSTEM_H
#define GODOT_OCULUS_MOBILE_PLUGIN_OVR_SYSTEM_H

namespace ovrmobile {
namespace {
using namespace godot;
} // namespace

/// Return the version of the vrapi driver.
String get_driver_version();

class OvrSystem : public Reference {
    GODOT_CLASS(OvrSystem, Reference)

 public:
    OvrSystem();

    ~OvrSystem();

    static void _register_methods();

    void _init();

    inline String get_driver_version() { return ""; /* ovrmobile::get_driver_version(); */ }
};
} // namespace ovrmobile

#endif // GODOT_OCULUS_MOBILE_PLUGIN_OVR_SYSTEM_H
