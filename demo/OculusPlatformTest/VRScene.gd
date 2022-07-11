extends Spatial


# Declare member variables here. Examples:
# var a = 2
# var b = "text"


var vr_interface

func init_vr():
	var available_interfaces = ARVRServer.get_interfaces();
	for interface in available_interfaces:
		match interface.name:
			"OpenXR":
				vr_interface = ARVRServer.find_interface("OpenXR");

	if vr_interface:
		if vr_interface.initialize():
			get_viewport().arvr = true;
			get_viewport().keep_3d_linear = false	
			Engine.target_fps = 72
			OS.vsync_enabled = false
			#ARVRServer.connect("openxr_pose_recentered", self, "on_recenter_scene")


# Called when the node enters the scene tree for the first time.
func _ready():
	init_vr()
