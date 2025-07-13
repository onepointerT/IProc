function(build MODULE_NAME MODULE_PATH)
set( JPEG_LIBRARY jpeglib )
set( JPEG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/libjpeg/libjpeg-master )
set( jpeg ON )
set( ZLIB_LIBRARY zlibstatic )
set( ZLIB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/zlib )
set( TIFF_STATIC_LIBS_DEFAULT ON )
option(tiff-tools "build TIFF tools" OFF)
option(tiff-tests "build TIFF tests" OFF)
option(tiff-contrib "build TIFF contrib" OFF)
option(tiff-docs "build TIFF documentation" OFF)
option(tiff-deprecated "build TIFF deprecated features" OFF)
set( TIFF_INSTALL_DEFAULT OFF )


set( CMAKE_CURRENT_SOURCE_DIR ${MODULE_PATH} )
set( CMAKE_CURRENT_BINARY_DIR ${MODULE_PATH} )
# CMake build for libtiff
# Run "cmake" to generate the build files for your platform
#
# Copyright © 2015 Open Microscopy Environment / University of Dundee
# Copyright © 2021 Roger Leigh <rleigh@codelibre.net>
# Written by Roger Leigh <rleigh@codelibre.net>
#
# Permission to use, copy, modify, distribute, and sell this software and
# its documentation for any purpose is hereby granted without fee, provided
# that (i) the above copyright notices and this permission notice appear in
# all copies of the software and related documentation, and (ii) the names of
# Sam Leffler and Silicon Graphics may not be used in any advertising or
# publicity relating to the software without the specific, prior written
# permission of Sam Leffler and Silicon Graphics.
#
# THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
# EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
# WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
#
# IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
# ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
# OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
# LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
# OF THIS SOFTWARE.

cmake_minimum_required(VERSION 3.10)

# Default policy is from 3.10
cmake_policy(VERSION 3.10)

if(POLICY CMP0074)
  # Allow find_package() to use the ZLIB_ROOT variable, if available.
  cmake_policy(SET CMP0074 NEW)
endif()

# Find CMake modules in cmake/
list(APPEND CMAKE_MODULE_PATH "${MODULE_PATH}/cmake")

# Read version information from configure.ac.
include( ${MODULE_PATH}/cmake/AutotoolsVersion.cmake )
message(STATUS "Building tiff version ${LIBTIFF_VERSION_FULL}")

# Project definition
set(CMAKE_C_STANDARD 99)
project(tiff
        VERSION "${LIBTIFF_VERSION}"
        LANGUAGES C CXX)

if(NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  # libtiff is being included as a subproject of some other project.
  set(TIFF_INSTALL_DEFAULT OFF)
else()
  set(TIFF_INSTALL_DEFAULT ON)
  option(BUILD_SHARED_LIBS "Build shared libraries" ON)
endif()

if (BUILD_SHARED_LIBS)
  set(TIFF_STATIC_LIBS_DEFAULT FALSE)
else()
  set(TIFF_STATIC_LIBS_DEFAULT TRUE)
 endif()

option(tiff-static "build TIFF static libraries" ${TIFF_STATIC_LIBS_DEFAULT})
option(tiff-tools "build TIFF tools" ON)
option(tiff-tests "build TIFF tests" ON)
option(tiff-contrib "build TIFF contrib" ON)
option(tiff-docs "build TIFF documentation" ON)
option(tiff-deprecated "build TIFF deprecated features" OFF)
option(tiff-install "install TIFF targets" ${TIFF_INSTALL_DEFAULT})

if (tiff-static)
  set(TIFF_BUILD_LIB_VALUE STATIC)
else()
  set(TIFF_BUILD_LIB_VALUE SHARED)
endif()

# Disable deprecated features to ensure clean build
if (tiff-deprecated)
  add_definitions(-DTIFF_DISABLE_DEPRECATED)
endif()

# Autotools compatibility
include( ${MODULE_PATH}/cmake/AutotoolsCompat.cmake )

# Compiler checks (warning flags, etc.)
include( ${MODULE_PATH}/cmake/CompilerChecks.cmake )

# Linker checks (version script, etc.)
include( ${MODULE_PATH}/cmake/LinkerChecks.cmake )

# Processor checks (endianness, fill order, floating point, etc.)
include( ${MODULE_PATH}/cmake/ProcessorChecks.cmake )

# Checks for headers
include( ${MODULE_PATH}/cmake/IncludeChecks.cmake )

# Checks for functions and other symbols
include( ${MODULE_PATH}/cmake/SymbolChecks.cmake )

# Standard installation paths
include(GNUInstallDirs)
# Documentation install directory (default to cmake project docdir)
set(LIBTIFF_DOCDIR "${CMAKE_INSTALL_DOCDIR}")

# CTest testing
enable_testing()

# Checks for type presence and size
include( ${MODULE_PATH}/cmake/TypeSizeChecks.cmake )

# Check for POSIX Large File Support (LFS)
include( ${MODULE_PATH}/cmake/LargeFileSupport.cmake )

# Options for internal codec support
include( ${MODULE_PATH}/cmake/InternalCodecs.cmake )

# Check for Deflate codec
include( ${MODULE_PATH}/cmake/DeflateCodec.cmake )

# Check for PixarLog codec
include( ${MODULE_PATH}/cmake/PixarLogCodec.cmake )

# Check for JPEG codec
include( ${MODULE_PATH}/cmake/JPEGCodec.cmake )

# Check for JBIG codec
include( ${MODULE_PATH}/cmake/JBIGCodec.cmake )

# Check for LERC codec
include( ${MODULE_PATH}/cmake/LERCCodec.cmake )

# Check for LZMA codec
include( ${MODULE_PATH}/cmake/LZMACodec.cmake )

# Check for ZSTD codec
include( ${MODULE_PATH}/cmake/ZSTDCodec.cmake )

# Check for WebP codec
include( ${MODULE_PATH}/cmake/WebPCodec.cmake )

# Option for C++ libtiffxx library
include( ${MODULE_PATH}/cmake/CXXLibrary.cmake )

# Checks for OpenGL support
include( ${MODULE_PATH}/cmake/OpenGLChecks.cmake )

# Windows support
include( ${MODULE_PATH}/cmake/WindowsSupport.cmake )

# Orthogonal features
include( ${MODULE_PATH}/cmake/LibraryFeatures.cmake )


# math.h/libm portability
find_package(CMath REQUIRED)

# Release support
include( ${MODULE_PATH}/cmake/Release.cmake )

# Process subdirectories
# CMake build for libtiff
#
# Copyright © 2015 Open Microscopy Environment / University of Dundee
# Written by Roger Leigh <rleigh@codelibre.net>
#
# Permission to use, copy, modify, distribute, and sell this software and
# its documentation for any purpose is hereby granted without fee, provided
# that (i) the above copyright notices and this permission notice appear in
# all copies of the software and related documentation, and (ii) the names of
# Sam Leffler and Silicon Graphics may not be used in any advertising or
# publicity relating to the software without the specific, prior written
# permission of Sam Leffler and Silicon Graphics.
#
# THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
# EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
# WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
#
# IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
# ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
# OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
# LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
# OF THIS SOFTWARE.

set( CMAKE_CURRENT_SOURCE_DIR ${MODULE_PATH}/port )
set( CMAKE_CURRENT_BINARY_DIR ${MODULE_PATH}/port )

# Generate headers
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libport_config.h.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/libport_config.h
        @ONLY)

set(port_HEADERS libport.h)

# Only build if any needed features are missing
if(NOT HAVE_GETOPT)
  add_library(tiff_port STATIC ${MODULE_PATH}/placeholder.h)

  # Add getopt if missing
  if(NOT HAVE_GETOPT)
    target_sources(tiff_port PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/getopt.c)
  endif()

  target_include_directories(tiff_port PUBLIC
          ${CMAKE_CURRENT_BINARY_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR})
else()
  # Dummy interface library
  add_library(tiff_port INTERFACE)
  target_include_directories(tiff_port INTERFACE
          ${CMAKE_CURRENT_BINARY_DIR}
          ${CMAKE_CURRENT_SOURCE_DIR})
endif()


# Process subdirectories
# CMake build for libtiff
#
# Copyright © 2015 Open Microscopy Environment / University of Dundee
# Written by Roger Leigh <rleigh@codelibre.net>
#
# Permission to use, copy, modify, distribute, and sell this software and
# its documentation for any purpose is hereby granted without fee, provided
# that (i) the above copyright notices and this permission notice appear in
# all copies of the software and related documentation, and (ii) the names of
# Sam Leffler and Silicon Graphics may not be used in any advertising or
# publicity relating to the software without the specific, prior written
# permission of Sam Leffler and Silicon Graphics.
#
# THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
# EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
# WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
#
# IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
# ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
# OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
# LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
# OF THIS SOFTWARE.

set( CMAKE_CURRENT_SOURCE_DIR ${MODULE_PATH}/libtiff )
set( CMAKE_CURRENT_BINARY_DIR ${MODULE_PATH}/libtiff )

# Generate headers
# and update configuration settings and package / version information.
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tif_config.h.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/tif_config.h
               @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tiffconf.h.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/tiffconf.h
               @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tiffvers.h.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/tiffvers.h
               @ONLY)

set(tiff_public_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/tiff.h
        ${CMAKE_CURRENT_SOURCE_DIR}/tiffio.h
        ${CMAKE_CURRENT_BINARY_DIR}/tiffvers.h
        ${CMAKE_CURRENT_BINARY_DIR}/tiffconf.h)

set(tiff_private_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/t4.h
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_dir.h
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_predict.h
        ${CMAKE_CURRENT_SOURCE_DIR}/tiffiop.h
        ${CMAKE_CURRENT_SOURCE_DIR}/uvcode.h
        ${CMAKE_CURRENT_BINARY_DIR}/tif_config.h)


add_library(tiff ${TIFF_BUILD_LIB_VALUE} ${MODULE_PATH}/libtiff/libtiff.def)
add_library(TIFF::tiff ALIAS tiff)

target_sources(tiff PRIVATE
        ${tiff_public_HEADERS}
        ${tiff_private_HEADERS}
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_aux.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_close.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_codec.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_color.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_compress.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_dir.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_dirinfo.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_dirread.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_dirwrite.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_dumpmode.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_error.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_extension.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_fax3.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_fax3sm.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_flush.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_getimage.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_hash_set.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_jbig.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_jpeg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_jpeg_12.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_lerc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_luv.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_lzma.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_lzw.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_next.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_ojpeg.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_open.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_packbits.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_pixarlog.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_predict.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_print.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_read.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_strip.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_swab.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_thunder.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_tile.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_version.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_warning.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_webp.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_write.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_zip.c
        ${CMAKE_CURRENT_SOURCE_DIR}/tif_zstd.c)

if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.16)
  set_property(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/tif_jpeg.c ${CMAKE_CURRENT_SOURCE_DIR}/tif_jpeg12.c PROPERTY SKIP_UNITY_BUILD_INCLUSION ON)
endif ()

# For all files (but tif_open.c, tif_unix.c and tif_win32.c), forbid the use
# of _TIFFmalloc/_TIFFfree and require the use of their "Ext" versions
target_compile_definitions(tiff PRIVATE TIFF_DO_NOT_USE_NON_EXT_ALLOC_FUNCTIONS)
set_property(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/tif_open.c APPEND PROPERTY COMPILE_DEFINITIONS ALLOW_TIFF_NON_EXT_ALLOC_FUNCTIONS)

if(USE_WIN32_FILEIO)
  target_sources(tiff PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tif_win32.c)
  set_property(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/tif_win32.c APPEND PROPERTY COMPILE_DEFINITIONS ALLOW_TIFF_NON_EXT_ALLOC_FUNCTIONS)
else()
  target_sources(tiff PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tif_unix.c)
  set_property(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/tif_unix.c APPEND PROPERTY COMPILE_DEFINITIONS ALLOW_TIFF_NON_EXT_ALLOC_FUNCTIONS)
endif()

target_include_directories(tiff
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${TIFF_INCLUDES}
)

# Windows specific resource preparation
if (WIN32)
  message(STATUS "Include resource version information for LibTIFF")
  target_sources(tiff PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tif_win32_versioninfo.rc)
  source_group("Resource Files" FILES ${CMAKE_CURRENT_SOURCE_DIR}/tif_win32_versioninfo.rc)
endif ()


set(tiff_libs_private_list "") # cmake list
set(tiff_requires_private "") # cmake string

if(ZIP_SUPPORT)
  target_link_libraries(tiff PRIVATE ZLIB::ZLIB)
  string(APPEND tiff_requires_private " zlib")
endif()
if(ZIP_SUPPORT AND LIBDEFLATE_SUPPORT)
  target_link_libraries(tiff PRIVATE Deflate::Deflate)
  if(Deflate_VERSION_STRING VERSION_GREATER_EQUAL "1.9")
    string(APPEND tiff_requires_private " libdeflate")
  else()
    list(APPEND tiff_libs_private_list "${Deflate_LIBRARY}")
  endif()
endif()
if(JPEG_SUPPORT)
  target_link_libraries(tiff PRIVATE JPEG::JPEG)
  string(APPEND tiff_requires_private " libjpeg")
  if(JPEG_DUAL_MODE_8_12 AND NOT HAVE_JPEGTURBO_DUAL_MODE_8_12)
    target_include_directories(tiff PRIVATE ${JPEG12_INCLUDE_DIR})
    target_link_libraries(tiff PRIVATE ${JPEG12_LIBRARIES})
  endif()
endif()
if(JBIG_SUPPORT)
  target_link_libraries(tiff PRIVATE JBIG::JBIG)
  list(APPEND tiff_libs_private_list "${JBIG_LIBRARY}")
endif()
if(LERC_SUPPORT)
  target_link_libraries(tiff PRIVATE LERC::LERC)
  if(LERC_VERSION_STRING VERSION_GREATER_EQUAL "4.0")
    string(APPEND tiff_requires_private " Lerc")
  else()
    list(APPEND tiff_libs_private_list "${LERC_LIBRARY}")
  endif()
endif()
if(LZMA_SUPPORT)
  target_link_libraries(tiff PRIVATE liblzma::liblzma)
  string(APPEND tiff_requires_private " liblzma")
endif()
if(ZSTD_SUPPORT)
  target_link_libraries(tiff PRIVATE ZSTD::ZSTD)
  string(APPEND tiff_requires_private " libzstd")
endif()
if(WEBP_SUPPORT)
  target_link_libraries(tiff PRIVATE WebP::webp)
  string(APPEND tiff_requires_private " libwebp")
endif()
if(CMath_LIBRARY)
  target_link_libraries(tiff PRIVATE CMath::CMath)
  list(APPEND tiff_libs_private_list "${CMath_LIBRARY}")
endif()

set(tiff_libs_private_list "${tiff_libs_private_list}" PARENT_SCOPE)
set(tiff_requires_private "${tiff_requires_private}" PARENT_SCOPE)

set_target_properties(tiff PROPERTIES SOVERSION ${SO_COMPATVERSION})
if(NOT CYGWIN)
    # This property causes shared libraries on Linux to have the full version
    # encoded into their final filename.  We disable this on Cygwin because
    # it causes cygz-${TIFF_FULL_VERSION}.dll to be created when cygz.dll
    # seems to be the default.
    set_target_properties(tiff PROPERTIES VERSION ${SO_VERSION})
endif()
if(HAVE_LD_VERSION_SCRIPT)
  if (CMAKE_VERSION GREATER_EQUAL 3.29 AND CMAKE_C_COMPILER_LINKER_ID STREQUAL "LLD" AND CMAKE_C_COMPILER_LINKER_VERSION GREATER_EQUAL 17)
    set_target_properties(tiff PROPERTIES LINK_FLAGS
                              "-Wl,--undefined-version -Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/libtiff.map")
  else()
    set_target_properties(tiff PROPERTIES LINK_FLAGS
                              "-Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/libtiff.map")
  endif()
endif()

if(tiff-install)
  export(TARGETS tiff NAMESPACE TIFF:: FILE "${CMAKE_CURRENT_BINARY_DIR}/libtiffTargets.cmake")
  install(TARGETS tiff EXPORT TiffTargets
          RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
          LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
          ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

  install(FILES ${tiff_public_HEADERS}
          DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

  set(TIFF_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/tiff)
  install(EXPORT TiffTargets
          FILE TiffTargets.cmake
          NAMESPACE TIFF::
          DESTINATION ${TIFF_CONFIGDIR}
  )

  include( ${MODULE_PATH}/cmake/CMakePackageConfigHelpers)
  write_basic_package_version_file(
    TiffConfigVersion.cmake
    VERSION ${LIBTIFF_VERSION}
    COMPATIBILITY SameMajorVersion)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/TiffConfigVersion.cmake DESTINATION ${TIFF_CONFIGDIR})

  configure_file(${PROJECT_SOURCE_DIR}/cmake/TiffConfig.cmake.in
                 ${CMAKE_CURRENT_BINARY_DIR}/TiffConfig.cmake @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/TiffConfig.cmake DESTINATION ${TIFF_CONFIGDIR})
endif()

if(CXX_SUPPORT)
  set(tiffxx_HEADERS
          ${CMAKE_CURRENT_SOURCE_DIR}/tiffio.hxx)

  # No .def file for this library.
  if (WIN32 AND NOT MINGW)
      add_library(tiffxx STATIC ${MODULE_PATH}/placeholder.h)
  else()
      add_library(tiffxx ${TIFF_BUILD_LIB_VALUE} ${MODULE_PATH}/placeholder.h)
  endif()

  add_library(TIFF::CXX ALIAS tiffxx)

  target_sources(tiffxx PRIVATE
          ${tiffxx_HEADERS}
          ${CMAKE_CURRENT_SOURCE_DIR}/tif_stream.cxx)
  target_link_libraries(tiffxx tiff)
  set_target_properties(tiffxx PROPERTIES SOVERSION ${SO_COMPATVERSION})
  if(NOT CYGWIN)
    # This property causes shared libraries on Linux to have the full version
    # encoded into their final filename.  We disable this on Cygwin because
    # it causes cygz-${TIFF_FULL_VERSION}.dll to be created when cygz.dll
    # seems to be the default.
    set_target_properties(tiffxx PROPERTIES VERSION ${SO_VERSION})
  endif()
  if(HAVE_LD_VERSION_SCRIPT)
    set_target_properties(tiffxx PROPERTIES LINK_FLAGS
                          "-Wl,--version-script=${CMAKE_CURRENT_SOURCE_DIR}/libtiffxx.map")
  endif()

  if(tiff-install)
    install(TARGETS tiffxx EXPORT TiffTargets
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

    install(FILES ${tiffxx_HEADERS}
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
  endif()

endif()

# pkg-config support
#include( ${MODULE_PATH}/cmake/${PROJECT_SOURCE_DIR}/cmake/modules_build/libtiff/PkgConfig.cmake)

message(STATUS "")
message(STATUS "Libtiff is now configured for ${CMAKE_SYSTEM}")
message(STATUS "")
if (NOT LIBTIFF_RELEASE_VERSION STREQUAL LIBTIFF_VERSION_FULL)
  message(STATUS "  Libtiff release version      ${LIBTIFF_RELEASE_VERSION} is not equal to build version!")
endif()
message(STATUS "  Libtiff build version:       ${LIBTIFF_VERSION_FULL}")
message(STATUS "  Libtiff library version:     ${SO_VERSION}")
message(STATUS "  Libtiff release date:        ${LIBTIFF_RELEASE_DATE}")
message(STATUS "")
message(STATUS "  Installation directory:             ${prefix}")
message(STATUS "  Documentation directory:            ${LIBTIFF_DOCDIR}")
message(STATUS "  C compiler:                         ${CMAKE_C_COMPILER}")
message(STATUS "  C++ compiler:                       ${CMAKE_CXX_COMPILER}")
message(STATUS "  Build shared libraries:             ${BUILD_SHARED_LIBS}")
message(STATUS "  Build tools:                        ${tiff-tools}")
message(STATUS "  Build tests:                        ${tiff-tests}")
message(STATUS "  Build contrib:                      ${tiff-contrib}")
message(STATUS "  Build docs:                         ${tiff-docs}")
message(STATUS "  Build deprecated features:          ${tiff-deprecated}")
message(STATUS "  Enable linker symbol versioning:    ${HAVE_LD_VERSION_SCRIPT}")
message(STATUS "  Support Microsoft Document Imaging: ${mdi}")
message(STATUS "  Use win32 IO:                       ${USE_WIN32_FILEIO}")
message(STATUS "")
message(STATUS " Support for internal codecs:")
message(STATUS "  CCITT Group 3 & 4 algorithms:       ${ccitt}")
message(STATUS "  Macintosh PackBits algorithm:       ${packbits}")
message(STATUS "  LZW algorithm:                      ${lzw}")
message(STATUS "  ThunderScan 4-bit RLE algorithm:    ${thunder}")
message(STATUS "  NeXT 2-bit RLE algorithm:           ${next}")
message(STATUS "  LogLuv high dynamic range encoding: ${logluv}")
message(STATUS "")
message(STATUS " Support for external codecs:")
message(STATUS "  ZLIB support:                       Requested:${zlib} Availability:${ZLIB_FOUND} Support:${ZLIB_SUPPORT}")
if(ZLIB_SUPPORT)
  message(STATUS "  libdeflate support:                 Requested:${libdeflate} Availability:${DEFLATE_FOUND} Support:${LIBDEFLATE_SUPPORT}")
else()
  message(STATUS "  libdeflate support:                 Requested:${libdeflate} Availability:${DEFLATE_FOUND} Support:${LIBDEFLATE_SUPPORT} (Depends on ZLIB Support)")
endif()
if(ZLIB_SUPPORT)
  message(STATUS "  Pixar log-format algorithm:         Requested:${pixarlog} Availability:${ZLIB_FOUND} Support:${PIXARLOG_SUPPORT}")
else()
  message(STATUS "  Pixar log-format algorithm:         Requested:${pixarlog} Availability:${ZLIB_FOUND} Support:${PIXARLOG_SUPPORT} (Depends on ZLIB Support)")
endif()
message(STATUS "  JPEG support:                       Requested:${jpeg} Availability:${JPEG_FOUND} Support:${JPEG_SUPPORT}")
if(JPEG_SUPPORT)
  message(STATUS "  Old JPEG support:                   Requested:${old-jpeg} Availability:${JPEG_SUPPORT} Support:${OJPEG_SUPPORT}")
else()
  message(STATUS "  Old JPEG support:                   Requested:${old-jpeg} Availability:${JPEG_SUPPORT} Support:${OJPEG_SUPPORT} (Depends on JPEG Support)")
endif()
if(JPEG_SUPPORT AND HAVE_JPEGTURBO_DUAL_MODE_8_12)
  message(STATUS "  JPEG 8/12 bit dual mode:            Support: yes (libjpeg turbo >= 3.0 dual mode)")
else()
  message(STATUS "  JPEG 8/12 bit dual mode:            Requested:${jpeg12} Availability:${JPEG12_FOUND} Support:${JPEG_DUAL_MODE_8_12}")
endif()
message(STATUS "  ISO JBIG support:                   Requested:${jbig} Availability:${JBIG_FOUND} Support:${JBIG_SUPPORT}")
if(ZLIB_SUPPORT)
  message(STATUS "  LERC support:                       Requested:${lerc} Availability:${LERC_FOUND} Support:${LERC_SUPPORT}")
else()
  message(STATUS "  LERC support:                       Requested:${lerc} Availability:${LERC_FOUND} Support:${LERC_SUPPORT} (Depends on ZLIB Support)")
endif()
message(STATUS "  LZMA2 support:                      Requested:${lzma} Availability:${liblzma_FOUND} Support:${LZMA_SUPPORT}")
message(STATUS "  ZSTD support:                       Requested:${zstd} Availability:${ZSTD_USABLE} Support:${ZSTD_SUPPORT}")
message(STATUS "  WEBP support:                       Requested:${webp} Availability:${WebP_FOUND} Support:${WEBP_SUPPORT}")
message(STATUS "")
message(STATUS "  C++ support:                        ${tiff-cxx} (requested) ${CXX_SUPPORT} (availability)")
message(STATUS "")
# message(STATUS "  X Athena Widgets support:           ${HAVE_XAW}")
message(STATUS "  OpenGL support:                     Requested:${tiff-opengl} Availability:${HAVE_OPENGL} Support:${OPENGL_SUPPORT}")
message(STATUS "")


endfunction(build MODULE_NAME MODULE_PATH)