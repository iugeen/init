#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ves" for configuration "Release"
set_property(TARGET ves APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ves PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libves.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS ves )
list(APPEND _IMPORT_CHECK_FILES_FOR_ves "${_IMPORT_PREFIX}/lib/libves.a" )

# Import target "vesShaders" for configuration "Release"
set_property(TARGET vesShaders APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vesShaders PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvesShaders.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vesShaders )
list(APPEND _IMPORT_CHECK_FILES_FOR_vesShaders "${_IMPORT_PREFIX}/lib/libvesShaders.a" )

# Import target "kiwi" for configuration "Release"
set_property(TARGET kiwi APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(kiwi PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "ves;vesShaders;vtkIOGeometry;vtkIOXML;vtkIOImage;vtkIOLegacy;vtkIOPLY;vtkFiltersCore;vtkFiltersSources;vtkFiltersGeometry;vtkFiltersModeling;vtkImagingCore;vtkRenderingCore;vtkRenderingFreeType;vtksys"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libkiwi.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS kiwi )
list(APPEND _IMPORT_CHECK_FILES_FOR_kiwi "${_IMPORT_PREFIX}/lib/libkiwi.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
