# ROOT PROJECT FILE

cmake_minimum_required(VERSION 3.10)

# Declare project
project(Inline-Engine)


# Project uses C and C++
enable_language(C)
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)


# Configurations
set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE TYPE INTERNAL FORCE)
set(DEBUG_CONFIGURATIONS Debug)


# Set platform-specific properties
include(GetPlatform.cmake)
include(Paths.cmake)
include(CopyRuntime.cmake)

if (TARGET_COMPILER_MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /MP /await")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4638") # Ignore XML doc not found reference
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd5033") # Register keyword is now deprecated but retarded Bullet uses it	
endif()


# Enable filter grouping of projects inside solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)


# Properties applied to all targets
include_directories("${CMAKE_CURRENT_LIST_DIR}/Engine")
include_directories("${EXTERNALS_INCLUDE}/Bullet") # because Bullet is retarded...


# Add additional folders
add_subdirectory(Engine)
add_subdirectory(Test)
add_subdirectory(Executables)


# Add custom target containing global files
add_custom_target(Files SOURCES 
	CMakeLists.txt
	Paths.cmake
	GetPlatform.cmake
	CopyRuntime.cmake)
set_target_properties(Files PROPERTIES FOLDER Files)

# Add Mathter.natvis to all targets
function(get_all_targets _result _dir)
    get_property(_subdirs DIRECTORY "${_dir}" PROPERTY SUBDIRECTORIES)
    foreach(_subdir IN LISTS _subdirs)
        get_all_targets(${_result} "${_subdir}")
    endforeach()
    get_property(_sub_targets DIRECTORY "${_dir}" PROPERTY BUILDSYSTEM_TARGETS)
    set(${_result} ${${_result}} ${_sub_targets} PARENT_SCOPE)
endfunction()

get_all_targets(all_targets ${CMAKE_SOURCE_DIR})
foreach (tar IN ITEMS ${all_targets})
	get_target_property(tar_type ${tar} TYPE)
	if (tar_type MATCHES "(STATIC_LIBRARY|MODULE_LIBRARY|SHARED_LIBRARY|EXECUTABLE)")
		target_sources(${tar} PRIVATE "${EXTERNALS_INCLUDE}/Mathter/Mathter.natvis")
	endif()
endforeach()
source_group("" FILES "${EXTERNALS_INCLUDE}/Mathter/Mathter.natvis")

# Put projects in their folders
set_target_properties(BaseLibrary PROPERTIES FOLDER Modules)
set_target_properties(GraphicsApi_D3D12 PROPERTIES FOLDER Modules)
set_target_properties(GraphicsEngine_LL PROPERTIES FOLDER Modules)
set_target_properties(AssetLibrary PROPERTIES FOLDER Modules)
set_target_properties(GuiEngine PROPERTIES FOLDER Modules)
set_target_properties(Core PROPERTIES FOLDER Modules)
set_target_properties(NetworkEngine PROPERTIES FOLDER Modules)
set_target_properties(NetworkApi PROPERTIES FOLDER Modules)
set_target_properties(PhysicsEngineBullet PROPERTIES FOLDER Modules)

set_target_properties(Test_General PROPERTIES FOLDER Test)
set_target_properties(QC_Simulator PROPERTIES FOLDER Test)
set_target_properties(Test_Unit PROPERTIES FOLDER Test)

set_target_properties(Editor PROPERTIES FOLDER Executables)


