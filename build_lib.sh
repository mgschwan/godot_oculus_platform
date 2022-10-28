#/bin/bash
source ~/.bash_profile
./gradlew :generatePluginBinary
mv /Users/rahulghosh/godot_projects/Github/godot_oculus_platform/plugin/build/outputs/aar/gdovrplatform.3.3.0-full-release.aar /Users/rahulghosh/godot_projects/Github/godot_oculus_platform/demo/OculusPlatformTest/android/plugins/gdovrplatform.3.3.0-full-release.aar
