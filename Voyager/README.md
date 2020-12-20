# Voyager Module

The Voyager module is the heart of the engine.

## Build Macros

## Contribs
Third-party libraries and custom libraries are placed under the "Contribs" folder.

Remember to set environment variable "CONTRIBS_PATH" according to your preferred location on the system. 

A "Contrib" normally has the following folder structure:

 - bin
 - include
 - lib
 - src

The following format can be used in a project's CMakeLists.txt to target a library:
- `bin/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}`
- `lib/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}`

## List of third-party libraries
These are the third-party libraries currently used in the project:
 - GLFW
 - Glad
 - spdlog
 - dear ImGui
 
 Voyager ships with ready to use CMake projects for each library, but the user is required to clone or download the repository themselves. It is also possible to remove the CMake projects and add them as git submodules instead.
