#Attention: Work in progress. Does not work yet

# Oculus Platform Godot plugin

## License

- This project is released under the MIT license.
- Please check the [Oculus Mobile SDK license](https://developer.oculus.com/licenses) for information
about the Oculus Mobile SDK used in this project.

## Getting the plugin

### Deployment

#### Oculus Platform SDK
- Download the [latest version](https://developer.oculus.com/downloads/package/oculus-platform-sdk/)
and extract it to `plugin/libs/ovr_platform_sdk` directory (create the directory if it doesn't exist).

#### Godot libraries
- Checkout the [godot-cpp](https://github.com/GodotNativeTools/godot-cpp) repo as a submodule by running the following command: `git submodule update --init --recursive`.
  - The [godot-cpp](https://github.com/GodotNativeTools/godot-cpp) repo will checkout under the `plugin/libs/godot-cpp` directory.
  - Make sure that all you checkout the correct tags of the correct branch for all submodules. For example to develop for Godot 3.4.1 you would do `git ceckout tags/godot-3.4.1-stable -b 3.4` in all included submodules
- Navigate to the `plugin/libs/godot-cpp` directory and follow [these steps](https://github.com/GodotNativeTools/godot-cpp/tree/master#compiling-the-cpp-bindings-library) to generate the cpp bindings.

#### Android SDK & NDK
- Download and setup
  [Android Studio version **4.2** or higher](https://developer.android.com/studio).
  - After setup, ensure you have the latest versions by checking the [SDK Manager](https://developer.android.com/studio/intro/update.html#sdk-manager) for updates.
- Set the environment variable `ANDROID_HOME` to the Android SDK location.
- Make sure you have the NDK version 21.4.7075529 installed and are using it for that build. Why? Because a command is either missing or in some other location in newer versions breaking the compilation. This may not be necessary for newer godot versions

### Build

#### Generate plugin binary files
In the project root directory:
 - Run `./gradlew :generatePluginBinary` to generate the plugin binary files.
 - Once the build successfully completes, the binary files can be found in the `build/outputs/pluginBin` directory.

