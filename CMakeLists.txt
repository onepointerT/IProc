cmake_minimum_required( VERSION 3.28 )


project( IProc CXX C )

set( PROJECT_NAME IProc )
set( PROJECT_BRIEF "A dynamic library for image processing. To Extract the pixel map of the image. Support PNG, JPG, TIF and BMP image file formats. Inbuilt methods for resizing, cropping, generating grayscale and binary images." )
set( PROJECT_VERSION "0.0.1.a1" )

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_C_STANDARD 23 )

if( UNIX )
    add_definitions( -fpermissive )
endif()

include_directories( lib )
include_directories( lib/libjpeg/libjpeg-master )
include_directories( lib/libpng )
include_directories( lib/libtiff/libtiff )
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


include_directories( src )
file( GLOB IPROC_SRCFILES IProc/*Processor/*.cpp IProc/IProc/*.cpp )
add_library( IProc STATIC ${IPROC_SRCFILES} )
target_link_libraries( IProc jpeglib png tiff zlibstatic )
