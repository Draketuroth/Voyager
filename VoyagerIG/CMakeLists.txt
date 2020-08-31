project(VoyagerIG C CXX)

################################################################################
# Source groups
################################################################################
set(VoyagerIG_Folder_Config
	Config/Shadersets.json
	Config/Views.json

)
source_group("VoyagerIG\\Config" FILES ${VoyagerIG_Folder_Config})

set(VoyagerIG_Folder
	Source/VoyagerIG/VoyagerIG.cpp
	Source/VoyagerIG/VoyagerIG.h
	Source/VoyagerIG/Scene.cpp
	Source/VoyagerIG/Scene.h
)
source_group("VoyagerIG\\Source" FILES ${VoyagerIG_Folder})

set(VoyagerIG_Folder_Layers
	Source/VoyagerIG/Layers/RenderLayer.h
	Source/VoyagerIG/Layers/RenderLayer.cpp
	Source/VoyagerIG/Layers/ResourceLayer.h
	Source/VoyagerIG/Layers/ResourceLayer.cpp
	Source/VoyagerIG/Layers/SceneLayer.h
	Source/VoyagerIG/Layers/SceneLayer.cpp
)
source_group("VoyagerIG\\Source\\Layers" FILES ${VoyagerIG_Folder_Layers})

set(VoyagerIG_Folder_Systems
	Source/VoyagerIG/Systems/RenderSystem.h
	Source/VoyagerIG/Systems/RenderSystem.cpp
)
source_group("VoyagerIG\\Source\\Systems" FILES ${VoyagerIG_Folder_Systems})

set(ALL_FILES
    ${VoyagerIG_Folder}
	${VoyagerIG_Folder_Config}
	${VoyagerIG_Folder_Layers}
	${VoyagerIG_Folder_Systems}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE VoyagerIG)

################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_DEBUG   "${PROJECT_NAME}d"
	TARGET_NAME_RELEASE "${PROJECT_NAME}"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_DIRECTORY_DEBUG   "Build/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/"
    OUTPUT_DIRECTORY_RELEASE "Build/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR};"
	"${CMAKE_SOURCE_DIR}/VoyagerIG/Source;"
	"${CMAKE_SOURCE_DIR}/Voyager/Source;"
	"${CMAKE_SOURCE_DIR}/Voyager/Contrib/spdlog/include;"
	"${CMAKE_SOURCE_DIR}/Voyager/Contrib/glad/include;"
	"${CMAKE_SOURCE_DIR}/Voyager/Contrib/imgui;"
	"${CMAKE_SOURCE_DIR}/Voyager/Contrib/stb;"
    "${CMAKE_CURRENT_SOURCE_DIR};"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "VE_PLATFORM_WINDOWS;"
	"VE_DEBUG;"
	"IMGUI_API=__declspec(dllimport);"
    "_MBCS"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:
            /Od;
			/MDd
        >
        $<$<CONFIG:Release>:
            /GL;
            /O2;
            /Oi;
            /MD;
            /Gy
        >
        /permissive-;
        /std:c++17;
        /sdl;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        ${DEFAULT_CXX_EXCEPTION_HANDLING}
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:
            /LTCG;
            /OPT:REF;
            /OPT:ICF
        >
        /DEBUG:FULL
    )
endif()

add_custom_command(
	TARGET ${PROJECT_NAME} 
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/../Contrib/voyager/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/$<IF:$<CONFIG:Debug>,Voyagerd.dll,Voyager.dll>" $<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Resources/Shaders/" $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Resources/Textures/" $<TARGET_FILE_DIR:${PROJECT_NAME}>/Textures
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/Resources/Models/" $<TARGET_FILE_DIR:${PROJECT_NAME}>/Models
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/Config/" $<TARGET_FILE_DIR:${PROJECT_NAME}>/Config
	
)

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
    Voyager
)

string(CONCAT ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
        "Voyagerd"
    ">"
    "$<$<CONFIG:Release>:"
        "Voyager"
    ">"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}/../Contrib/voyager/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/"
)