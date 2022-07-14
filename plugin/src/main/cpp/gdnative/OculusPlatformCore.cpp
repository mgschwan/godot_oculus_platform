#include "common.h"
#include "gdnative/OculusPlatformCore.h"
#include "jni/ovr_platform_plugin_wrapper.h"

using namespace godot;

void OculusPlatformCore::_register_methods() {
	register_method("_ready", &OculusPlatformCore::_ready);
	register_method("_process", &OculusPlatformCore::_process);
	register_method("_init", &OculusPlatformCore::_init);
	register_method("getUser", &OculusPlatformCore::getUser);
	register_method("getLoggedInUser", &OculusPlatformCore::getLoggedInUser);
	register_method("checkEntitlement", &OculusPlatformCore::checkEntitlement);
	register_method("initEntitlement", &OculusPlatformCore::initEntitlement);
}

OculusPlatformCore::OculusPlatformCore() {
}

OculusPlatformCore::~OculusPlatformCore() {
}

void OculusPlatformCore::_init() {
	// nothing to do here
}

void OculusPlatformCore::_ready() {
}


void OculusPlatformCore::initEntitlement(const String appId) {
    char *c_appId = appId.alloc_c_string();
    ALOGV("Trying to initialize OVR Platform");
    if (ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment && ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_activity) {  
        ALOGV("Yes we are initializing");      
        
        jclass ovr_platform_plugin_class = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->GetObjectClass(ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_instance);
        ALOG_ASSERT(ovr_platform_plugin_class != nullptr, "Invalid jclass value.");

        jmethodID get_activity = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->GetMethodID(ovr_platform_plugin_class, "getMainActivity", "()Landroid/app/Activity;");
        jobject activity = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->CallObjectMethod(ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_instance, get_activity);
        
        ALOGV("Got all objects");      
        
        ovr_PlatformInitializeAndroid(c_appId, activity, ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment);
        ALOGV("Finished initializing");      
        
        ovr_Entitlement_GetIsViewerEntitled();
           __android_log_print(ANDROID_LOG_VERBOSE, "godot_oculus_platform", "Entitlement check for %s", c_appId); 
        initialized = true;     
        
    } else {
        ALOGV("OVR Platform can not be initialized");
    }

}


void OculusPlatformCore::pumpOVRMessages() {
  ovrMessageHandle message = nullptr;

  while ((message = ovr_PopMessage()) != nullptr) {
    switch (ovr_Message_GetType(message)) {
    //   case ovrMessage_Room_CreateAndJoinPrivate:
    //     processCreateAndJoinPrivateRoom(message);
    //     break;
    //   case ovrMessage_Room_GetCurrent:
    //     processGetCurrentRoom(message);
    //     break;
    //   case ovrMessage_Room_Get:
    //     processGetRoom(message);
    //     break;
    //   case ovrMessage_Room_Leave:
    //     processLeaveRoom(message);
    //     break;
    //   case ovrMessage_Room_Join:
    //     processJoinRoom(message);
    //     break;
    //   case ovrMessage_Room_KickUser:
    //     processKickUser(message);
    //     break;
       case ovrMessage_User_GetLoggedInUser:
         processGetLoggedInUser(message);
         break;
       case ovrMessage_User_Get:
         processGetUser(message);
         break;
    //   case ovrMessage_User_GetLoggedInUserFriends:
    //     processGetFriends(message);
    //     break;
    //   case ovrMessage_Room_GetInvitableUsers:
    //     processGetInvitableUsers(message);
    //     break;
    //   case ovrMessage_Room_InviteUser:
    //     processInviteUser(message);
    //     break;
    //   case ovrMessage_Room_SetDescription:
    //     processSetRoomDescription(message);
    //     break;
    //   case ovrMessage_Room_UpdateDataStore:
    //     processUpdateRoomDataStore(message);
    //     break;
    //   case ovrMessage_Notification_Room_RoomUpdate:
    //     processRoomUpdate(message);
    //     break;
    //   case ovrMessage_User_GetUserProof:
    //     processGenerateUserProof(message);
    //     break;
    //   case ovrMessage_User_GetAccessToken:
    //     processGetUserToken(message);
    //     break;
    //   case ovrMessage_Achievements_GetDefinitionsByName:
    //     processGetAchievementDefinition(message);
    //     break;
    //   case ovrMessage_Achievements_GetProgressByName:
    //     processGetAchievementProgress(message);
    //     break;
    //   case ovrMessage_Achievements_Unlock:
    //     processUnlockAchievement(message);
    //     break;
    //   case ovrMessage_Achievements_AddCount:
    //     processAddAchievementCount(message);
    //     break;
    //   case ovrMessage_Achievements_AddFields:
    //     processAddAchievementBitfield(message);
    //     break;
    //   case ovrMessage_Leaderboard_WriteEntry:
    //     processWriteLeaderboardEntry(message);
    //     break;
    //   case ovrMessage_Leaderboard_GetEntries:
    //     processGetLeaderboardEntries(message);
    //     break;
       case ovrMessage_Entitlement_GetIsViewerEntitled:
         processCheckEntitlement(message);
         break;
    //   case ovrMessage_CloudStorage_Load:
    //     processCloudStorageLoad(message);
    //     break;
    //   case ovrMessage_CloudStorage_Save:
    //     processCloudStorageSave(message);
    //     break;
    //   case ovrMessage_CloudStorage_Delete:
    //     processCloudStorageDelete(message);
    //     break;
    //   case ovrMessage_CloudStorage_LoadBucketMetadata:
    //     processCloudMetaData(message);
    //     break;
      default:
        __android_log_print(ANDROID_LOG_VERBOSE, "godot_oculus_platform", "unknown OVR Platform message %d", ovr_Message_GetType(message));
    }
    //printf("\nCommand > %s", commandBuffer);
    ovr_FreeMessage(message);
  }
}



void OculusPlatformCore::_process(float delta) {
    if (initialized)
        pumpOVRMessages();
}


void OculusPlatformCore::getUser(ovrID userID) {
  ALOGV("\nTrying to get user %llu\n", userID);

  ovrRequest req;

  req = ovr_User_Get(userID);
}

void OculusPlatformCore::processGetUser(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ALOGV("Received get user success\n");

    ovrUser* user = ovr_Message_GetUser(message);
    __android_log_print(ANDROID_LOG_VERBOSE, "godot_oculus_platform", "user %s %s\n", ovr_User_GetID(user), ovr_User_GetOculusID(user));
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    __android_log_print(ANDROID_LOG_VERBOSE, "godot_oculus_platform","Received get user failure: %s\n", ovr_Error_GetMessage(error));
  }
}



void OculusPlatformCore::checkEntitlement() {
  ALOGV("\nChecking for an entitlement\n");

  ovrRequest req;

  req = ovr_Entitlement_GetIsViewerEntitled();
}

void OculusPlatformCore::processCheckEntitlement(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ALOGV("User has an entitlement\n");
  } else {
    ALOGV("Could NOT get an entitlement\n");
    //TODO: Send a signal that the entitlement check failed
  }
}


void OculusPlatformCore::getLoggedInUser() {
  ALOGV("\nTrying to get logged in user\n");

  ovrRequest req;

  req = ovr_User_GetLoggedInUser();
}

void OculusPlatformCore::processGetLoggedInUser(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ALOGV("Received get logged in user success\n");

    ovrUserHandle user = ovr_Message_GetUser(message);
    __android_log_print(ANDROID_LOG_VERBOSE, "godot_oculus_platform","user %llu %s\n", ovr_User_GetID(user), ovr_User_GetOculusID(user));
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    __android_log_print(ANDROID_LOG_VERBOSE, "godot_oculus_platform","Received get user failure: %s\n", ovr_Error_GetMessage(error));
  }
}