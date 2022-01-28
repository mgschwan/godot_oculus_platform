
#include "ovrpl_loader.h"



namespace ovrplatform {

OvrplLoader::OvrplLoader() = default;

OvrplLoader::~OvrplLoader() = default;

void OvrplLoader::_init() {}

void OvrplLoader::_register_methods() {
    register_method("get_driver_version", &OvrplLoader::Initialize_standalone());
}
// need to addin the necessary structs to add in the arguements as well
String Initialize_standalone() {
    return ovr_Platform_InitializeStandaloneOculusEx();
}

}
