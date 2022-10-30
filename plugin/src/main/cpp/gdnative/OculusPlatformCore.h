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
		void initializePlatform(char * app_id, jobject activity);

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);
		
		void pumpOVRMessages();
		
		//command functions
		void initialize(const String appId, bool async);
		
		void checkEntitlement();
		void getUser(ovrID userID);
		void getLoggedInUser();
		void getLoggedInUserFriends();
		void generateUserProof();
		void getUserToken();

		void writeCloudData(const String cloud_bucket, const String cloud_key, const String data, String extra, int counter);
		void getCloudData(const String cloud_bucket, const String cloud_key);
		void deleteCloudData(const String cloud_bucket, const String cloud_key);
		void getCloudMetaData(const String cloud_bucket);

		// Notification handlers
		void processInitializePlatform(ovrMessageHandle message);

		void processCheckEntitlement(ovrMessageHandle message);
		void processGetUser(ovrMessageHandle message);
		void processGetLoggedInUser(ovrMessageHandle message);
		void processGetFriends(ovrMessageHandle message);
		void processGenerateUserProof(ovrMessageHandle message);
  		void processGetUserToken(ovrMessageHandle message);

		void processCloudStorageLoad(ovrMessageHandle message);
		void processCloudStorageSave(ovrMessageHandle message);
		void processCloudStorageDelete(ovrMessageHandle message);
		void processCloudMetaData(ovrMessageHandle message);

		//helper functions
		bool isPlatformInitialized();
		void generateUserArray(ovrUserArrayHandle users);		

		OculusPlatformCore();
		~OculusPlatformCore();

	};
} // namespace godot

#endif // !OCULUS_PLATFORM_CORE_H



