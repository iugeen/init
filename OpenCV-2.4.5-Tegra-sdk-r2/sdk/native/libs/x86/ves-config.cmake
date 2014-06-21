# Config file for VES - defines the following variables:
#
#  VES_INCLUDE_DIRS - include directories for ves
#  VES_LIBRARIES    - libraries to link against for ves


get_filename_component(VES_CONFIG_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)


# setup include dirs
set(VES_INCLUDE_DIRS)
set(VES_RELATIVE_INCLUDE_DIRS ./.;ves/.;kiwi/.;kiwi/pcl/.)

if(EXISTS "${VES_CONFIG_DIR}/CMakeCache.txt")
   include("${VES_CONFIG_DIR}/ves-build-config.cmake")
else()
  set(VES_INCLUDE_DIR_RELATIVE_TO_CONFIG_DIR ../include/ves)
  set(VES_INCLUDE_BASE_DIR "${VES_CONFIG_DIR}/${VES_INCLUDE_DIR_RELATIVE_TO_CONFIG_DIR}")
  list(APPEND VES_RELATIVE_INCLUDE_DIRS ves/.;shaders/.)
endif()

foreach(dir ${VES_RELATIVE_INCLUDE_DIRS})
  list(APPEND VES_INCLUDE_DIRS "${VES_INCLUDE_BASE_DIR}/${dir}")
endforeach()


# setup libraries & other targets
include("${VES_CONFIG_DIR}/ves-targets.cmake")
set(VES_LIBRARIES ves;vesShaders;kiwi)
