extends Control

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
		$OculusPlatformCore.initEntitlement("org.godotengine.oculusplatformtest")
		print ("We at least did not crash")
		
		$Debug.text += "\nWe at least did not crash"
		print("checking entitlement")
		$OculusPlatformCore.connect("entitlement_check", self, "_on_entitlement_check")
		$OculusPlatformCore.checkEntitlement()
		
	else:
		$GridContainer/Status.text = "not available"
		$Debug.text += "\nNot available on this platform"

func _on_entitlement_check(success):
	print("succesful entiltemnt_check , success = " ,success)
