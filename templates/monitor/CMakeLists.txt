cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project([CLASS_PREFIX] LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include_directories("../../pambase/")
!pamfft include_directories("../../pamfft/")
!pamfft include_directories("../../external/kiss_fft130")
!pamfft include_directories("../../external/kiss_fft130/tools")
!pamlevel include_directories("../../pamlevel/")

link_directories("../../lib")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS, "Build Type: ${CMAKE_BUILD_TYPE}")

file(GLOB SOURCES "*.cpp")

add_library([CLASS_PREFIX] MODULE ${SOURCES})

target_compile_definitions([CLASS_PREFIX] PUBLIC DLL_EXPORTS wxUSE_UNICODE _monitor_ _MSL_STDINT_H)

list(APPEND flags "-fPIC" "-Wall" "-fpermissive" "-O3")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	list(APPEND flags "-O3")
	target_compile_definitions([CLASS_PREFIX] PUBLIC NDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND flags "-Og")
	target_compile_options([CLASS_PREFIX] PRIVATE ${flags})
	target_compile_definitions([CLASS_PREFIX] PUBLIC __WXDEBUG__)
endif()

target_compile_options([CLASS_PREFIX] PRIVATE ${flags})

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_compile_definitions([CLASS_PREFIX] PUBLIC __WXGNU__)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_compile_definitions([CLASS_PREFIX] PUBLIC __WXMSW__)
endif()


#find external libraries
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})

target_link_libraries([CLASS_PREFIX] ${wxWidgets_LIBRARIES})
target_link_libraries([CLASS_PREFIX] pambase)
!pamfft  target_link_libraries([CLASS_PREFIX] pamfft)
!pamlevel target_link_libraries([CLASS_PREFIX] pamlevel)

set_target_properties([CLASS_PREFIX] PROPERTIES LIBRARY_OUTPUT_DIRECTORY "../../../lib/monitor")

#linux specific
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	install(TARGETS [CLASS_PREFIX] LIBRARY DESTINATION /usr/local/lib/pam2/monitor)
endif()

		
