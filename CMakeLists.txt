cmake_minimum_required(VERSION 3.25)
project(
	CraftpixIndieJam-1-2026
	VERSION 0.1.0
	LANGUAGES C
)

set(CMAKE_C_STANDARD          23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS        OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR})

set(CIJ_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(CIJ_VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Vendor")

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON  CACHE BOOL "" FORCE)
add_subdirectory(
	"${CIJ_VENDOR_DIR}/SDL"
	EXCLUDE_FROM_ALL SYSTEM
)

add_subdirectory(
	"${CIJ_VENDOR_DIR}/glad"
	EXCLUDE_FROM_ALL SYSTEM
)

add_library(KDG STATIC)
set_target_properties(
	KDG PROPERTIES
	OUTPUT_NAME "KDG"
)
file(
	GLOB_RECURSE KDG_SOURCES CONFIGURE_DEPENDS
	"${CIJ_SOURCE_DIR}/*.kdg.c" 
	"${CIJ_SOURCE_DIR}/*.kdg.h"
)
target_sources(
	KDG PRIVATE
	${KDG_SOURCES}
)
target_include_directories(
	KDG PRIVATE
	${CIJ_SOURCE_DIR}
)
target_include_directories(
	KDG PUBLIC
	${CIJ_SOURCE_DIR}
)
target_link_libraries(
	KDG PUBLIC
	SDL3::SDL3
	glad
)

add_executable(CIJ)
set_target_properties(
	CIJ PROPERTIES
	OUTPUT_NAME "CIJ"
)
file(
	GLOB_RECURSE CIJ_SOURCES CONFIGURE_DEPENDS
	"${CIJ_SOURCE_DIR}/*.cij.c"
	"${CIJ_SOURCE_DIR}/*.cij.h"
)
target_sources(
	CIJ PRIVATE
	${CIJ_SOURCES}
)
target_link_libraries(
	CIJ PRIVATE
	KDG
)
install(
	FILES
		$<TARGET_FILE:CIJ>
	DESTINATION
		"."
)

file(
	GLOB_RECURSE SCRIPT_SOURCES
	RELATIVE ${CIJ_SOURCE_DIR}
	"${CIJ_SOURCE_DIR}/*.script.c"
)
foreach(SCRIPT_SOURCE IN LISTS SCRIPT_SOURCES)
	get_filename_component(
		SCRIPT_SOURCE_WO_EXTENSION
		${SCRIPT_SOURCE} NAME_WE
	)
	set(SCRIPT "Script${SCRIPT_SOURCE_WO_EXTENSION}")
	add_library(${SCRIPT} SHARED)
	set_target_properties(
		${SCRIPT} PROPERTIES
		OUTPUT_NAME ${SCRIPT}
	)
	target_sources(
		${SCRIPT} PRIVATE
		"${CIJ_SOURCE_DIR}/${SCRIPT_SOURCE}"
	)
	target_link_libraries(
		${SCRIPT} PRIVATE
		KDG
	)
	install(
		FILES
			$<TARGET_FILE:${SCRIPT}>
		DESTINATION
			"."
	)
endforeach()

