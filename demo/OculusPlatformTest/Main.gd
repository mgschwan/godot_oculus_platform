extends Control

var native_module
# Called when the node enters the scene tree for the first time.
func _ready():	
	print ("Checking for OVRPlatform plugin")
	if Engine.has_singleton("OVRPlatform"):
		native_module = Engine.get_singleton("OVRPlatform")
		$GridContainer/Status.text = "initialized"
	else:
		$GridContainer/Status.text = "not available"
		

