extends Control

export(String)  var APP_ID = "5593167750762370" # use your own 
export(String)  var CLOUD_BUCKET = "testbucket"
export(String)  var CLOUD_KEY = "testkey"

var ACHIEVEMENT_NAME = "Test_Achievement"
var _leaderboardname = "test_board"
var native_module

const sample_data:String  = "Rahul Ghosh is storing some data here"
# Called when the node enters the scene tree for the first time.
func _ready():	
	print ("Checking for OVRPlatform plugin")
	$Debug.text += "Checking for OVRPlatform plugin"
	if Engine.has_singleton("OVRPlatform"):
		native_module = Engine.get_singleton("OVRPlatform")
		$GridContainer/Status.text = "initialized"	
		$Debug.text += "\nSeems to be available"
		print("connecting")
		$OculusPlatformCore.connect("platform_initialized", self, "_on_PlatformInitialized")
		print("platform setup done")
		$OculusPlatformCore.connect("get_entitlement_check_done", self, "_on_EntitlementCheckDone")
		print("entitlement setup done")
		$OculusPlatformCore.connect("get_logged_in_user_done", self, "_on_getLoggedInUserDone")
		$OculusPlatformCore.connect("get_user_done", self, "_on_getUserDone")
		$OculusPlatformCore.connect("get_user_token_done", self, "_on_getUserTokenDone")
		$OculusPlatformCore.connect("get_user_proof_done", self, "_on_getUserProofDone")
		$OculusPlatformCore.connect("get_user_friends_done", self, "_on_getUserFriendsDone")
		print("user setup done")
		$OculusPlatformCore.connect("write_cloud_data_done", self, "_on_writeCloudDataDone")
		$OculusPlatformCore.connect("get_cloud_meta_data_done", self, "_on_getCloudMetaDataDone")
		$OculusPlatformCore.connect("get_cloud_data_done", self, "_on_getCloudDataDone")
		$OculusPlatformCore.connect("delete_cloud_data_done", self, "_on_deleteCloudDataDone")
		print("Cloud setup done")
		$OculusPlatformCore.connect("submit_score_to_leaderboard_done", self, "_on_submitScoreToLeaderboardDone")
		$OculusPlatformCore.connect("get_score_from_leaderboard_done", self, "_on_get_scoreFromLeaderboardDone")
		print("leaderboard setup done")
		$OculusPlatformCore.connect("create_and_join_private_room_done",self,"_on_createAndJoinPrivateRoomDone")
		$OculusPlatformCore.connect("get_current_room_done",self,"_on_getCurrentRoomDone")
		$OculusPlatformCore.connect("leave_room_done",self,"_on_leaveRoomDone")
		$OculusPlatformCore.connect("join_room_done",self,"_on_joinRoomDone")
		$OculusPlatformCore.connect("get_invitable_users_done",self,"_on_getInvitableUsersDone")
		$OculusPlatformCore.connect("set_room_description_done",self,"_on_setRoomDescriptionDone")
		$OculusPlatformCore.connect("update_room_datastore_done",self,"_on_updateRoomDatastoreDone")
		$OculusPlatformCore.connect("room_update_done",self,"_on_roomUpdateDone")
		print("room setup done")
		$OculusPlatformCore.connect("get_all_achievement_definition",self,"_on_getAllAchievementDefinitionDone")
		$OculusPlatformCore.connect("get_all_achievement_progress",self,"_on_getAllAchievementProgressDone")
		$OculusPlatformCore.connect("get_achievement_definition",self,"_on_getAchievementDefinitionDone")
		$OculusPlatformCore.connect("get_achievement_progress",self,"_on_getAchievementProgressDone")
		$OculusPlatformCore.connect("unlock_achievement",self,"_on_unlockAchievementDone")
		$OculusPlatformCore.connect("add_achievement_count",self,"_on_addAchievementCountDone")
		$OculusPlatformCore.connect("add_achievement_bitfield",self,"_on_addAchievementBitfieldDone")
		print("achievement setup done")
		print ("initializing")
		$OculusPlatformCore.initialize(APP_ID)
	else:
		$GridContainer/Status.text = "not available"
		$Debug.text += "\nNot available on this platform"

var values  = [["40","best"]]
func test_leaderboard():
	for i in values:
		$OculusPlatformCore.submitScoreToLeaderboard(_leaderboardname,i[0],i[1])
		
func _on_PlatformInitialized(response):
	print(response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	$Debug.text += "\nTry to get entitlement"
	print ("Try to get entitlement")
	$OculusPlatformCore.checkEntitlement()
		
func _on_EntitlementCheckDone(response):
	print(response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	print ("trying to get user")
	$OculusPlatformCore.getLoggedInUser()

func _on_getUserDone(response):
	print("get user response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return

func _on_getLoggedInUserDone(response):
	print("login user response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	var uid =  response["user_id"]
	#$OculusPlatformCore.getUser(uid)
	#$OculusPlatformCore.getUserToken()
	#$OculusPlatformCore.getUserProof()
	#$OculusPlatformCore.getScoreFromLeaderboard(_leaderboardname,10)
	#$OculusPlatformCore.getLoggedInUserFriends()
	#test_leaderboard()
	#$OculusPlatformCore.writeCloudData(CLOUD_BUCKET,CLOUD_KEY	,sample_data,"Testdata")
	#$OculusPlatformCore.createAndJoinPrivateRoom("NONE",2,true)
	$OculusPlatformCore.addAchievementCount(ACHIEVEMENT_NAME,"3")
	
#NONE EVERYONE FRIENDS_OF_MEMBERS FRIENDS_OF_OWNER INVITED_USERS
func _on_getAllAchievementDefinitionDone(response):
	print("all Achievement ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	$OculusPlatformCore.getAllAchievementProgress()
	
func _on_getAllAchievementProgressDone(response):
	print("all Achievement progress ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	print("unlocking count achievement by adding 8 points")
	$OculusPlatformCore.addAchievementCount(ACHIEVEMENT_NAME,"8")

func _on_getAchievementDefinitionDone(response):
	print("Achievement ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	
func _on_getAchievementProgressDone(response):
	print("Achievement progress ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
		
func _on_unlockAchievementDone(response):
	print("Achievement unlock response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
		
func _on_addAchievementCountDone(response):
	print("Achievement count response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	$OculusPlatformCore.getAllAchievementDefinition()
	
func _on_addAchievementBitfieldDone(response):
	print("Achievement Bitfield response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return

var ROOMID:String 

func _on_createAndJoinPrivateRoomDone(response):
	print("create room response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	ROOMID = response["room_details"]["room_id"]
	print("room id is ",ROOMID)
	$OculusPlatformCore.setRoomDescription(ROOMID,"Testroom")
	$OculusPlatformCore.updateRoomDatastore(ROOMID,"Testkey","Testvalue")
	$OculusPlatformCore.joinRoom(ROOMID)

func _on_updateRoomDatastoreDone(response):
	print("set room description response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return

func _on_roomUpdateDone(response):
	print("set room update response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return

func _on_setRoomDescriptionDone(response):
	print("set room description response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return

func _on_joinRoomDone(response):
	print("join room response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return 
	$OculusPlatformCore.getCurrentRoom()
	$OculusPlatformCore.getInvitableUsers()

func _on_getCurrentRoomDone(response):
	print("get room response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	
func _on_getInvitableUsersDone(response):
	print("get invitable users response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	$OculusPlatformCore.leaveRoom(ROOMID)
	
func _on_leaveRoomDone(response):
	print("get leave room response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	$OculusPlatformCore.getCurrentRoom()

func _on_getUserTokenDone(response):
	print(response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	
func _on_getUserProofDone(response):
	print(response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	
func _on_getUserFriendsDone(response):
	print("friends respone: ", response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	# not implemented yet
var total_rows = 0

func _on_submitScoreToLeaderboardDone(response):
	print(response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	total_rows +=1
	print("final rows entered = ",total_rows)
	if total_rows == len(values):
		pass

func _on_get_scoreFromLeaderboardDone(response):
	print(response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return


# cloud functions ( dont work , bcz functions in sdk not implemented for android )
func _on_writeCloudDataDone(response):
	print(response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	print("save was successful")
	
	$OculusPlatformCore.getCloudMetaData(CLOUD_BUCKET)
	
func _on_getCloudMetaDataDone(response):
	print(response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	print("get metadata was successful")
	
	$OculusPlatformCore.getCloudData(CLOUD_BUCKET,CLOUD_KEY)
	
func _on_getCloudDataDone(response):
	print(response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return

	$OculusPlatformCore.deleteCloudData(CLOUD_BUCKET,CLOUD_KEY)

func _on_deleteCloudDataDone(response):
	print(response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	print("delete successful")
