prefix = @CMAKE_INSTALL_PREFIX@
exec_prefix = ${prefix}
includedir = ${prefix}/include
libdir = ${prefix}/@CMAKE_INSTALL_LIBDIR@

Name: pnicore
Description: PNI core library
Version: @PROJECT_VERSION@
Cflags: -I${includedir} @PNICORE_CMP_FLAGS@ 
Libs: -L${libdir} -lpnicore -lboost_program_options -lboost_regex -lboost_system
