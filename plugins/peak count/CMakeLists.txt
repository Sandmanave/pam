cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(peakcount LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include_directories("../../pambase/")

link_directories("../../lib")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS, "Build Type: ${CMAKE_BUILD_TYPE}")

file(GLOB SOURCES "*.cpp")

add_library(peakcount MODULE ${SOURCES})

target_compile_definitions(peakcount PUBLIC DLL_EXPORTS wxUSE_UNICODE _test_ _MSL_STDINT_H)

list(APPEND flags "-fPIC" "-Wall" "-fpermissive")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	list(APPEND flags "-O3")
	target_compile_definitions(peakcount PUBLIC NDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND flags "-Og")
	target_compile_options(peakcount PRIVATE ${flags})
	target_compile_definitions(peakcount PUBLIC __WXDEBUG__)
endif()

target_compile_options(peakcount PRIVATE ${flags})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions(peakcount PUBLIC __WXGNU__)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions(peakcount PUBLIC __WXMSW__)
endif()


#find external libraries
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})


target_link_libraries(peakcount ${wxWidgets_LIBRARIES})
target_link_libraries(peakcount pambase)

set_target_properties(peakcount PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../../../lib/test")


#linux specific
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	install(TARGETS peakcount LIBRARY DESTINATION /usr/local/lib/pam2/monitor)
endif()		
