cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(channeldelay LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include_directories("../../pambase/")
include_directories("../../pamfft/")

link_directories("../../lib")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS, "Build Type: ${CMAKE_BUILD_TYPE}")

file(GLOB SOURCES "*.cpp")

add_library(channeldelay MODULE ${SOURCES})

target_compile_definitions(channeldelay PUBLIC DLL_EXPORTS wxUSE_UNICODE _test_ _MSL_STDINT_H)

list(APPEND flags "-fPIC" "-Wall" "-fpermissive")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	list(APPEND flags "-O3")
	target_compile_definitions(channeldelay PUBLIC NDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND flags "-Og")
	target_compile_options(channeldelay PRIVATE ${flags})
	target_compile_definitions(channeldelay PUBLIC __WXDEBUG__)
endif()

target_compile_options(channeldelay PRIVATE ${flags})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(channeldelay PUBLIC __WXGNU__)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(channeldelay PUBLIC __WXMSW__)
endif()


#find external libraries
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})


target_link_libraries(channeldelay ${wxWidgets_LIBRARIES})
target_link_libraries(channeldelay pambase)
target_link_libraries(channeldelay pamfft)

set_target_properties(channeldelay PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../../../lib/test")

#linux specific
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	install(TARGETS channeldelay LIBRARY DESTINATION /usr/local/lib/pam2/test)
endif()
		
