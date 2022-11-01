// written by "S.Y.B.I.O.T.E" aka Rahul Ghosh
// with lots of help from Micheal Gschwandtner
#include "common.h"
#include "OculusPlatformCore.h"
#include "jni/ovr_platform_plugin_wrapper.h"

using namespace godot;

void OculusPlatformCore::_register_methods()
{
  // input methods
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

  register_method("submitScoreToLeaderboard", &OculusPlatformCore::writeLeaderboardEntry);
  register_method("getScoreFromLeaderboard", &OculusPlatformCore::getLeaderboardEntries);

  register_method("createAndJoinPrivateRoom", &OculusPlatformCore::createAndJoinPrivateRoom);
  register_method("getCurrentRoom", &OculusPlatformCore::getCurrentRoom);
  register_method("leaveRoom", &OculusPlatformCore::leaveRoom);
  register_method("joinRoom", &OculusPlatformCore::joinRoom);
  register_method("kickUser", &OculusPlatformCore::kickUser);
  register_method("getInvitableUsers", &OculusPlatformCore::getInvitableUsers);
  register_method("inviteUser", &OculusPlatformCore::inviteUser);
  register_method("setRoomDescription", &OculusPlatformCore::setRoomDescription);

  register_method("writeCloudData", &OculusPlatformCore::writeCloudData);
  register_method("getCloudData", &OculusPlatformCore::getCloudData);
  register_method("deleteCloudData", &OculusPlatformCore::deleteCloudData);
  register_method("getCloudMetaData", &OculusPlatformCore::getCloudMetaData);
  register_method("updateRoomDatastore",&OculusPlatformCore::updateRoomDataStore);
  // signals (technically output methods)
  register_signal<OculusPlatformCore>((char *)"platform_initialized", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"get_entitlement_check_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);

  register_signal<OculusPlatformCore>((char *)"get_logged_in_user_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"get_user_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"get_user_token_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"get_user_proof_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"get_user_friends_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);

  register_signal<OculusPlatformCore>((char *)"submit_score_to_leaderboard_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"get_score_from_leaderboard_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);

  register_signal<OculusPlatformCore>((char *)"create_and_join_private_room_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"get_current_room_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"leave_room_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"join_room_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"kick_user_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"get_invitable_users_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"invite_user_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"set_room_description_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"update_room_datastore_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"room_update_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);

  register_signal<OculusPlatformCore>((char *)"write_cloud_data_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"get_cloud_data_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"delete_cloud_data_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
  register_signal<OculusPlatformCore>((char *)"get_cloud_meta_data_done", "response", GODOT_VARIANT_TYPE_DICTIONARY);
}

#pragma region Godot node functions
OculusPlatformCore::OculusPlatformCore()
{
}

OculusPlatformCore::~OculusPlatformCore()
{
}

void OculusPlatformCore::_init()
{
  // nothing to do here
}

void OculusPlatformCore::_ready()
{
}

void OculusPlatformCore::pumpOVRMessages()
{
  ovrMessageHandle message = nullptr;

  while ((message = ovr_PopMessage()) != nullptr)
  {
    ovrMessageType message_type = ovr_Message_GetType(message);
    switch (message_type)
    {
    case ovrMessage_PlatformInitializeAndroidAsynchronous:
      ALOGV("platform initialized async successful");
      processInitializePlatform(message);
      break;
    case ovrMessage_Room_CreateAndJoinPrivate:
      processCreateAndJoinPrivateRoom(message);
      break;
    case ovrMessage_Room_GetCurrent:
      processGetCurrentRoom(message);
      break;
    case ovrMessage_Room_Get:
      processGetRoom(message);
      break;
    case ovrMessage_Room_Leave:
      processLeaveRoom(message);
      break;
    case ovrMessage_Room_Join:
      processJoinRoom(message);
      break;
    case ovrMessage_Room_KickUser:
      processKickUser(message);
      break;
    case ovrMessage_User_GetLoggedInUser:
      processGetLoggedInUser(message);
      break;
    case ovrMessage_User_Get:
      processGetUser(message);
      break;
    case ovrMessage_User_GetLoggedInUserFriends:
      processGetFriends(message);
      break;
    case ovrMessage_Room_GetInvitableUsers:
      processGetInvitableUsers(message);
      break;
    case ovrMessage_Room_InviteUser:
      processInviteUser(message);
      break;
    case ovrMessage_Room_SetDescription:
      processSetRoomDescription(message);
      break;
    case ovrMessage_Room_UpdateDataStore:
      processUpdateRoomDataStore(message);
      break;
    case ovrMessage_Notification_Room_RoomUpdate:
      processRoomUpdate(message);
      break;
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
    case ovrMessage_Leaderboard_WriteEntry:
      processWriteLeaderboardEntry(message);
      break;
    case ovrMessage_Leaderboard_GetEntries:
      processGetLeaderboardEntries(message);
      break;
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
      ALOGV("unknown OVR Platform message %d", message_type);
    }
    ovr_FreeMessage(message);
  }
}

void OculusPlatformCore::_process(float delta)
{
  pumpOVRMessages();
}
#pragma endregion

/// handles android appid login, does not support standalone login yet
/// appid according to id taken from oculus devloper console
/// async, initialize asynchronously and wait for success
/// or try to initialize and handle error

// initialization functions
#pragma region initialization functions

void OculusPlatformCore::initialize(const String appId, bool async = false)
{
  char *c_appId = appId.alloc_c_string();
  ALOGV("Trying to initialize OVR Platform");
  if (ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment && ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_activity)
  {
    ALOGV("Yes we are initializing");

    jclass ovr_platform_plugin_class = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->GetObjectClass(ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_instance);
    ALOG_ASSERT(ovr_platform_plugin_class != nullptr, "Invalid jclass value.");

    jmethodID get_activity = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->GetMethodID(ovr_platform_plugin_class, "getMainActivity", "()Landroid/app/Activity;");
    jobject activity = ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment->CallObjectMethod(ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_instance, get_activity);

    ALOGV("Got all objects");
    if (async)
    {
      initializePlatform(c_appId, activity);
    }
    else
    {
      ovr_PlatformInitializeAndroidAsynchronous(c_appId, activity, ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment);
    }
  }
  else
  {
    ALOGV("OVR Platform can not be initialized");
  }
}

bool OculusPlatformCore::isPlatformInitialized()
{
  bool value = ovr_IsPlatformInitialized();
  return value;
}

void OculusPlatformCore::initializePlatform(char *app_id, jobject activity)
{
  Dictionary response;
  ovrPlatformInitializeResult status = ovr_PlatformInitializeAndroid(app_id, activity, ovrplatform::OvrPlatformPluginWrapper::ovr_platform_plugin_environment);
  const char *error = ovrPlatformInitializeResult_ToString(status);
  ALOGV("emmitting signal %i %s", isPlatformInitialized(), error);
  response["success"] = isPlatformInitialized();
  if (!response["success"])
    response["error"] = error;
  emit_signal("platform_initialized", response);
}

void OculusPlatformCore::processInitializePlatform(ovrMessageHandle message)
{
  Dictionary response;
  if (ovr_Message_IsError(message))
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    response["error"] = ovr_Error_GetDisplayableMessage(error);
  }
  response["success"] = isPlatformInitialized();
  emit_signal("platform_initialized", response);
}

void OculusPlatformCore::checkEntitlement()
{
  ALOGV("\nChecking for an entitlement\n");

  ovrRequest req;

  req = ovr_Entitlement_GetIsViewerEntitled();
}

void OculusPlatformCore::processCheckEntitlement(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (!response["success"])
  {
    ALOGV("Could NOT get an entitlement\n");
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received get entitlement failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  ALOGV("entitlement signal");
  emit_signal("get_entitlement_check_done", response);
}

#pragma endregion

// User Functions
#pragma region user functions
void OculusPlatformCore::getUser(String userID)
{
  ALOGV("\nTrying to get user %s\n", userID.alloc_c_string());

  ovrRequest req;
  ovrID uID = std::strtoull(userID.alloc_c_string(), NULL, 10);
  req = ovr_User_Get(uID);
}

void OculusPlatformCore::processGetUser(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received get user success\n");
    ovrUser *user = ovr_Message_GetUser(message);
    ovrID user_id = ovr_User_GetID(user);
    const char *user_oculus_id = ovr_User_GetOculusID(user);
    response["user_id"] = String::num_int64(user_id);
    response["oculus_id"] = user_oculus_id;
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("get_user_done", response);
}

void OculusPlatformCore::getLoggedInUser()
{
  ALOGV("\nTrying to get logged in user\n");

  ovrRequest req;

  req = ovr_User_GetLoggedInUser();
}

void OculusPlatformCore::processGetLoggedInUser(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received get logged in user success\n");
    ovrUserHandle user = ovr_Message_GetUser(message);
    ovrID user_id = ovr_User_GetID(user);
    const char *user_oculus_id = ovr_User_GetOculusID(user);
    response["user_id"] = String::num_int64(user_id);
    response["oculus_id"] = user_oculus_id;
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    response["error"] = ovr_Error_GetMessage(error);
  }

  ALOGV("emitting signal, login user");
  emit_signal("get_logged_in_user_done", response);
}

void OculusPlatformCore::getLoggedInUserFriends()
{
  ALOGV("\nTrying to get friends for logged in user\n");

  ovrRequest req;

  req = ovr_User_GetLoggedInUserFriends();
}

void OculusPlatformCore::processGetFriends(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received get friends success\n");
    ovrUserArrayHandle users = ovr_Message_GetUserArray(message);
    generateUserArray(users, response);

  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("get_user_friends_done", response);
}

void OculusPlatformCore::generateUserArray(ovrUserArrayHandle users, Dictionary &response)
{
  ALOGV("in generateUserArray success\n");

  size_t nUsers = ovr_UserArray_GetSize(users);
  ALOGV("friends %u \n",nUsers);
  response["count"] = int(nUsers);
  Array usersfriends;
  for (size_t i = 0; i < nUsers; ++i)
  {
    ovrUserHandle user = ovr_UserArray_GetElement(users, i);
    Dictionary userinfo;
    userinfo["user_id"] = String::num_int64(ovr_User_GetID(user));
    userinfo["oculus_user_id"] = ovr_User_GetOculusID(user);
    userinfo["user_action"] = ovr_User_GetPresence(user);
    userinfo["invite_token"] = ovr_User_GetInviteToken(user);
    usersfriends.append(userinfo);
    ALOGV(
        "user %llu %s %s %s\n",
        ovr_User_GetID(user),
        ovr_User_GetOculusID(user),
        ovr_User_GetPresence(user),
        ovr_User_GetInviteToken(user));
    // need to make custom dictionary for godot here, then emit that
    response["friends"] = usersfriends;
  }
}

void OculusPlatformCore::getUserToken()
{
  ALOGV("\nTrying to generate a user token\n");

  ovrRequest req;

  req = ovr_User_GetAccessToken();
}

void OculusPlatformCore::processGetUserToken(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    response["user_token"] = ovr_Message_GetString(message);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    response["error"] = ovr_Error_GetMessage(error);
  }
  ALOGV("user token signal ");
  emit_signal("get_user_token_done", response);
}

void OculusPlatformCore::generateUserProof()
{
  ALOGV("\nTrying to generate a user nonce\n");

  ovrRequest req;

  req = ovr_User_GetUserProof();
}

void OculusPlatformCore::processGenerateUserProof(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ovrUserProofHandle proof = ovr_Message_GetUserProof(message);
    response["user_proof"] = ovr_UserProof_GetNonce(proof);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    response["error"] = ovr_Error_GetMessage(error);
  }
  ALOGV("user proof signal ");
  emit_signal("get_user_proof_done", response);
}

#pragma endregion

// Leaderboard Functions
#pragma region leaderboard functions
void OculusPlatformCore::writeLeaderboardEntry(String leaderboardName, String value, String extraData = "", bool forceUpdate = false)
{
  ALOGV("\nTrying to write leaderboard entry to  %s\n", leaderboardName.alloc_c_string());
  const char *extradata = extraData.alloc_c_string();
  ovrRequest req;

  req = ovr_Leaderboard_WriteEntry(
      leaderboardName.alloc_c_string(), std::strtoull(value.alloc_c_string(), NULL, 10), extradata, sizeof(extraData.alloc_c_string()), forceUpdate);
}

void OculusPlatformCore::processWriteLeaderboardEntry(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = false;
  if (ovr_Message_IsError(message))
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    response["error"] = ovr_Error_GetMessage(error);
  }
  else
  {
    ovrLeaderboardUpdateStatusHandle updateResult = ovr_Message_GetLeaderboardUpdateStatus(message);
    if (!ovr_LeaderboardUpdateStatus_GetDidUpdate(updateResult))
    {
      response["error"] = "Leaderboard NOT updated as per constraints";
    }
    else
    {
      response["success"] = true;
    }
  }
  emit_signal("submit_score_to_leaderboard_done", response);
}

void OculusPlatformCore::getLeaderboardEntries(String leaderboardName, int limit)
{
  ALOGV("Trying to get leaderboard entries for  %s\n", leaderboardName.alloc_c_string());
  ovrRequest req;
  req = ovr_Leaderboard_GetEntries(
      leaderboardName.alloc_c_string(),
      limit,
      ovrLeaderboard_FilterNone, // need to implement this for some reason default arguements didnt work
      ovrLeaderboard_StartAtTop);
}

void OculusPlatformCore::processGetLeaderboardEntries(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ovrLeaderboardEntryArrayHandle results = ovr_Message_GetLeaderboardEntryArray(message);

    unsigned long long totalRows = ovr_LeaderboardEntryArray_GetTotalCount(results);
    Array leaderboardvalues;
    size_t count = ovr_LeaderboardEntryArray_GetSize(results);

    ALOGV("Total Rows in Leaderboard: %llu\n", totalRows);
    for (size_t x = 0; x < count; x++)
    {

      ovrLeaderboardEntryHandle entry = ovr_LeaderboardEntryArray_GetElement(results, x);
      ovrUserHandle user = ovr_LeaderboardEntry_GetUser(entry);
      long long score = ovr_LeaderboardEntry_GetScore(entry);
      unsigned int ranking = ovr_LeaderboardEntry_GetRank(entry);
      const char *extraData = ovr_LeaderboardEntry_GetExtraData(entry);
      unsigned long long timestamp = ovr_LeaderboardEntry_GetTimestamp(entry);
      Dictionary boardrow;

      boardrow["rank"] = int(ranking);
      boardrow["oculus_user_id"] = ovr_User_GetOculusID(user);
      boardrow["display_name"] = ovr_User_GetDisplayName(user);
      boardrow["score"] = int(score);
      boardrow["extra_data"] = extraData;
      boardrow["timestamp"] = int(timestamp);

      leaderboardvalues.append(boardrow);
    }
    response["leaderboard_rows"] = leaderboardvalues;
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("get_score_from_leaderboard_done", response);
}

#pragma endregion

// Room functions
#pragma region room functions
// Room join modes are
// NONE EVERYONE FRIENDS_OF_MEMBERS FRIENDS_OF_OWNER INVITED_USERS
void OculusPlatformCore::createAndJoinPrivateRoom(String joinType, unsigned int maxUsers, bool subscribetoupdates)
{ 
  ovrRoomJoinPolicy join_type = ovrRoomJoinPolicy_FromString(joinType.alloc_c_string());
  ALOGV("\nTrying to get create and join private room %d\n",join_type);
  ovrRequest req;

  req = ovr_Room_CreateAndJoinPrivate(join_type, maxUsers, subscribetoupdates);
}

void OculusPlatformCore::processCreateAndJoinPrivateRoom(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Created and joined private room\n");
    ovrRoomHandle room = ovr_Message_GetRoom(message);
    outputRoomDetails(room, response);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Error creating private room: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("create_and_join_private_room_done", response);
}

void OculusPlatformCore::getCurrentRoom()
{
  ALOGV("\nTrying to get current room\n");

  ovrRequest req;

  req = ovr_Room_GetCurrent();
}

void OculusPlatformCore::processGetCurrentRoom(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received get current room success\n");

    ovrRoomHandle room = ovr_Message_GetRoom(message);
    outputRoomDetails(room, response);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received get room failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("get_current_room_done", response);
}

void OculusPlatformCore::getRoom(String roomID)
{
  ovrID room_id = std::strtoull(roomID.alloc_c_string(), NULL, 10);
  ALOGV("\nTrying to get room %llu\n", room_id);

  ovrRequest req;

  req = ovr_Room_Get(room_id);
}

void OculusPlatformCore::processGetRoom(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received get room success\n");

    ovrRoomHandle room = ovr_Message_GetRoom(message);
    outputRoomDetails(room, response);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received get room failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("", response);
}

void OculusPlatformCore::leaveRoom(String roomID)
{
  ovrID room_id = std::strtoull(roomID.alloc_c_string(), NULL, 10);

  ALOGV("\nTrying to leave room %llu\n", room_id);

  ovrRequest req;

  req = ovr_Room_Leave(room_id);
}

void OculusPlatformCore::processLeaveRoom(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received leave room success\n");

    ovrRoomHandle room = ovr_Message_GetRoom(message);
    outputRoomDetails(room, response);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received leave room failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("leave_room_done", response);
}

void OculusPlatformCore::joinRoom(String roomID)
{
  ovrID room_id = std::strtoull(roomID.alloc_c_string(), NULL, 10);
  ALOGV("\nTrying to join room %llu\n", room_id);

  ovrRequest req;

  req = ovr_Room_Join(room_id, true);
}

void OculusPlatformCore::processJoinRoom(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received join room success\n");

    ovrRoomHandle room = ovr_Message_GetRoom(message);
    outputRoomDetails(room, response);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received get room failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("join_room_done", response);
}

void OculusPlatformCore::kickUser(String roomID, String userID, int kickduration)
{
  ovrID room_id = std::strtoull(roomID.alloc_c_string(), NULL, 10);
  ovrID user_id = std::strtoull(userID.alloc_c_string(), NULL, 10);
  ALOGV("\nTrying to get kick user %llu from room %llu\n", user_id, room_id);

  ovrRequest req;

  req = ovr_Room_KickUser(room_id, user_id, kickduration /*kickDurationSeconds*/);
}

void OculusPlatformCore::processKickUser(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received kick user success\n");

    ovrRoomHandle room = ovr_Message_GetRoom(message);
    outputRoomDetails(room, response);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received kick user failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("kick_user_done", response);
}

void OculusPlatformCore::getInvitableUsers()
{
  ALOGV("\nTrying to get invitable users\n");

  ovrRequest req;

  req = ovr_Room_GetInvitableUsers();
}

void OculusPlatformCore::processGetInvitableUsers(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received get invitable users success\n");

    ovrUserArrayHandle users = ovr_Message_GetUserArray(message);
    generateUserArray(users, response);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received get invitable users failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("get_invitable_users_done", response);
}

void OculusPlatformCore::inviteUser(String roomID, String inviteToken)
{
  ovrID room_id = std::strtoull(roomID.alloc_c_string(), NULL, 10);
  ALOGV("\nTrying to get invite token %s to room %llu\n", inviteToken.alloc_c_string(), room_id);

  ovrRequest req;

  req = ovr_Room_InviteUser(room_id, inviteToken.alloc_c_string());
}

void OculusPlatformCore::processInviteUser(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received invite user success\n");

    ovrRoomHandle room = ovr_Message_GetRoom(message);
    outputRoomDetails(room, response);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received invite user failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("invite_user_done", response);
}

void OculusPlatformCore::setRoomDescription(String roomID, String description)
{
  ovrID room_id = std::strtoull(roomID.alloc_c_string(), NULL, 10);
  ALOGV("\nTrying to set description of room %llu to %s\n", room_id, description.alloc_c_string());

  ovrRequest req;

  req = ovr_Room_SetDescription(room_id, description.alloc_c_string());
}

void OculusPlatformCore::processSetRoomDescription(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received set description success\n");

    ovrRoomHandle room = ovr_Message_GetRoom(message);
    outputRoomDetails(room, response);
    ovrUserArrayHandle users = ovr_Room_GetUsers(room);
    generateUserArray(users, response);
  }
  else
  {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    ALOGV("Received set description failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("set_room_description_done", response);
}

// send null value with key to remove key
void OculusPlatformCore::updateRoomDataStore(String roomID, String key, String value) {
  
  ovrID room_id = std::strtoull(roomID.alloc_c_string(), NULL, 10);
  printf("\nTrying to update data store for room %llu\n", room_id);
  ovrRequest req;

  ovrKeyValuePair newKVPair;
  newKVPair.key = key.alloc_c_string();
  newKVPair.valueType = ovrKeyValuePairType_String;
  newKVPair.stringValue = value.alloc_c_string();

  req = ovr_Room_UpdateDataStore(room_id, &newKVPair, 1);
}

void OculusPlatformCore::processUpdateRoomDataStore(ovrMessageHandle message) {
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if(response["success"]){
    printf("Received update data store success\n");
    ovrRoomHandle room = ovr_Message_GetRoom(message);
    outputRoomDetails(room,response);
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received update room data failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("update_room_datastore_done", response);
}

void OculusPlatformCore::processRoomUpdate(ovrMessageHandle message) {
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if(response["success"]){
    printf("Received room update Notification\n");
    ovrRoomHandle room = ovr_Message_GetRoom(message);
    outputRoomDetails(room, response);
  } else {
    const ovrErrorHandle error = ovr_Message_GetError(message);
    printf("Received room update failure: %s\n", ovr_Error_GetMessage(error));
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("room_update_done", response);
}

void OculusPlatformCore::outputRoomDetails(ovrRoomHandle room, Dictionary &response)
{
  Dictionary _roomdetails;

  _roomdetails["room_id"] = String::num_int64(ovr_Room_GetID(room));
  _roomdetails["room_app_id"] = String::num_int64(ovr_Room_GetApplicationID(room));
  _roomdetails["room_description"] = ovr_Room_GetDescription(room);
  response["room_details"] = _roomdetails;

  size_t maxUsers = ovr_Room_GetMaxUsers(room);
  
  response["max_users"] = int(maxUsers);

  ovrUserHandle owner = ovr_Room_GetOwner(room);

  Dictionary _owner;
  
  _owner["user_id"] = String::num_int64(ovr_User_GetID(owner));
  _owner["oculus_id"] = ovr_User_GetOculusID(owner);
  response["owner"] = _owner;
  response["join_policy"] = ovrRoomJoinPolicy_ToString(ovr_Room_GetJoinPolicy(room));
  response["room_type"] = ovrRoomType_ToString(ovr_Room_GetType(room));

  Dictionary _datastore_dict;

  ovrDataStoreHandle dataStore = ovr_Room_GetDataStore(room);
  size_t count = ovr_DataStore_GetNumKeys(dataStore);
  for (size_t x = 0; x < count; x++)
  {
    const char *key = ovr_DataStore_GetKey(dataStore, x);
    _datastore_dict[key] = ovr_DataStore_GetValue(dataStore, key);
  }
  response["datastore"] = _datastore_dict;
}

#pragma endregion

// Cloud Functions
#pragma region Cloud Functions
// Note the functions below are not implemented for andriod by the sdk itself , they only work in windows mode

// IMPORTANT NOTE:
// ovr_CloudStorage_Save is only passing in a pointer to your data in an async call.  Your data
// will need to stay alive and unmodified until you receive a ovrMessage_CloudStorage_Save message
// indicating that the save was successful.  If the data is destroyed or modified prior to
// receiving that message there's a good chance the proper data won't be saved.
void OculusPlatformCore::writeCloudData(const String cloud_bucket, const String cloud_key, const Dictionary data, String extra, int counter = 0)
{
  ALOGV("\nSaving cloud data.\n");
  ovrRequest req;
  req = ovr_CloudStorage_Save(cloud_bucket.alloc_c_string(), cloud_key.alloc_c_string(), &data, sizeof(data), counter, extra.alloc_c_string());
}

void OculusPlatformCore::processCloudStorageSave(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (!response["success"])
  {
    ALOGV("Could NOT save cloud data\n");
    ovrErrorHandle error = ovr_Message_GetError(message);
    response["error_code"] = ovr_Error_GetCode(error);
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("write_cloud_data_done", response);
}

void OculusPlatformCore::getCloudData(const String cloud_bucket, const String cloud_key)
{
  ALOGV("\nLoading cloud data.\n");

  ovrRequest req;

  req = ovr_CloudStorage_Load(cloud_bucket.alloc_c_string(), cloud_key.alloc_c_string());
}

void OculusPlatformCore::processCloudStorageLoad(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Cloud data was loaded!\n");
    ovrCloudStorageDataHandle _response = ovr_Message_GetCloudStorageData(message);
    const void *data = ovr_CloudStorageData_GetData(_response);
    unsigned int data_size = ovr_CloudStorageData_GetDataSize(_response);
    const Dictionary *loaded_data = static_cast<const Dictionary *>(data);
    response["data"] = loaded_data;
  }
  else
  {
    ALOGV("Could NOT load cloud data\n");
    ovrErrorHandle error = ovr_Message_GetError(message);
    response["error_code"] = ovr_Error_GetCode(error);
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("get_cloud_data_done", response);
}

void OculusPlatformCore::deleteCloudData(const String cloud_bucket, const String cloud_key)
{
  ALOGV("\nDeleting cloud data.\n");

  ovrRequest req;

  req = ovr_CloudStorage_Delete(cloud_bucket.alloc_c_string(), cloud_key.alloc_c_string());
}

void OculusPlatformCore::processCloudStorageDelete(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (!response["success"])
  {
    ovrErrorHandle error = ovr_Message_GetError(message);
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("delete_cloud_data_done", response);
}

void OculusPlatformCore::getCloudMetaData(const String cloud_bucket)
{
  ALOGV("\nLoading Cloud metadata\n");

  ovrRequest req;
  req = ovr_CloudStorage_LoadBucketMetadata(cloud_bucket.alloc_c_string());
}

void OculusPlatformCore::processCloudMetaData(ovrMessageHandle message)
{
  Dictionary response;
  response["success"] = !ovr_Message_IsError(message);
  if (response["success"])
  {
    ALOGV("Received the following cloud metadata:\n");

    ovrCloudStorageMetadataArrayHandle metaDataArray =
        ovr_Message_GetCloudStorageMetadataArray(message);

    size_t numElements = ovr_CloudStorageMetadataArray_GetSize(metaDataArray);

    for (size_t x = 0; x < numElements; x++)
    {
      ovrCloudStorageMetadataHandle metaDataHandle =
          ovr_CloudStorageMetadataArray_GetElement(metaDataArray, x);

      unsigned int data_size = ovr_CloudStorageMetadata_GetDataSize(metaDataHandle);
      double saved_time = ovr_CloudStorageMetadata_GetSaveTime(metaDataHandle);
      ovrCloudStorageDataStatus status = ovr_CloudStorageMetadata_GetStatus(metaDataHandle);
      const char *extraData = ovr_CloudStorageMetadata_GetExtraData(metaDataHandle);
      int counter = ovr_CloudStorageMetadata_GetCounter(metaDataHandle);
      String message = ovrCloudStorageDataStatus_ToString(status);
      Dictionary cloudmetadata;
      cloudmetadata["data_size"] = data_size;
      cloudmetadata["saved_time"] = saved_time;
      cloudmetadata["counter"] = counter;
      cloudmetadata["extraData"] = counter;
      cloudmetadata["status"] = message;
      response["cloudmetadata"] = cloudmetadata;
    }
  }
  else
  {
    ALOGV("Could NOT get cloud metadata\n");
    ovrErrorHandle error = ovr_Message_GetError(message);
    response["error"] = ovr_Error_GetMessage(error);
  }
  emit_signal("get_cloud_meta_data_done", response);
}

#pragma endregion