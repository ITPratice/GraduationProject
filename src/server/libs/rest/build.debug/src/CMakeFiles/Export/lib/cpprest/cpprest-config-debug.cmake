#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "cpprest" for configuration "Debug"
set_property(TARGET cpprest APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(cpprest PROPERTIES
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libcpprest.so.2.9"
  IMPORTED_SONAME_DEBUG "libcpprest.so.2.9"
  )

list(APPEND _IMPORT_CHECK_TARGETS cpprest )
list(APPEND _IMPORT_CHECK_FILES_FOR_cpprest "${_IMPORT_PREFIX}/lib/libcpprest.so.2.9" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
