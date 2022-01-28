/**
 * Created by Fredia Huya-Kouadio.
 */

#include "ovr_system.h"
#include "api_common.h"

namespace ovrmobile {
OvrSystem::OvrSystem() = default;

OvrSystem::~OvrSystem() = default;

void OvrSystem::_init() {}

void OvrSystem::_register_methods() {
    register_method("get_driver_version", &OvrSystem::get_driver_version);
}

String get_driver_version() {
    return vrapi_GetVersionString();
}

} // namespace ovrmobile
