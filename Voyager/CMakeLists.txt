project(Voyager C CXX)

################################################################################
# Source groups
################################################################################
set(Voyager_Folder_Source
	Source/Voyager.h
	Source/pch.h
	Source/pch.cpp
)
source_group("Voyager" FILES ${Voyager_Folder_Source})

set(Contrib_Folder_STB
	Contrib/stb/stb_image.h
	Contrib/stb/stb_image.cpp
)
source_group("Contrib\\stb" FILES ${Contrib_Folder_STB})

set (Voyager_Folder_Components
    Source/Voyager/Components/Geometry.h
	Source/Voyager/Components/Material.h
	Source/Voyager/Components/Transform.h
)
source_group("Voyager\\Components" FILES ${Voyager_Folder_Components})

set(Voyager_Folder_Core
    Source/Voyager/Core/Core.h
	Source/Voyager/Core/Application.h
	Source/Voyager/Core/Application.cpp
	Source/Voyager/Core/Layer.h
	Source/Voyager/Core/Layer.cpp
	Source/Voyager/Core/LayerStack.h
	Source/Voyager/Core/LayerStack.cpp
	Source/Voyager/Core/Log.h
	Source/Voyager/Core/Log.cpp
    Source/Voyager/Core/Entrypoint.h
	Source/Voyager/Core/IWindow.cpp
	Source/Voyager/Core/IWindow.h
	Source/Voyager/Core/Input.h
	Source/Voyager/Core/Timestep.h
	Source/Voyager/Core/Timer.h
	Source/Voyager/Core/Timer.cpp
	Source/Voyager/Core/KeyCodes.h
	Source/Voyager/Core/MouseButtonCodes.h
	Source/Voyager/Core/Types.h
	Source/Voyager/Core/System.h
	Source/Voyager/Core/IEntityManager.h
	Source/Voyager/Core/IEntityManager.cpp
	Source/Voyager/Core/Resource.h
	Source/Voyager/Core/ResourceManager.h
	Source/Voyager/Core/EntityManager.h
	Source/Voyager/Core/ComponentArray.h
	Source/Voyager/Core/ComponentManager.h
	Source/Voyager/Core/IComponentManager.h
	Source/Voyager/Core/IComponentManager.cpp
	Source/Voyager/Core/SystemManager.h
	Source/Voyager/Core/ISystemManager.h
	Source/Voyager/Core/ISystemManager.cpp
	Source/Voyager/Core/Bitmask.h
	
)
source_group("Voyager\\Core" FILES ${Voyager_Folder_Core})

set(Voyager_Folder_Event
    Source/Voyager/Event/Event.h
	Source/Voyager/Event/ApplicationEvent.h
	Source/Voyager/Event/ComponentEvent.h
	Source/Voyager/Event/Dispatcher.h
	Source/Voyager/Event/IDispatcher.h
	Source/Voyager/Event/IDispatcher.cpp
	Source/Voyager/Event/EntityEvent.h
	Source/Voyager/Event/KeyEvent.h
	Source/Voyager/Event/MouseEvent.h
)
source_group("Voyager\\Event" FILES ${Voyager_Folder_Event})

set(Voyager_Folder_ImGui
	Source/Voyager/ImGui/ImGuiBuild.cpp
	Source/Voyager/ImGui/ImGuiLayer.h
	Source/Voyager/ImGui/ImGuiLayer.cpp
)
source_group("Voyager\\ImGui" FILES ${Voyager_Folder_ImGui})

set(Voyager_Folder_Renderer
	Source/Voyager/Renderer/GraphicsContext.h
	Source/Voyager/Renderer/Shader.h
	Source/Voyager/Renderer/Shader.cpp
	Source/Voyager/Renderer/Shaderset.h
	Source/Voyager/Renderer/Shaderset.cpp
	Source/Voyager/Renderer/Camera.h
	Source/Voyager/Renderer/OrtographicCamera.h
	Source/Voyager/Renderer/OrtographicCamera.cpp
	Source/Voyager/Renderer/PerspectiveCamera.h
	Source/Voyager/Renderer/PerspectiveCamera.cpp
	Source/Voyager/Renderer/Buffer.h
	Source/Voyager/Renderer/Buffer.cpp
	Source/Voyager/Renderer/Geometry.h
	Source/Voyager/Renderer/Geometry.cpp
	Source/Voyager/Renderer/Renderer.h
	Source/Voyager/Renderer/Renderer.cpp
	Source/Voyager/Renderer/RendererAPIHandler.h
	Source/Voyager/Renderer/RendererAPIHandler.cpp
	Source/Voyager/Renderer/RenderCommand.h
	Source/Voyager/Renderer/RenderCommand.cpp
	Source/Voyager/Renderer/Pipeline.h
	Source/Voyager/Renderer/Pipeline.cpp
	Source/Voyager/Renderer/Texture.h
	Source/Voyager/Renderer/Texture.cpp
	Source/Voyager/Renderer/Material.h
	Source/Voyager/Renderer/Material.cpp
	Source/Voyager/Renderer/Transform.h
	Source/Voyager/Renderer/Transform.cpp
	Source/Voyager/Renderer/RenderJob.h
	Source/Voyager/Renderer/RenderJob.cpp
	Source/Voyager/Renderer/Identifier.cpp
	Source/Voyager/Renderer/Identifier.h
	Source/Voyager/Renderer/RenderFlags.h
	Source/Voyager/Renderer/RenderSettings.h
)
source_group("Voyager\\Renderer" FILES ${Voyager_Folder_Renderer})

set(Voyager_Folder_Renderer_Material
	Source/Voyager/Renderer/Material/Standard.h
)
source_group("Voyager\\Renderer\\Material" FILES ${Voyager_Folder_Renderer_Material})

set(Voyager_Folder_IO
    Source/Voyager/IO/Parsing.h
    Source/Voyager/IO/Parsing.cpp
	Source/Voyager/IO/JSONParser.h
	Source/Voyager/IO/OBJParser.cpp
	Source/Voyager/IO/OBJParser.h
	Source/Voyager/IO/ImportSettings.h
	Source/Voyager/IO/JSONParser.cpp
	Source/Voyager/IO/FileNotifier.h
)
source_group("Voyager\\IO" FILES ${Voyager_Folder_IO})

set(Voyager_Folder_Geometry
    Source/Voyager/Geometry/GeometryData.h
    Source/Voyager/Geometry/GeometryGenerator.h
    Source/Voyager/Geometry/GeometryGenerator.cpp
)
source_group("Voyager\\Geometry" FILES ${Voyager_Folder_Geometry})

set(Voyager_Folder_Image
    Source/Voyager/Image/ImageData.h
)
source_group("Voyager\\Image" FILES ${Voyager_Folder_Image})

set(Voyager_Folder_Math
	Source/Voyager/Math/Constants.h
	Source/Voyager/Math/Utils.h
)
source_group("Voyager\\Math" FILES ${Voyager_Folder_Math})

set(Voyager_Folder_Math_Vector
	Source/Voyager/Math/Vector/Base.h
	Source/Voyager/Math/Vector/VectorLayout.h
	Source/Voyager/Math/Vector/YawPitchRoll.h
	Source/Voyager/Math/Vector/Vector2.h
	Source/Voyager/Math/Vector/Vector3.h
	Source/Voyager/Math/Vector/Vector4.h
)
source_group("Voyager\\Math\\Vector" FILES ${Voyager_Folder_Math_Vector})

set(Voyager_Folder_Math_Matrix
    Source/Voyager/Math/Matrix/MatrixLayout.h
	Source/Voyager/Math/Matrix/Matrix2x2.h
	Source/Voyager/Math/Matrix/Matrix2x2H.h
	Source/Voyager/Math/Matrix/Matrix3x3.h
	Source/Voyager/Math/Matrix/Matrix4x4.h
)
source_group("Voyager\\Math\\Matrix" FILES ${Voyager_Folder_Math_Matrix})

set(Platform_Folder
	Source/Platform/APIType.h
)
source_group("Platform" FILES ${Platform_Folder})

set(Platform_Folder_Window
	Source/Platform/Window/WindowAPIHandler.h
	Source/Platform/Window/WindowAPIHandler.cpp
	Source/Platform/Window/WindowsInput.h
	Source/Platform/Window/WindowsInput.cpp
)
source_group("Platform\\Window" FILES ${Platform_Folder_Window})

set(Platform_Folder_Window_GLFW
	Source/Platform/Window/GLFW/GLFWHandler.h
	Source/Platform/Window/GLFW/GLFWHandler.cpp
)
source_group("Platform\\Window\\GLFW" FILES ${Platform_Folder_Window_GLFW})

set(Platform_Folder_Window_WIN
	Source/Platform/Window/WIN/Win32Handler.h
	Source/Platform/Window/WIN/Win32Handler.cpp
)
source_group("Platform\\Window\\WIN" FILES ${Platform_Folder_Window_WIN})

set(Platform_Folder_OpenGL
	Source/Platform/OpenGL/OpenGLPipeline.h
	Source/Platform/OpenGL/OpenGLPipeline.cpp
	Source/Platform/OpenGL/OpenGLContext.h
	Source/Platform/OpenGL/OpenGLContext.cpp
	Source/Platform/OpenGL/OpenGLAssert.h
	Source/Platform/OpenGL/OpenGLProgram.h
	Source/Platform/OpenGL/OpenGLProgram.cpp
	Source/Platform/OpenGL/OpenGLShader.h
	Source/Platform/OpenGL/OpenGLShader.cpp
	Source/Platform/OpenGL/OpenGLBuffer.h
	Source/Platform/OpenGL/OpenGLBuffer.cpp
	Source/Platform/OpenGL/OpenGLVertexArray.h
	Source/Platform/OpenGL/OpenGLVertexArray.cpp
	Source/Platform/OpenGL/OpenGLShaderset.h
	Source/Platform/OpenGL/OpenGLShaderset.cpp
	Source/Platform/OpenGL/OpenGLStatus.h
	Source/Platform/OpenGL/OpenGLStatus.cpp
	Source/Platform/OpenGL/OpenGLRendererAPI.h
	Source/Platform/OpenGL/OpenGLRendererAPI.cpp
	Source/Platform/OpenGL/OpenGLTexture.h
	Source/Platform/OpenGL/OpenGLTexture.cpp
	Source/Platform/OpenGL/OpenGLTransform.h
	Source/Platform/OpenGL/OpenGLTransform.cpp
)
source_group("Platform\\OpenGL" FILES ${Platform_Folder_OpenGL})

set(Platform_Folder_DirectX

)
source_group("Platform\\DirectX" FILES ${Platform_Folder_DirectX})

set(ALL_FILES
	${Contrib_Folder_STB}
	${Voyager_Folder_Components}
	${Voyager_Folder_Source}
    ${Voyager_Folder_Core}
    ${Voyager_Folder_Event}
	${Voyager_Folder_ImGui}
	${Voyager_Folder_Renderer}
	${Voyager_Folder_Renderer_Material}
	${Voyager_Folder_IO}
	${Voyager_Folder_Geometry}
	${Voyager_Folder_Image}
	${Voyager_Folder_Math}
	${Voyager_Folder_Math_Vector}
	${Voyager_Folder_Math_Matrix}
	${Platform_Folder}
	${Platform_Folder_Window}
	${Platform_Folder_Window_GLFW}
	${Platform_Folder_Window_WIN}
	${Platform_Folder_OpenGL}
	${Platform_Folder_DirectX}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Voyager)

################################################################################
# Target standard
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

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
    OUTPUT_DIRECTORY_DEBUG   "${CMAKE_SOURCE_DIR}/../Contrib/voyager/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/"
    OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/../Contrib/voyager/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/"
)
################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
	"${CMAKE_SOURCE_DIR}/Voyager/Source;"
	"${CMAKE_SOURCE_DIR}/Voyager/Contrib/spdlog/include;"
	"${CMAKE_SOURCE_DIR}/Voyager/Contrib/glad/include;"
	"${CMAKE_SOURCE_DIR}/Voyager/Contrib/glfw/include;"
	"${CMAKE_SOURCE_DIR}/Voyager/Contrib/stb;"
	"${CMAKE_SOURCE_DIR}/Voyager/Contrib/imgui;"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "VE_PLATFORM_WINDOWS;"
    "VE_BUILD_DLL;"
	"VE_DEBUG;"
	"GLFW_INCLUDE_NONE;"
	"IMGUI_API=__declspec(dllexport);"
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
            /MD
            /Gy
        >
        /permissive-;
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
        /DEBUG:FULL;
        /SUBSYSTEM:CONSOLE
    )
endif()

################################################################################
# Dependencies
################################################################################

string(CONCAT ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:Debug>:"
        "glfw3;"
        "opengl32;"
        "glu32;"
		"glad;"
		"imgui;"
    ">"
    "$<$<CONFIG:Release>:"
        "glfw3;"
        "opengl32;"
        "glu32;"
		"glad;"
		"imgui;"
    ">"
)
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

target_link_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}/Voyager/Contrib/glfw/lib/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/;${CMAKE_SOURCE_DIR}/Voyager/Contrib/glad/lib/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/;${CMAKE_SOURCE_DIR}/Voyager/Contrib/imgui/lib/$<CONFIG>-${CMAKE_VS_PLATFORM_NAME}/"
)