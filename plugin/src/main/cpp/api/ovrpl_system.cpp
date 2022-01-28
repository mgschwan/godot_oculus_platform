/**
 * Created by Fredia Huya-Kouadio.
 */

#include "ovrpl_system.h"
#include "api_common.h"

namespace ovrplatform {
OvrplSystem::OvrplSystem() = default;

OvrplSystem::~OvrplSystem() = default;

void OvrplSystem::_init() {}

void OvrplSystem::_register_methods() {
    register_method("get_driver_version", &OvrplSystem::get_driver_version);
}

String get_driver_version() {
    return vrapi_GetVersionString();
}

} // namespace ovrmobile
