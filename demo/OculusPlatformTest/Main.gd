extends Control

export(String)  var APP_ID = "5593167750762370" # use your own 
export(String)  var CLOUD_BUCKET = "testbucket"
export(String)  var CLOUD_KEY = "testkey"

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
		$OculusPlatformCore.connect("create_and_join_private_room_done",self,"_on_create_and_join_private_room_done")
		$OculusPlatformCore.connect("get_current_room_done",self,"_on_get_current_room_done")
		$OculusPlatformCore.connect("leave_room_done",self,"_on_leave_room_done")
		$OculusPlatformCore.connect("join_room_done",self,"_on_join_room_done")
		$OculusPlatformCore.connect("kick_user_done",self,"_on_kick_user_done")
		$OculusPlatformCore.connect("get_invitable_users_done",self,"_on_get_invitable_users_done")
		$OculusPlatformCore.connect("invite_user_done",self,"_on_invite_user_done")
		$OculusPlatformCore.connect("set_room_description_done",self,"_on_set_room_description_done")
		print("room setup done")
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
	

func _on_getLoggedInUserDone(response):
	print("login user response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	var uid =  response["user_id"]
	$OculusPlatformCore.getUser(uid)
	#$OculusPlatformCore.getUserToken()
	#$OculusPlatformCore.getUserProof()
	#$OculusPlatformCore.getScoreFromLeaderboard(_leaderboardname,10)
	#$OculusPlatformCore.getLoggedInUserFriends()
	#test_leaderboard()
	#$OculusPlatformCore.writeCloudData(CLOUD_BUCKET,CLOUD_KEY	,sample_data,"Testdata")

func _on_getUserDone(response):
	print("get user response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return
	$OculusPlatformCore.getLoggedInUserFriends()
	
func _on_create_and_join_private_room_done(response):
	print("get user response ",response)
	if not response["success"]: 
		print("error :" ,response["error"]) 
		return

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
