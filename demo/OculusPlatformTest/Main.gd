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
		print ("initializing")
		$OculusPlatformCore.initialize(APP_ID)
	else:
		$GridContainer/Status.text = "not available"
		$Debug.text += "\nNot available on this platform"

var values  = [["10","worst"],["30","middle"],["40","best"]]
func test_leaderboard():
	for i in values:
		$OculusPlatformCore.submitScoreToLeaderboard(_leaderboardname,i[0],i[1])
		
func _on_PlatformInitialized(success,message):
	print("signal inititlaized")
	if not success: 
		print("error :" ,message) 
		return
	$Debug.text += "\nTry to get entitlement"
	print ("Try to get entitlement")
	$OculusPlatformCore.checkEntitlement()
		
func _on_EntitlementCheckDone(success):
	print("signal entitlement")
	if not success: 
		return
	print("successful entiltemnt_check , success = " ,success)
	print ("trying to get user")
	$OculusPlatformCore.getLoggedInUser()
	
	
		
func _on_getLoggedInUserDone(success,userid,oculus_user_id):
	print("successful get_user , success = " ,success,  " user_id = ", userid  , " oculus_user_id = ", oculus_user_id )
	$OculusPlatformCore.getUserToken()
	$OculusPlatformCore.getUserProof()
	$OculusPlatformCore.getScoreFromLeaderboard(_leaderboardname)
	$OculusPlatformCore.getLoggedInUserFriends()
	#test_leaderboard()
	#$OculusPlatformCore.writeCloudData(CLOUD_BUCKET,CLOUD_KEY,sample_data,"Testdata")

func _on_getUserTokenDone(success,message):
	if not success:
		print("get User Token fail , error:",message)
		return
	print("user token is ",message)
	
func _on_getUserProofDone(success,message):
	if not success:
		print("get User Proof fail, error:",message)
		return
	print("user proof is ",message)
	
func _on_getUserFriendsDone(success,friends_array):
	if not success:
		print("get User friends fail")
		return
	# not implemented yet

var total_rows = 0

func _on_submitScoreToLeaderboardDone(success):
	if not success:
		print("leaderboard entry fail")
		return
	total_rows +=1
	print("final rows entered = ",total_rows)
	if total_rows == len(values):
		pass

func _on_get_scoreFromLeaderboardDone(success,leaderboard_rows):
	print("score retrive signal")
	if not success:
		print("leaderboard retrival fail")
		return 
	
	print(leaderboard_rows)





# cloud functions ( dont work , bcz functions in sdk not implemented for android )




func _on_writeCloudDataDone(success):
	if not success:
		print("save unsuccessful")
		return
	print("save was successful")
	
	$OculusPlatformCore.getCloudMetaData(CLOUD_BUCKET)
	
func _on_getCloudMetaDataDone(success,data_size,saved_time,counter,extradata,status):
	if not success:
		print("get Cloud Meta Data unsuccessful")
		return
	print("get metadata was successful")
	print("data size = ",data_size ," saved_time = ",saved_time," counter = ",counter," extradata = ",extradata," status = ",status )
	
	$OculusPlatformCore.getCloudData(CLOUD_BUCKET,CLOUD_KEY)
	
func _on_getCloudDataDone(success,loaded_data):
	if not success:
		print("get Cloud Data unsuccessful")
		return
	print("load succesful , data = ",loaded_data)
	
	$OculusPlatformCore.deleteCloudData(CLOUD_BUCKET,CLOUD_KEY)

func _on_deleteCloudDataDone(success):
	if not success:
		print("delete Cloud Data unsuccessful")
		return
	print("delete successful")
