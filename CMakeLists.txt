cmake_minimum_required( VERSION 3.28 )


project( IProc CXX C ASM )

set( PROJECT_NAME IProc )
set( PROJECT_BRIEF "A dynamic library for image processing. To Extract the pixel map of the image. Support PNG, JPG, TIF and BMP image file formats. Inbuilt methods for resizing, cropping, generating grayscale and binary images." )
set( PROJECT_VERSION "0.0.1.a1" )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_C_STANDARD 23 )

if( UNIX )
    add_definitions( -fpermissive )
endif()

#include_directories( lib )
include_directories( lib/libjpeg/libjpeg-master )
include_directories( lib/libpng )
include_directories( lib/libtiff/libtiff )
include_directories( lib/libm/src/ce-libm )
#include_directories( lib/openlibm/include )
include_directories( lib/nanosvg/src )
include_directories( lib/zlib )

include_directories( IProc )

include( cmake/build_module.cmake )

# Build libjpeg
build_module( libjpeg ${PROJECT_SOURCE_DIR}/lib/jpeg-6b )
# Build zlib
build_module( zlib ${PROJECT_SOURCE_DIR}/lib/zlib )
# Build libtiff
build_module( libtiff ${PROJECT_SOURCE_DIR}/lib/libtiff )
# Build libpng
build_module( libpng ${PROJECT_SOURCE_DIR}/lib/libpng )
# Build libm
#add_subdirectory( lib/openlibm )
#build_module( libm ${PROJECT_SOURCE_DIR}/lib/libm )
add_subdirectory( lib/libm )
# Build nanosvg
set( MATH_LIBRARY m_ce )
build_module( nanosvg ${PROJECT_SOURCE_DIR}/lib/nanosvg )


include_directories( src )
file( GLOB IPROC_SRCFILES IProc/*Processor/*.cpp IProc/IProc/*.cpp )
add_library( IProc STATIC ${IPROC_SRCFILES} )
target_link_libraries( IProc jpeglib png tiff zlibstatic ${MATH_LIBRARY} )


set( ENABLE_DOC_IProc TRUE )
if( ENABLE_DOC_IProc )
	find_package(Doxygen)
	if(DOXYGEN_FOUND)
		message("-- Enabled doc_IProc target for make")
        # CMAKE_CURRENT_SOURCE_DIR is where the last call to CMake's project was,
        # CMAKE_CURRENT_BINARY_DIR is where the build of the binaries is performed
		configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
		add_custom_target(doc_IProc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMENT "Generating documentation with Doxygen")
	endif()
endif()
