cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0058 NEW)
project(pnicore
        LANGUAGES CXX C
        VERSION 1.1.1)

include(CTest)             # - activate testing
set(CMAKE_CXX_STANDARD 11) # - we need C++11 for the entire code

include(cmake/common/InstallConfig.cmake)   #setup the install paths
include(cmake/common/OutputDirConfig.cmake) #setting up output directories for
                                            #the build
include(cmake/common/PackageConfig.cmake)   #create some basic variables for
                                            #cmake packages

include(cmake/common/EnsureBuildType.cmake)
include(cmake/common/WindowsUtils.cmake)
include(cmake/common/DoxygenUtils.cmake)
include(cmake/common/SphinxUtils.cmake)


#
# add a check target that runs the tests
#
add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} -C ${CMAKE_BUILD_TYPE})

#
#as libpnicore is in most part a template library and should thus be
#treated like a static library. In most cases all code using
#libpnicore has to be rebuilt if something in the headers is changed.
#we thus set the SO version to the package version. This is also
#the way the boost libraries are packaged.
#
set(pnicore_SO_VERSION ${pnicore_VERSION})


# =============================================================================
# on Windows we try to fetch Boost by default from Conan
# =============================================================================
set(WITH_CONAN OFF CACHE BOOL "Pull dependencies from conan repository")

if(WITH_CONAN)
    include(cmake/common/ConanSetup.cmake)
    include(conan.cmake)
    conan_cmake_run(CONANFILE conanfile.txt
                    BASIC_SETUP
                    BUILD missing)
endif()



#
# for windows we need two additional components
# - we have to build an MSI package for installation
# - we need to add a package configuration file so that the library
#   can be found with the find_package command
# the packaging is independent of the compiler used thus we have to check the
# system name.
#
if(CMAKE_SYSTEM_NAME MATCHES Windows)
    include(CPackComponent)
endif()



#======================do here some setup work=================================
include(configure/CMakeLists.txt)
include(cmake/CMakeLists.txt)



#need this to get the generated header files into the build.
add_subdirectory("src")
add_subdirectory("doc")
add_subdirectory("test")
add_subdirectory("resources")

#-----------------------------------------------------------------------------
# Configuration for the package generator
#-----------------------------------------------------------------------------
if(CMAKE_CXX_COMPILER_ID MATCHES MSVC)


    set(CPACK_GENERATOR WIX)
    set(CPACK_PACKAGE_VENDOR "DESY")
    set(CPACK_PACKAGE_VERSION_MAJOR "${pnicore_VERSION_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${pnicore_VERSION_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${pnicore_VERSION_PATCH}")


    set(CPACK_WIX_PRODUCT_ICON "resources/icon.ico")
    set(CPACK_WIX_UI_BANNER "resources/banner.bmp")
    set(CPACK_WIX_UI_DIALOG "resources/ui_dialog.bmp")
    set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING.txt")


    cpack_add_component(libraries
        DISPLAY_NAME "Libraries"
        DESCRIPTION "Runtime libraries"
        GROUP "Runtime")


    cpack_add_component(development
        DISPLAY_NAME "Development files"
        DESCRIPTION "Header files for the library"
        DEPENDS "libraries"
        GROUP "Development")

    cpack_add_component(doc_html
        DISPLAY_NAME "HTML"
        DESCRIPTION "Documentation as HTML pages"
        GROUP "Documentation")

    cpack_add_component(doc_examples
        DISPLAY_NAME "Examples"
        DESCRIPTION "Usage examples for the library"
        GROUP "Documentation")

    cpack_add_component(doc_pdf
        DISPLAY_NAME "PDF"
        DESCRIPTION "Documentation as PDF"
        GROUP "Documentation")

    cpack_add_component_group(Documentation)

    set(CPACK_WIX_CMAKE_PACKAGE_REGISTRY "pnicore")

    include(CPack)
    include(CPackWIX)
endif()
