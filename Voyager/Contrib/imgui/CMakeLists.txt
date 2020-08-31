cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

project(imgui C CXX)

set(SOURCE_FILES 
	imconfig.h
	imgui.cpp
	imgui.h
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_internal.h
	imgui_widgets.cpp
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
	"IMGUI_API=__declspec(dllexport);"
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR};"
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
