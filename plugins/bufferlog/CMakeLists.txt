cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(bufferlog LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include_directories("../../pambase/")

link_directories("../../lib")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS, "Build Type: ${CMAKE_BUILD_TYPE}")

file(GLOB SOURCES "*.cpp")

add_library(bufferlog MODULE ${SOURCES})

target_compile_definitions(bufferlog PUBLIC DLL_EXPORTS wxUSE_UNICODE _monitor_ _MSL_STDINT_H)

list(APPEND flags "-fPIC" "-Wall" "-fpermissive")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	list(APPEND flags "-O3")
	target_compile_definitions(bufferlog PUBLIC NDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND flags "-Og")
	target_compile_options(bufferlog PRIVATE ${flags})
	target_compile_definitions(bufferlog PUBLIC __WXDEBUG__)
endif()

target_compile_options(bufferlog PRIVATE ${flags})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(bufferlog PUBLIC __WXGNU__)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(bufferlog PUBLIC __WXMSW__)
endif()


#find external libraries
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})


target_link_libraries(bufferlog ${wxWidgets_LIBRARIES})
target_link_libraries(bufferlog pambase)

set_target_properties(bufferlog PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../../lib/monitor")


		
