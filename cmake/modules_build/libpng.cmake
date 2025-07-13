function(build MODULE_NAME MODULE_PATH)
    set( ZLIB_LIBRARY zlibstatic )
    set( ZLIB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/zlib )

    file( GLOB PNG_SOURCES ${MODULE_PATH}/*.c )
    add_library( png ${PNG_SOURCES} )
    target_link_libraries( png zlibstatic )
endfunction(build MODULE_NAME MODULE_PATH)
