extends Control

export(String)  var APP_ID = "5593167750762370"
var native_module

# Called when the node enters the scene tree for the first time.
func _ready():	
	print ("Checking for OVRPlatform plugin")
	$Debug.text += "Checking for OVRPlatform plugin"
	if Engine.has_singleton("OVRPlatform"):
		
		native_module = Engine.get_singleton("OVRPlatform")
		$GridContainer/Status.text = "initialized"	
		$Debug.text += "\nSeems to be available"

		yield(get_tree().create_timer(5), "timeout")
		
		print ("Try to get entitlement")
		$Debug.text += "\nTry to get entitlement"
		$OculusPlatformCore.connect("get_entitlement_check", self, "_on_entitlement_check")
		$OculusPlatformCore.initEntitlement(APP_ID)
		print ("We at least did not crash")
		
		$Debug.text += "\nWe at least did not crash"
		print ("trying to get user")
		$OculusPlatformCore.connect("get_logged_in_user", self, "_on_get_logged_in_user")
		$OculusPlatformCore.getLoggedInUser()
	else:
		$GridContainer/Status.text = "not available"
		$Debug.text += "\nNot available on this platform"

func _on_entitlement_check(success):
	print("successful entiltemnt_check , success = " ,success)
	
func _on_get_logged_in_user(success,userid,oculus_user_id):
	print("successful get_user , success = " ,success,  "user_id = ", userid  , "oculus_user_id = ", oculus_user_id )
