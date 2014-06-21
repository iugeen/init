#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vtksys" for configuration "Release"
set_property(TARGET vtksys APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtksys PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "dl"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtksys-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtksys )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtksys "${_IMPORT_PREFIX}/lib/libvtksys-6.0.a" )

# Import target "vtkCommonCore" for configuration "Release"
set_property(TARGET vtkCommonCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkCommonCore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtksys"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkCommonCore-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonCore "${_IMPORT_PREFIX}/lib/libvtkCommonCore-6.0.a" )

# Import target "vtkCommonMath" for configuration "Release"
set_property(TARGET vtkCommonMath APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkCommonMath PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonCore"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkCommonMath-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonMath )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonMath "${_IMPORT_PREFIX}/lib/libvtkCommonMath-6.0.a" )

# Import target "vtkCommonMisc" for configuration "Release"
set_property(TARGET vtkCommonMisc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkCommonMisc PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonMath"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkCommonMisc-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonMisc )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonMisc "${_IMPORT_PREFIX}/lib/libvtkCommonMisc-6.0.a" )

# Import target "vtkCommonSystem" for configuration "Release"
set_property(TARGET vtkCommonSystem APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkCommonSystem PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonCore;vtksys"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkCommonSystem-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonSystem )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonSystem "${_IMPORT_PREFIX}/lib/libvtkCommonSystem-6.0.a" )

# Import target "vtkCommonTransforms" for configuration "Release"
set_property(TARGET vtkCommonTransforms APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkCommonTransforms PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonCore;vtkCommonMath"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkCommonTransforms-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonTransforms )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonTransforms "${_IMPORT_PREFIX}/lib/libvtkCommonTransforms-6.0.a" )

# Import target "vtkCommonDataModel" for configuration "Release"
set_property(TARGET vtkCommonDataModel APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkCommonDataModel PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonMath;vtkCommonMisc;vtkCommonSystem;vtkCommonTransforms"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkCommonDataModel-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonDataModel )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonDataModel "${_IMPORT_PREFIX}/lib/libvtkCommonDataModel-6.0.a" )

# Import target "vtkCommonComputationalGeometry" for configuration "Release"
set_property(TARGET vtkCommonComputationalGeometry APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkCommonComputationalGeometry PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonDataModel;vtkCommonMath;vtkCommonSystem"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkCommonComputationalGeometry-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonComputationalGeometry )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonComputationalGeometry "${_IMPORT_PREFIX}/lib/libvtkCommonComputationalGeometry-6.0.a" )

# Import target "vtkCommonExecutionModel" for configuration "Release"
set_property(TARGET vtkCommonExecutionModel APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkCommonExecutionModel PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonDataModel"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkCommonExecutionModel-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkCommonExecutionModel )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkCommonExecutionModel "${_IMPORT_PREFIX}/lib/libvtkCommonExecutionModel-6.0.a" )

# Import target "vtkDICOMParser" for configuration "Release"
set_property(TARGET vtkDICOMParser APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkDICOMParser PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkDICOMParser-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkDICOMParser )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkDICOMParser "${_IMPORT_PREFIX}/lib/libvtkDICOMParser-6.0.a" )

# Import target "vtkFiltersCore" for configuration "Release"
set_property(TARGET vtkFiltersCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkFiltersCore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonExecutionModel;vtkCommonMath;vtkCommonMisc;vtkCommonSystem;vtkCommonTransforms"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkFiltersCore-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkFiltersCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkFiltersCore "${_IMPORT_PREFIX}/lib/libvtkFiltersCore-6.0.a" )

# Import target "vtkFiltersGeneral" for configuration "Release"
set_property(TARGET vtkFiltersGeneral APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkFiltersGeneral PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonComputationalGeometry;vtkFiltersCore"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkFiltersGeneral-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkFiltersGeneral )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkFiltersGeneral "${_IMPORT_PREFIX}/lib/libvtkFiltersGeneral-6.0.a" )

# Import target "vtkImagingCore" for configuration "Release"
set_property(TARGET vtkImagingCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkImagingCore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonExecutionModel;vtkCommonMath;vtkCommonSystem;vtkCommonTransforms"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkImagingCore-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkImagingCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkImagingCore "${_IMPORT_PREFIX}/lib/libvtkImagingCore-6.0.a" )

# Import target "vtkImagingFourier" for configuration "Release"
set_property(TARGET vtkImagingFourier APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkImagingFourier PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkImagingCore"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkImagingFourier-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkImagingFourier )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkImagingFourier "${_IMPORT_PREFIX}/lib/libvtkImagingFourier-6.0.a" )

# Import target "vtkalglib" for configuration "Release"
set_property(TARGET vtkalglib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkalglib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkalglib-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkalglib )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkalglib "${_IMPORT_PREFIX}/lib/libvtkalglib-6.0.a" )

# Import target "vtkFiltersStatistics" for configuration "Release"
set_property(TARGET vtkFiltersStatistics APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkFiltersStatistics PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonExecutionModel;vtkCommonMath;vtkCommonMisc;vtkCommonTransforms;vtkImagingFourier;vtkalglib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkFiltersStatistics-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkFiltersStatistics )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkFiltersStatistics "${_IMPORT_PREFIX}/lib/libvtkFiltersStatistics-6.0.a" )

# Import target "vtkFiltersExtraction" for configuration "Release"
set_property(TARGET vtkFiltersExtraction APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkFiltersExtraction PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonExecutionModel;vtkFiltersCore;vtkFiltersGeneral;vtkFiltersStatistics"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkFiltersExtraction-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkFiltersExtraction )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkFiltersExtraction "${_IMPORT_PREFIX}/lib/libvtkFiltersExtraction-6.0.a" )

# Import target "vtkFiltersGeometry" for configuration "Release"
set_property(TARGET vtkFiltersGeometry APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkFiltersGeometry PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkFiltersCore"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkFiltersGeometry-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkFiltersGeometry )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkFiltersGeometry "${_IMPORT_PREFIX}/lib/libvtkFiltersGeometry-6.0.a" )

# Import target "vtkFiltersSources" for configuration "Release"
set_property(TARGET vtkFiltersSources APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkFiltersSources PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonComputationalGeometry;vtkFiltersGeneral"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkFiltersSources-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkFiltersSources )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkFiltersSources "${_IMPORT_PREFIX}/lib/libvtkFiltersSources-6.0.a" )

# Import target "vtkFiltersModeling" for configuration "Release"
set_property(TARGET vtkFiltersModeling APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkFiltersModeling PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkFiltersGeneral;vtkFiltersSources"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkFiltersModeling-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkFiltersModeling )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkFiltersModeling "${_IMPORT_PREFIX}/lib/libvtkFiltersModeling-6.0.a" )

# Import target "vtkzlib" for configuration "Release"
set_property(TARGET vtkzlib APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkzlib PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkzlib-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkzlib )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkzlib "${_IMPORT_PREFIX}/lib/libvtkzlib-6.0.a" )

# Import target "vtkIOCore" for configuration "Release"
set_property(TARGET vtkIOCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkIOCore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMisc;vtksys;vtkzlib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkIOCore-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOCore "${_IMPORT_PREFIX}/lib/libvtkIOCore-6.0.a" )

# Import target "vtkjsoncpp" for configuration "Release"
set_property(TARGET vtkjsoncpp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkjsoncpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkjsoncpp-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkjsoncpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkjsoncpp "${_IMPORT_PREFIX}/lib/libvtkjsoncpp-6.0.a" )

# Import target "vtkIOGeometry" for configuration "Release"
set_property(TARGET vtkIOGeometry APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkIOGeometry PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonDataModel;vtkCommonMisc;vtkCommonSystem;vtkIOCore;vtkjsoncpp;vtkzlib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkIOGeometry-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOGeometry )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOGeometry "${_IMPORT_PREFIX}/lib/libvtkIOGeometry-6.0.a" )

# Import target "vtkmetaio" for configuration "Release"
set_property(TARGET vtkmetaio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkmetaio PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkzlib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkmetaio-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkmetaio )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkmetaio "${_IMPORT_PREFIX}/lib/libvtkmetaio-6.0.a" )

# Import target "vtkjpeg" for configuration "Release"
set_property(TARGET vtkjpeg APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkjpeg PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkjpeg-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkjpeg )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkjpeg "${_IMPORT_PREFIX}/lib/libvtkjpeg-6.0.a" )

# Import target "vtkpng" for configuration "Release"
set_property(TARGET vtkpng APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkpng PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkzlib;-lm"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkpng-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkpng )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkpng "${_IMPORT_PREFIX}/lib/libvtkpng-6.0.a" )

# Import target "vtktiff" for configuration "Release"
set_property(TARGET vtktiff APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtktiff PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkzlib;vtkjpeg;-lm"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtktiff-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtktiff )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtktiff "${_IMPORT_PREFIX}/lib/libvtktiff-6.0.a" )

# Import target "vtkIOImage" for configuration "Release"
set_property(TARGET vtkIOImage APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkIOImage PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonDataModel;vtkCommonExecutionModel;vtkCommonMath;vtkCommonMisc;vtkCommonSystem;vtkCommonTransforms;vtkDICOMParser;vtkIOCore;vtkmetaio;vtkjpeg;vtkpng;vtktiff"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkIOImage-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOImage )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOImage "${_IMPORT_PREFIX}/lib/libvtkIOImage-6.0.a" )

# Import target "vtkIOLegacy" for configuration "Release"
set_property(TARGET vtkIOLegacy APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkIOLegacy PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonDataModel;vtkCommonMisc;vtkCommonSystem;vtkIOCore"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkIOLegacy-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOLegacy )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOLegacy "${_IMPORT_PREFIX}/lib/libvtkIOLegacy-6.0.a" )

# Import target "vtkInfovisCore" for configuration "Release"
set_property(TARGET vtkInfovisCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkInfovisCore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonDataModel;vtkCommonSystem;vtkFiltersExtraction;vtkFiltersGeneral"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkInfovisCore-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkInfovisCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkInfovisCore "${_IMPORT_PREFIX}/lib/libvtkInfovisCore-6.0.a" )

# Import target "vtklibxml2" for configuration "Release"
set_property(TARGET vtklibxml2 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtklibxml2 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkzlib;dl;dl;m"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtklibxml2-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtklibxml2 )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtklibxml2 "${_IMPORT_PREFIX}/lib/libvtklibxml2-6.0.a" )

# Import target "vtkIOInfovis" for configuration "Release"
set_property(TARGET vtkIOInfovis APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkIOInfovis PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonDataModel;vtkCommonMisc;vtkCommonSystem;vtkIOCore;vtkIOLegacy;vtkInfovisCore;vtklibxml2"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkIOInfovis-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOInfovis )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOInfovis "${_IMPORT_PREFIX}/lib/libvtkIOInfovis-6.0.a" )

# Import target "vtkIOPLY" for configuration "Release"
set_property(TARGET vtkIOPLY APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkIOPLY PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonExecutionModel;vtkCommonMisc;vtkIOGeometry"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkIOPLY-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOPLY )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOPLY "${_IMPORT_PREFIX}/lib/libvtkIOPLY-6.0.a" )

# Import target "vtkexpat" for configuration "Release"
set_property(TARGET vtkexpat APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkexpat PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkexpat-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkexpat )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkexpat "${_IMPORT_PREFIX}/lib/libvtkexpat-6.0.a" )

# Import target "vtkIOXMLParser" for configuration "Release"
set_property(TARGET vtkIOXMLParser APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkIOXMLParser PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonDataModel;vtkCommonMisc;vtkCommonSystem;vtkIOCore;vtkexpat"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkIOXMLParser-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOXMLParser )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOXMLParser "${_IMPORT_PREFIX}/lib/libvtkIOXMLParser-6.0.a" )

# Import target "vtkIOXML" for configuration "Release"
set_property(TARGET vtkIOXML APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkIOXML PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkIOGeometry;vtkIOXMLParser"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkIOXML-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkIOXML )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkIOXML "${_IMPORT_PREFIX}/lib/libvtkIOXML-6.0.a" )

# Import target "vtkParallelCore" for configuration "Release"
set_property(TARGET vtkParallelCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkParallelCore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonCore;vtkIOLegacy"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkParallelCore-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkParallelCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkParallelCore "${_IMPORT_PREFIX}/lib/libvtkParallelCore-6.0.a" )

# Import target "vtkRenderingCore" for configuration "Release"
set_property(TARGET vtkRenderingCore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkRenderingCore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkCommonExecutionModel;vtkCommonTransforms;vtkFiltersExtraction;vtkFiltersGeneral;vtkFiltersGeometry;vtkFiltersSources;vtkIOImage;vtkIOXMLParser"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkRenderingCore-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkRenderingCore )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkRenderingCore "${_IMPORT_PREFIX}/lib/libvtkRenderingCore-6.0.a" )

# Import target "vtkfreetype" for configuration "Release"
set_property(TARGET vtkfreetype APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkfreetype PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkzlib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkfreetype-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkfreetype )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkfreetype "${_IMPORT_PREFIX}/lib/libvtkfreetype-6.0.a" )

# Import target "vtkRenderingFreeType" for configuration "Release"
set_property(TARGET vtkRenderingFreeType APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(vtkRenderingFreeType PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "vtkRenderingCore;vtkfreetype"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libvtkRenderingFreeType-6.0.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS vtkRenderingFreeType )
list(APPEND _IMPORT_CHECK_FILES_FOR_vtkRenderingFreeType "${_IMPORT_PREFIX}/lib/libvtkRenderingFreeType-6.0.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
