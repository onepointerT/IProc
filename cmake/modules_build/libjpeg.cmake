function(build MODULE_NAME MODULE_PATH)

add_definitions( -DXMS_SUPPORTED=1 )

# Build libjpeg
set( JPEG_SOURCES ${MODULE_PATH}/jcapimin.c
        ${MODULE_PATH}/jcapistd.c
        ${MODULE_PATH}/jccoefct.c
        ${MODULE_PATH}/jccolor.c
        ${MODULE_PATH}/jcdctmgr.c
        ${MODULE_PATH}/jchuff.c
        ${MODULE_PATH}/jcinit.c
        ${MODULE_PATH}/jcmainct.c
        ${MODULE_PATH}/jcmarker.c
        ${MODULE_PATH}/jcmaster.c
        ${MODULE_PATH}/jcomapi.c
        ${MODULE_PATH}/jcparam.c
        ${MODULE_PATH}/jcphuff.c
        ${MODULE_PATH}/jcprepct.c
        ${MODULE_PATH}/jcsample.c
        ${MODULE_PATH}/jctrans.c
        ${MODULE_PATH}/jdapimin.c
        ${MODULE_PATH}/jdapistd.c
        ${MODULE_PATH}/jdatadst.c
        ${MODULE_PATH}/jdatasrc.c
        ${MODULE_PATH}/jdcoefct.c
        ${MODULE_PATH}/jdcolor.c
        ${MODULE_PATH}/jddctmgr.c
        ${MODULE_PATH}/jdhuff.c
        ${MODULE_PATH}/jdinput.c
        ${MODULE_PATH}/jdmainct.c
        ${MODULE_PATH}/jdmarker.c
        ${MODULE_PATH}/jdmaster.c
        ${MODULE_PATH}/jdmerge.c
        ${MODULE_PATH}/jdphuff.c
        ${MODULE_PATH}/jdpostct.c
        ${MODULE_PATH}/jdsample.c
        ${MODULE_PATH}/jdtrans.c
        ${MODULE_PATH}/jerror.c
        ${MODULE_PATH}/jfdctflt.c
        ${MODULE_PATH}/jfdctfst.c
        ${MODULE_PATH}/jfdctint.c
        ${MODULE_PATH}/jidctflt.c
        ${MODULE_PATH}/jidctfst.c
        ${MODULE_PATH}/jidctint.c
        ${MODULE_PATH}/jidctred.c
        ${MODULE_PATH}/jquant1.c
        ${MODULE_PATH}/jquant2.c
        ${MODULE_PATH}/jutils.c
        ${MODULE_PATH}/jmemmgr.c
#        ${MODULE_PATH}/jmemansi.c
#        ${MODULE_PATH}/jmemname.c
        ${MODULE_PATH}/jmemnobs.c
#        ${MODULE_PATH}/jmemdos.c
#        ${MODULE_PATH}/jmemmac.c
#        ${MODULE_PATH}/cjpeg.c
#        ${MODULE_PATH}/djpeg.c
#        ${MODULE_PATH}/jpegtran.c
        ${MODULE_PATH}/rdjpgcom.c
#        ${MODULE_PATH}/wrjpgcom.c
        ${MODULE_PATH}/cdjpeg.c
        ${MODULE_PATH}/rdcolmap.c
        ${MODULE_PATH}/rdswitch.c
        ${MODULE_PATH}/transupp.c
        ${MODULE_PATH}/rdppm.c
        ${MODULE_PATH}/wrppm.c
        ${MODULE_PATH}/rdgif.c
        ${MODULE_PATH}/wrgif.c
        ${MODULE_PATH}/rdtarga.c
        ${MODULE_PATH}/wrtarga.c
        ${MODULE_PATH}/rdbmp.c
        ${MODULE_PATH}/wrbmp.c
        ${MODULE_PATH}/rdrle.c
        ${MODULE_PATH}/wrrle.c )
add_library( jpeglib ${JPEG_SOURCES} )
endfunction(build MODULE_NAME MODULE_PATH)