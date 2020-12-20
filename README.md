# VOYAGER - A 3D Rendering Framework

![alt text](https://draketuroth.files.wordpress.com/2018/09/voyager_logo_cover.jpg)

## Introduction
Voyager is a program suite in development for the purpose of easy framework setup for 3D applications and implementation of rendering techniques. 

## Building the project

 ### Windows
 Note: I have kept a CMakeSettings.json for Visual Studio holding custom configurations set up for quick startup. Feel free to modify for your own configurations.
 
 #### Visual Studio 
	 mkdir build
	 cd build
     cmake -G "Visual Studio 16 2019" -A x64 ..\"path_to_source"\
	 
 #### Ninja
 In order to build with Ninja, the current terminal being used must have the Visual Studio compiler environment setup. 
 
	mkdir build
	cd build
    cmake -G "Ninja" ..\"path_to_source"\
	
	
## Version History

### Dev1 2020: 
* Changed default Window API from Qt to GLFW
* Added ImGui support
* Introduced high-level interfaces for abstract 3D programming

### Prototype 2018
* Intial prototype for default OpenGL backend 
* Custom math library using row major notation
 
 
