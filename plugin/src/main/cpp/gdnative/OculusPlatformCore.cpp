#include "common.h"
#include "OculusPlatformCore.h"
#include "jni/ovr_platform_plugin_wrapper.h"

using namespace godot;

void OculusPlatformCore::_register_methods() {
  //input methods
	register_method("_ready", &OculusPlatformCore::_ready);
	register_method("_process", &OculusPlatformCore::_process);
	register_method("_init", &OculusPlatformCore::_init);

	register_method("initialize", &OculusPlatformCore::initialize);
  register_method("platform_initialized", &OculusPlatformCore::isPlatformInitialized);
  register_method("checkEntitlement", &OculusPlatformCore::checkEntitlement);
  register_method("getUser", &OculusPlatformCore::getUser);
	register_method("getLoggedInUser", &OculusPlatformCore::getLoggedInUser);
	register_method("getLoggedInUserFriends", &OculusPlatformCore::getLoggedInUserFriends);
  register_method("getUserToken", &OculusPlatformCore::getUserToken);
  register_method("getUserProof", &OculusPlatformCore::generateUserProof);
	

  register_method("writeCloudData", &OculusPlatformCore::writeCloudData);
	register_method("getCloudData", &OculusPlatformCore::getCloudData);
	register_method("deleteCloudData", &OculusPlatformCore::deleteCloudData);
	register_method("getCloudMetaData", &OculusPlatformCore::getCloudMetaData);

  //signals (technically output methods)
  register_signal<OculusPlatformCore>((char*)"platform_initialized","success", GODOT_VARIANT_TYPE_BOOL,"error",GODOT_VARIANT_TYPE_STRING);
  register_signal<OculusPlatformCore>((char*)"get_entitlement_check_done","success", GODOT_VARIANT_TYPE_BOOL);
  register_signal<OculusPlatformCore>((char*)"get_logged_in_user_done","success", GODOT_VARIANT_TYPE_BOOL,"user_id",GODOT_VARIANT_TYPE_INT,"oculus_user_id",GODOT_VARIANT_TYPE_STRING);
  register_signal<OculusPlatformCore>((char*)"get_user_done","success", GODOT_VARIANT_TYPE_BOOL,"user_id",GODOT_VARIANT_TYPE_INT,"oculus_user_id",GODOT_VARIANT_TYPE_STRING);
  register_signal<OculusPlatformCore>((char*)"get_user_token_done","success", GODOT_VARIANT_TYPE_BOOL,"user_token",GODOT_VARIANT_TYPE_STRING);
  register_signal<OculusPlatformCore>((char*)"get_user_proof_done","success", GODOT_VARIANT_TYPE_BOOL,"user_proof",GODOT_VARIANT_TYPE_STRING);
  register_signal<OculusPlatformCore>((char*)"get_user_friends_done","success", GODOT_VARIANT_TYPE_BOOL,"user_friends",GODOT_VARIANT_TYPE_ARRAY);

  register_signal<OculusPlatformCore>((char*)"write_cloud_data_done","success", GODOT_VARIANT_TYPE_BOOL);
  register_signal<OculusPlatformCore>((char*)"get_cloud_data_done","success", GODOT_VARIANT_TYPE_BOOL,"data",GODOT_VARIANT_TYPE_STRING);
  register_signal<OculusPlatformCore>((char*)"delete_cloud_data_done","success", GODOT_VARIANT_TYPE_BOOL);
  register_signal<OculusPlatformCore>((char*)"get_cloud_meta_data_done","success", GODOT_VARIANT_TYPE_BOOL,"data_size",GODOT_VARIANT_TYPE_INT,
  															"saved_time",GODOT_VARIANT_TYPE_REAL,"counter",GODOT_VARIANT_TYPE_INT,
															"extraData",GODOT_VARIANT_TYPE_STRING,"status",GODOT_VARIANT_TYPE_STRING);

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

/// handles android appid login, does not support standalone login yet 
/// appid according to id taken from oculus devloper console
/// async, initialize asynchronously and wait for success 
/// or try to initialize and handle error
void OculusPlatformCore::initialize(const String appId, bool async = false) {
    char *c_appId = appId.alloc_c_string();
    ALOGV("Trying to initialize OVR Platform");
    if (ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment && ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_activity) {  
        ALOGV("Yes we are initializing");      
        
        jclass ovr_platform_plugin_class = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->GetObjectClass(ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_instance);
        ALOG_ASSERT(ovr_platform_plugin_class != nullptr, "Invalid jclass value.");

        jmethodID get_activity = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->GetMethodID(ovr_platform_plugin_class, "getMainActivity", "()Landroid/app/Activity;");
        jobject activity = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->CallObjectMethod(ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_instance, get_activity);
        
        ALOGV("Got all objects");   
        if(async){   
          initializePlatform(c_appId,activity);
        } else {
          ovr_PlatformInitializeAndroidAsynchronous(c_appId, activity, ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment);
        }
    } else {
        ALOGV("OVR Platform can not be initialized");
    }

}

void OculusPlatformCore::pumpOVRMessages() {
  ovrMessageHandle message = nullptr;

  while ((message = ovr_PopMessage()) != nullptr) {
    ovrMessageType message_type = ovr_Message_GetType(message);
    switch (message_type) {
         case ovrMessage_PlatformInitializeAndroidAsynchronous:
            ALOGV("platform initialized async successful");
            processInitializePlatform(message);
            break;
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
       case ovrMessage_User_GetLoggedInUserFriends:
         processGetFriends(message);
         break;
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
       case ovrMessage_User_GetUserProof:
         processGenerateUserProof(message);
         break;
       case ovrMessage_User_GetAccessToken:
         processGetUserToken(message);
         break;
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
       case ovrMessage_CloudStorage_Load:
         processCloudStorageLoad(message);
         break;
       case ovrMessage_CloudStorage_Save:
         processCloudStorageSave(message);
         break;
       case ovrMessage_CloudStorage_Delete:
         processCloudStorageDelete(message);
         break;
       case ovrMessage_CloudStorage_LoadBucketMetadata:
         processCloudMetaData(message);
         break;
      default:
        ALOGV("unknown OVR Platform message %d",message_type);
    }
    //printf("\nCommand > %s", commandBuffer);
    ovr_FreeMessage(message);
  }
}

void OculusPlatformCore::_process(float delta) {
    pumpOVRMessages();
}


bool OculusPlatformCore::isPlatformInitialized(){
    bool value = ovr_IsPlatformInitialized();
    return value;
  }

void OculusPlatformCore::initializePlatform(char * app_id, jobject activity){
    ovrPlatformInitializeResult status = ovr_PlatformInitializeAndroid(app_id, activity, ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment);
    const char * error = ovrPlatformInitializeResult_ToString(status);
    switch (status) {
        case ovrPlatformInitialize_Success:
          ALOGV("initialize success"); 
          break;
        case ovrPlatformInitialize_Uninitialized:
          ALOGV("initialize failure"); // exit here i guess 
          break;
        case ovrPlatformInitialize_PreLoaded:
          ALOGV("already loaded");
          break;
        case ovrPlatformInitialize_FileInvalid:
          ALOGV("initialize failure , file invalid"); // exit here i guess
          break;
        case ovrPlatformInitialize_SignatureInvalid:
          ALOGV("initialize failure , sign invalid");
          break;
        case ovrPlatformInitialize_UnableToVerify:
          ALOGV("initialize failure , verify faliure");
          break;
        case ovrPlatformInitialize_VersionMismatch:
          ALOGV("initialize failure , version mismatch");
          break;
        case ovrPlatformInitialize_Unknown:
          ALOGV("initialize failure , unknown error");
          break;
        case ovrPlatformInitialize_InvalidCredentials:
          ALOGV("initialize failure , Invalid Credentials");
          break;
        case ovrPlatformInitialize_NotEntitled:
          ALOGV("initialize failure , Not entitled ");
          break;
        default:
          ALOGV("unknown status %d",status);
        }
    ALOGV("emmitting signal %i %s" , isPlatformInitialized(),error);
    emit_signal("platform_initialized",isPlatformInitialized(),error);
}

void OculusPlatformCore::processInitializePlatform(ovrMessageHandle message){
    if (!ovr_Message_IsError(message)) {
      emit_signal("platform_initialized",isPlatformInitialized(),NULL);
    } else {
      const ovrErrorHandle error = ovr_Message_GetError(message);
      emit_signal("platform_initialized",isPlatformInitialized(),ovr_Error_GetDisplayableMessage(error));
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
    emit_signal("get_entitlement_check_done",true);
  } else {
    ALOGV("Could NOT get an entitlement\n");
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received get entitlement failure: %s\n", ovr_Error_GetMessage(error));
    emit_signal("get_entitlement_check_done",false);
    //TODO: Send a signal that the entitlement check failed
  }
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
    ovrID user_id = ovr_User_GetID(user);
    const char * user_oculus_id = ovr_User_GetOculusID(user);
    ALOGV("user  = %llu oculus id = %s \n",user_id,user_oculus_id);
    emit_signal("get_user_done",true,user_id,user_oculus_id);
    
  } else {

    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received get user failure: %s\n", ovr_Error_GetMessage(error));
    emit_signal("get_user_done",false,NULL,NULL);
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
    ovrID user_id = ovr_User_GetID(user);
    const char * user_oculus_id = ovr_User_GetOculusID(user);
    ALOGV("user  = %llu oculus id = %s \n",user_id,user_oculus_id);
    emit_signal("get_logged_in_user_done",true,user_id,user_oculus_id);
  } else {

    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received get user failure: %s\n", ovr_Error_GetMessage(error));
    emit_signal("get_logged_in_user_done",false,NULL,NULL);
  }
}


void OculusPlatformCore::getLoggedInUserFriends() {
  printf("\nTrying to get friends for logged in user\n");

  ovrRequest req;

  req = ovr_User_GetLoggedInUserFriends();
}

void OculusPlatformCore::processGetFriends(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    printf("Received get friends success\n");

    ovrUserArrayHandle users = ovr_Message_GetUserArray(message);
    generateUserArray(users);
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received get friends failure: %s\n", ovr_Error_GetMessage(error));
    emit_signal("get_user_freinds_done",false,NULL);
  }
}

void OculusPlatformCore::generateUserArray(ovrUserArrayHandle users) {
  size_t nUsers = ovr_UserArray_GetSize(users);
  for (size_t i = 0; i < nUsers; ++i) {
    ovrUserHandle user = ovr_UserArray_GetElement(users, i);
    printf(
        "user %llu %s %s %s\n",
        ovr_User_GetID(user),
        ovr_User_GetOculusID(user),
        ovr_User_GetPresence(user),
        ovr_User_GetInviteToken(user));
  // need to make custom dictionary for godot here, then emit that 
  // emit_signal("get_user_freinds_done",true,)
  }
}


void OculusPlatformCore::getUserToken() {
  printf("\nTrying to generate a user token\n");

  ovrRequest req;

  req = ovr_User_GetAccessToken();
}

void OculusPlatformCore::processGetUserToken(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    printf("Received user token %s\n", ovr_Message_GetString(message));
    emit_signal("get_user_token_done",true,ovr_Message_GetString(message));
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received user token failure: %s\n", ovr_Error_GetMessage(error));
    emit_signal("get_user_token_done",false,ovr_Error_GetMessage(error));
  }
}


void OculusPlatformCore::generateUserProof() {
  printf("\nTrying to generate a user nonce\n");

  ovrRequest req;

  req = ovr_User_GetUserProof();
}

void OculusPlatformCore::processGenerateUserProof(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ovrUserProofHandle proof = ovr_Message_GetUserProof(message);
    printf("Received user nonce %s\n", ovr_UserProof_GetNonce(proof));
    emit_signal("get_user_proof_done",true,ovr_Message_GetString(message));
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received user nonce failure: %s\n", ovr_Error_GetMessage(error));
    emit_signal("get_user_proof_done",false,ovr_Error_GetMessage(error));
  }
}


// IMPORTANT NOTE:
// ovr_CloudStorage_Save is only passing in a pointer to your data in an async call.  Your data
// will need to stay alive and unmodified until you receive a ovrMessage_CloudStorage_Save message
// indicating that the save was successful.  If the data is destroyed or modified prior to
// receiving that message there's a good chance the proper data won't be saved.
void OculusPlatformCore::writeCloudData(const String cloud_bucket, const String cloud_key, const String data, String extra, int counter = 0) {
ALOGV("\nSaving cloud data.\n");
ovrRequest req;
req = ovr_CloudStorage_Save(cloud_bucket.alloc_c_string(), cloud_key.alloc_c_string(), &data, sizeof(data), counter, extra.alloc_c_string());
}

void OculusPlatformCore::processCloudStorageSave(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ALOGV("Cloud data was saved!\n");
  emit_signal("write_cloud_data_done",true);
  } else {
    ALOGV("Could NOT save cloud data\n");
    ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Error Code: %d\n", ovr_Error_GetCode(error));
    ALOGV("Error Message: %s\n", ovr_Error_GetMessage(error));
  emit_signal("write_cloud_data_done",false);
  }
}


void OculusPlatformCore::getCloudData(const String cloud_bucket, const String cloud_key) {
  ALOGV("\nLoading cloud data.\n");

  ovrRequest req;

  req = ovr_CloudStorage_Load(cloud_bucket.alloc_c_string(), cloud_key.alloc_c_string());
}

void OculusPlatformCore::processCloudStorageLoad(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ALOGV("Cloud data was loaded!\n");
    ovrCloudStorageDataHandle response = ovr_Message_GetCloudStorageData(message);
    const void* data = ovr_CloudStorageData_GetData(response);
    unsigned int data_size = ovr_CloudStorageData_GetDataSize(response);
    const char * loaded_data = static_cast<const char*>(data); 
    emit_signal("get_cloud_data_done",true,loaded_data);
    } else {
      ALOGV("Could NOT load cloud data\n");
      ovrErrorHandle error = ovr_Message_GetError(message);
      ALOGV("Error Code: %d\n", ovr_Error_GetCode(error));
      ALOGV("Error Message: %s\n", ovr_Error_GetMessage(error));
    emit_signal("get_cloud_data_done",false,NULL);
    }
}


void OculusPlatformCore::deleteCloudData(const String cloud_bucket, const String cloud_key) {
  ALOGV("\nDeleting cloud data.\n");

  ovrRequest req;

  req = ovr_CloudStorage_Delete(cloud_bucket.alloc_c_string(), cloud_key.alloc_c_string());
}

void OculusPlatformCore::processCloudStorageDelete(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ALOGV("Cloud data was deleted!\n");
    emit_signal("delete_cloud_data_done",true);
    } else {
      ovrErrorHandle error = ovr_Message_GetError(message);
      ALOGV("Received cloud delete failure: %s\n", ovr_Error_GetMessage(error));
      emit_signal("delete_cloud_data_done",false);
    }
}


void OculusPlatformCore::getCloudMetaData(const String cloud_bucket) {
  ALOGV("\nLoading Cloud metadata\n");

  ovrRequest req;
  req = ovr_CloudStorage_LoadBucketMetadata(cloud_bucket.alloc_c_string());
}

void OculusPlatformCore::processCloudMetaData(ovrMessageHandle message) {
  if (!ovr_Message_IsError(message)) {
    ALOGV("Received the following cloud metadata:\n");

    ovrCloudStorageMetadataArrayHandle metaDataArray =
        ovr_Message_GetCloudStorageMetadataArray(message);

    size_t numElements = ovr_CloudStorageMetadataArray_GetSize(metaDataArray);

    for (size_t x = 0; x < numElements; x++) {
      ovrCloudStorageMetadataHandle metaDataHandle =
          ovr_CloudStorageMetadataArray_GetElement(metaDataArray, x);

    unsigned int data_size = ovr_CloudStorageMetadata_GetDataSize(metaDataHandle);
    double saved_time = ovr_CloudStorageMetadata_GetSaveTime(metaDataHandle);
    ovrCloudStorageDataStatus status = ovr_CloudStorageMetadata_GetStatus(metaDataHandle);
    const char* extraData = ovr_CloudStorageMetadata_GetExtraData(metaDataHandle);
    int counter = ovr_CloudStorageMetadata_GetCounter(metaDataHandle);
    String message = ovrCloudStorageDataStatus_ToString(status);
    ALOGV("%u %lld %s %d ", data_size, saved_time, extraData, counter);
    switch (status) {
      case ovrCloudStorageDataStatus_InSync:
        ALOGV("ovrCloudStorageDataStatus_InSync\n");
        break;
      case ovrCloudStorageDataStatus_NeedsDownload:
        ALOGV("ovrCloudStorageDataStatus_NeedsDownload\n");
        break;
      case ovrCloudStorageDataStatus_RemoteDownloading:
        ALOGV("ovrCloudStorageDataStatus_RemoteDownloading\n");
        break;
      case ovrCloudStorageDataStatus_NeedsUpload:
        ALOGV("ovrCloudStorageDataStatus_NeedsUpload\n");
        break;
      case ovrCloudStorageDataStatus_LocalUploading:
        ALOGV("ovrCloudStorageDataStatus_LocalUploading\n");
        break;
      case ovrCloudStorageDataStatus_InConflict:
        ALOGV("ovrCloudStorageDataStatus_InConflict\n");
        break;
      case ovrCloudStorageDataStatus_Unknown:
      default:
        ALOGV("ovrCloudStorageDataStatus_Unknown\n");
        break;
    }
    emit_signal("get_cloud_meta_data_done",true,data_size,saved_time,counter,extraData,status);
    }
  } else {
    ALOGV("Could NOT get cloud metadata\n");
    emit_signal("get_cloud_meta_data_done",false,NULL,NULL,NULL,NULL,NULL);
  }
}

