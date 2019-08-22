cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(r128 LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include_directories("../../pambase/")
include_directories("../../pamlevel/")

link_directories("../../lib")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS, "Build Type: ${CMAKE_BUILD_TYPE}")

file(GLOB SOURCES "*.cpp")

add_library(r128 MODULE ${SOURCES})

target_compile_definitions(r128 PUBLIC DLL_EXPORTS wxUSE_UNICODE _monitor_ _MSL_STDINT_H)

list(APPEND flags "-fPIC" "-Wall" "-fpermissive")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	list(APPEND flags "-O3")
	target_compile_definitions(r128 PUBLIC NDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND flags "-Og")
	target_compile_options(r128 PRIVATE ${flags})
	target_compile_definitions(r128 PUBLIC __WXDEBUG__)
endif()

target_compile_options(r128 PRIVATE ${flags})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(r128 PUBLIC __WXGNU__)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(r128 PUBLIC __WXMSW__)
endif()


#find external libraries
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})


target_link_libraries(r128 ${wxWidgets_LIBRARIES})
target_link_libraries(r128 pambase)
target_link_libraries(r128 pamlevel)

set_target_properties(r128 PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../../../lib/monitor")


#linux specific
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	install(TARGETS r128 LIBRARY DESTINATION /usr/local/lib/pam2/monitor)
endif()	
