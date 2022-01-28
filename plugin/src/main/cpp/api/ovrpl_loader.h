#include "OVR_Platform.h"
#include "OVR_PlatformVersion.h"
#include "OVR_PlatformInitializeResult.h"
#include "OVR_PlatformInitialize.h"
namespace ovrplatform {
namespace {
using namespace godot;
} 
class OvrplLoader : public Reference{
	GODOT_CLASS(OvrplLoader, Reference)
	public:
    OvrplLoader();

    ~OvrplLoader();

    static void _register_methods();

    void _init();
    // the function to get the standalone loding of the platform sdk
    inline String Initialize_standalone() { return ""; /* ovrplatform::(); */ }
};
}
#endif