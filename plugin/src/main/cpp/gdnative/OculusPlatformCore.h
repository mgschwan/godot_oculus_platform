#ifndef OCULUS_PLATFORM_CORE_H
#define OCULUS_PLATFORM_CORE_H

#include <Godot.hpp>
#include <Ref.hpp>
#include <Spatial.hpp>
#include <Array.hpp>
#include <stdlib.h>
#include <sstream>

#include "OVR_Platform.h"

namespace godot {
	class OculusPlatformCore : public Node {
		GODOT_CLASS(OculusPlatformCore, Node)

	private:
		void initializePlatform(char * app_id, jobject activity);
		void outputRoomDetails(ovrRoomHandle room,Dictionary &response);
		void generateUserArray(ovrUserArrayHandle users,Dictionary &response);		

	public:
		static void _register_methods();
		void _init();
		void _ready();
		void _process(float delta);
		
		void pumpOVRMessages();
		
		//command functions
		void initialize(const String appId, bool async);
		
		void createAndJoinPrivateRoom(String joinType, unsigned int maxUsers);
		void getCurrentRoom();
		void getRoom(String roomID);
		void leaveRoom(String roomID);
		void joinRoom(String roomID);
		void kickUser(String roomID, String userID, int kickduration = 10);
		void getInvitableUsers();
		void inviteUser(String roomID, String inviteToken);
		void setRoomDescription(String roomID,String description);

		void checkEntitlement();
		void getUser(String userID);
		void getLoggedInUser();
		void getLoggedInUserFriends();
		void generateUserProof();
		void getUserToken();

		void writeLeaderboardEntry(String leaderboardName, String value,String extraData,bool forceupdate);
  		void getLeaderboardEntries(String leaderboardName, int limit = 10);

		void writeCloudData(const String cloud_bucket, const String cloud_key, const Dictionary data, String extra, int counter);
		void getCloudData(const String cloud_bucket, const String cloud_key);
		void deleteCloudData(const String cloud_bucket, const String cloud_key);
		void getCloudMetaData(const String cloud_bucket);

		// Notification handlers
		void processInitializePlatform(ovrMessageHandle message);

		void processCreateAndJoinPrivateRoom(ovrMessageHandle message);
		void processGetCurrentRoom(ovrMessageHandle message);
		void processGetRoom(ovrMessageHandle message);
		void processLeaveRoom(ovrMessageHandle message);
		void processJoinRoom(ovrMessageHandle message);
		void processKickUser(ovrMessageHandle message);
		void processGetInvitableUsers(ovrMessageHandle message);
		void processInviteUser(ovrMessageHandle message);
		void processSetRoomDescription(ovrMessageHandle message);

		void processCheckEntitlement(ovrMessageHandle message);
		void processGetUser(ovrMessageHandle message);
		void processGetLoggedInUser(ovrMessageHandle message);
		void processGetFriends(ovrMessageHandle message);
		void processGenerateUserProof(ovrMessageHandle message);
  		void processGetUserToken(ovrMessageHandle message);

		void processWriteLeaderboardEntry(ovrMessageHandle message);
  		void processGetLeaderboardEntries(ovrMessageHandle message);

		void processCloudStorageLoad(ovrMessageHandle message);
		void processCloudStorageSave(ovrMessageHandle message);
		void processCloudStorageDelete(ovrMessageHandle message);
		void processCloudMetaData(ovrMessageHandle message);

		//helper functions
		bool isPlatformInitialized();
		
		OculusPlatformCore();
		~OculusPlatformCore();

	};
} // namespace godot

#endif // !OCULUS_PLATFORM_CORE_H



