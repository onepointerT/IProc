function(build_with_cmake MODULE_NAME MODULE_PATH)
    build(${MODULE_NAME} "${MODULE_PATH}")
endfunction()

function(build_module MODULE_NAME MODULE_PATH)
    include("${PROJECT_SOURCE_DIR}/cmake/modules_build/${MODULE_NAME}.cmake")
    build_with_cmake(${MODULE_NAME} ${MODULE_PATH})
endfunction(build_module MODULE_NAME) 