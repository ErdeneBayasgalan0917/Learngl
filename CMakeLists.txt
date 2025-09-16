# ...existing code...
cmake_minimum_required(VERSION 3.10)
project(learngl)

# Set source files
set(SOURCES
	src/main.cpp
	src/glad.c
)

# Include directories
include_directories(
	${CMAKE_SOURCE_DIR}/include
)

# Link directories
link_directories(
	lib
)

# Create executable
add_executable(learngl ${SOURCES})

# Set output name based on build type (safe for single-config generators)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set_target_properties(learngl PROPERTIES OUTPUT_NAME "learngl_debug")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set_target_properties(learngl PROPERTIES OUTPUT_NAME "learngl_release")
endif()

# Link libraries (GLFW, OpenGL)
target_link_libraries(learngl ${CMAKE_SOURCE_DIR}/lib/libglfw3.a opengl32)

# Ensure _DEBUG is defined for Debug builds
target_compile_definitions(learngl PRIVATE
	$<$<CONFIG:Debug>:_DEBUG>
)

# Copy DLL after build (Windows only)
add_custom_command(TARGET learngl POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_SOURCE_DIR}/lib/libglfw3.a
		$<TARGET_FILE_DIR:learngl>
)
