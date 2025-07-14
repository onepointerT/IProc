function(build MODULE_NAME MODULE_PATH)
    set( CMAKE_CURRENT_SOURCE_DIR ${MODULE_PATH} )

    # CMake needs *.c files to do something useful
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/nanosvg.h ${MODULE_PATH}/nanosvg.c)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/nanosvgrast.h ${MODULE_PATH}/nanosvgrast.c)

    add_library(nanosvg ${MODULE_PATH}/nanosvg.c)

    set( MATH_LIBRARY m_ce )
    if(MATH_LIBRARY)
        target_link_libraries(nanosvg PUBLIC ${MATH_LIBRARY})
    endif()

    target_include_directories(nanosvg PUBLIC $<INSTALL_INTERFACE:include/nanosvg>)
    target_compile_definitions(nanosvg PRIVATE NANOSVG_IMPLEMENTATION)

    # Same for nanosvgrast
    add_library(nanosvgrast ${MODULE_PATH}/nanosvgrast.c)
    target_link_libraries(nanosvgrast PUBLIC nanosvg)
endfunction(build MODULE_NAME MODULE_PATH)