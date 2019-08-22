cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(distortion LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include_directories("../../pambase/")
include_directories("../../pamfft/")
include_directories("../../external/kiss_fft130")
include_directories("../../external/kiss_fft130/tools")

link_directories("../../lib")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS, "Build Type: ${CMAKE_BUILD_TYPE}")

file(GLOB SOURCES "*.cpp")

add_library(distortion MODULE ${SOURCES})

target_compile_definitions(distortion PUBLIC DLL_EXPORTS wxUSE_UNICODE _test_ _MSL_STDINT_H)

list(APPEND flags "-fPIC" "-Wall" "-fpermissive")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	list(APPEND flags "-O3")
	target_compile_definitions(distortion PUBLIC NDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND flags "-Og")
	target_compile_options(distortion PRIVATE ${flags})
	target_compile_definitions(distortion PUBLIC __WXDEBUG__)
endif()

target_compile_options(distortion PRIVATE ${flags})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(distortion PUBLIC __WXGNU__)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(distortion PUBLIC __WXMSW__)
endif()


#find external libraries
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})


target_link_libraries(distortion ${wxWidgets_LIBRARIES})
target_link_libraries(distortion pambase)
target_link_libraries(distortion pamfft)

set_target_properties(distortion PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../../../lib/test")

#linux specific
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	install(TARGETS distortion LIBRARY DESTINATION /usr/local/lib/pam2/test)
endif()
		
