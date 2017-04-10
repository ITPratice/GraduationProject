# Install script for directory: /home/ubuntu/Desktop/casablanca/Release/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcpprest.so.2.9"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcpprest.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries/libcpprest.so.2.9"
    "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries/libcpprest.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcpprest.so.2.9"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcpprest.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cpprest" TYPE FILE FILES
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/filestream.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/http_client.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/http_msg.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/interopstream.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/json.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/http_headers.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/asyncrt_utils.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/rawptrstream.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/ws_msg.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/astreambuf.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/oauth2.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/base_uri.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/uri.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/version.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/streams.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/uri_builder.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/ws_client.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/oauth1.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/http_listener.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/containerstream.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/producerconsumerstream.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/pplx" TYPE FILE FILES
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/pplx/pplxinterface.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/pplx/pplxcancellation_token.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/pplx/pplxconv.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/pplx/pplxwin.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/pplx/threadpool.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/pplx/pplxtasks.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/pplx/pplxlinux.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/pplx/pplx.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cpprest/details" TYPE FILE FILES
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/basic_types.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/http_server.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/nosal.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/cpprest_compat.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/http_server_api.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/http_server_httpsys.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/http_server_asio.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/uri_parser.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/x509_cert_utilities.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/web_utilities.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/http_helpers.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/fileio.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/resource.h"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/SafeInt3.hpp"
    "/home/ubuntu/Desktop/casablanca/Release/src/../include/cpprest/details/http_constants.dat"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cpprest/cpprest-config.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cpprest/cpprest-config.cmake"
         "/home/ubuntu/Desktop/casablanca/Release/build.debug/src/CMakeFiles/Export/lib/cpprest/cpprest-config.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cpprest/cpprest-config-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cpprest/cpprest-config.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cpprest" TYPE FILE FILES "/home/ubuntu/Desktop/casablanca/Release/build.debug/src/CMakeFiles/Export/lib/cpprest/cpprest-config.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cpprest" TYPE FILE FILES "/home/ubuntu/Desktop/casablanca/Release/build.debug/src/CMakeFiles/Export/lib/cpprest/cpprest-config-debug.cmake")
  endif()
endif()

