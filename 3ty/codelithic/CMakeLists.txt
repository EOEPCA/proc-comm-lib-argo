
#/home/emmet/Ide/clion-2016.3/bin/cmake/bin/cmake --build /home/emmet/Projects/codelithic/cmake-build-debug --target all -- -j 4

cmake_minimum_required(VERSION 3.5.1)
project(codelithic)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

find_package(PkgConfig)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS " -Wall -fPIC")
#-DNO_FCGI

#include_directories( /home/emmet/sdk/cgicc-3.2.16/OUT/include )
#link_directories(/home/emmet/sdk/cgicc-3.2.16/OUT/lib/)


#da cancellare e mettere dinamica

#libfcgi
#include_directories(/home/emmet/Projects/CREAM/libfcgi-2.4.0.orig/OUT/include)
#link_directories(/home/emmet/Projects/CREAM/libfcgi-2.4.0.orig/OUT/lib/)

#cgicc
#include_directories(/home/emmet/Projects/CREAM/cgicc-3.2.19/OUT/include)
#set(CGICC_STATIC_LIB /home/emmet/Projects/CREAM/cgicc-3.2.19/OUT/lib/libcgicc.a)
#link_directories(/home/emmet/Projects/CREAM/cgicc-3.2.19/OUT/lib)


#set(CGICC_STATIC_LIB /usr/lib/libcgicc.a)
link_directories(/usr/lib/)


include_directories(src/codelithic/include)
include_directories(src/codelithic_sites/include)


set(FCGI_IO src/codelithic/include/codelithic/site/FCgiIO.h src/codelithic/site/FCgiIO.cpp)

set(CODELITHIC_CORE

        src/codelithic/include/codelithic/delegate/Delegate.hpp
        src/codelithic/include/codelithic/delegate/DelegateBase.hpp
        src/codelithic/include/codelithic/delegate/MultiCastDelegate.hpp

        src/codelithic/include/codelithic/site/define.hpp
        src/codelithic/site/Application.cpp
        src/codelithic/include/codelithic/site/Application.hpp

        src/codelithic/include/codelithic/site/PageNotFound.hpp src/codelithic/site/PageNotFound.cpp


        src/codelithic/include/codelithic/utils/FileUtil.hpp src/codelithic/utils/FileUtil.cpp
        src/codelithic/include/codelithic/utils/StringUtil.hpp src/codelithic/utils/StringUtil.cpp

        src/codelithic/include/codelithic/site/PageParameters.hpp src/codelithic/site/PageParameters.cpp
        #        src/codelithic/include/codelithic/site/Templates.hpp src/codelithic/site/Templates.cpp
        src/codelithic/include/codelithic/site/Controller.hpp src/codelithic/site/Controller.cpp
        src/codelithic/include/codelithic/site/Site.hpp src/codelithic/site/Site.cpp

        src/codelithic/include/codelithic/site/Entity.hpp src/codelithic/site/Entity.cpp
        src/codelithic/site/Page.cpp src/codelithic/include/codelithic/site/PageSite.hpp

        src/codelithic/site/Routes.cpp src/codelithic/include/codelithic/site/Routes.hpp
        src/codelithic/site/Services.cpp src/codelithic/include/codelithic/site/Services.hpp
        src/codelithic/site/Session.cpp src/codelithic/include/codelithic/site/Session.hpp
        src/codelithic/include/codelithic/site/Enviroments.hpp
        src/codelithic/include/codelithic/site/Logger.hpp
        src/codelithic/utils/DateUtil.cpp src/codelithic/include/codelithic/utils/DateUtil.hpp

        )

set(CODELITHIC_SITES
        src/codelithic/include/codelithic/site_ext/SiteLogger.hpp
        #        src/codelithic/include/codelithic/site_ext/SiteView.hpp src/codelithic/site_ext/SiteView.cpp


        src/codelithic/include/codelithic/site_ext/HTTPJsonHeader.hpp src/codelithic/site_ext/HTTPJsonHeader.cpp
        src/codelithic/include/codelithic/site_ext/HTTPXmlHeader.hpp src/codelithic/site_ext/HTTPXmlHeader.cpp


        src/codelithic/include/codelithic/site_ext/HTTPTextHeader.hpp src/codelithic/site_ext/HTTPTextHeader.cpp


        src/codelithic/include/codelithic/site_ext/PageSite.hpp src/codelithic/site_ext/PageSite.cpp
        #   src/codelithic/include/codelithic/site_ext/Template.hpp src/codelithic/site_ext/Template.cpp
        #   src/codelithic/site_ext/TemplateLoader.cpp src/codelithic/include/codelithic/site_ext/TemplateLoader.hpp
        #   src/codelithic/site_ext/MainView.cpp src/codelithic/include/codelithic/site_ext/MainView.hpp
        )


# set(CODELITHIC_SITES_TEST src/test/page/page.cpp)

set(LSD_VERSION_MAJOR 1)
set(LSD_VERSION_MINOR 1)
set(LSD_VERSION_PATCH 1)
set(LSD_VERSION ${LSD_VERSION_MAJOR}.${LSD_VERSION_MINOR}.${LSD_VERSION_PATCH})

#add_library(codelithic SHARED ${CODELITHIC_CORE} ${FCGI_IO} ${CODELITHIC_SITES} ${CODELITHIC_PERSISTANCE})
add_library(codelithic STATIC ${CODELITHIC_CORE} ${FCGI_IO} ${CODELITHIC_SITES} ${CODELITHIC_PERSISTANCE})
set_target_properties(codelithic PROPERTIES VERSION ${LSD_VERSION}
        SOVERSION ${LSD_VERSION_MAJOR})

#SET_TARGET_PROPERTIES(codelithic PROPERTIES IMPORTED_LOCATION ${CGICC_STATIC_LIB})
TARGET_LINK_LIBRARIES(codelithic pthread fcgi++ fcgi cgicc)

# add_executable(codelithic_test ${CODELITHIC_SITES_TEST} )
#SET_TARGET_PROPERTIES(codelithic_test PROPERTIES IMPORTED_LOCATION ${CGICC_STATIC_LIB})
# target_link_libraries(codelithic_test codelithic  pthread fcgi++ fcgi cgicc)


#add_definitions( -DNO_FCGI)
#unset(FCGI_IO)
#add_library(codelithic_cgi SHARED ${CODELITHIC_CORE} ${CODELITHIC_SITES}  ${CODELITHIC_PERSISTANCE} )
#set_target_properties(codelithic_cgi PROPERTIES VERSION ${LSD_VERSION}     SOVERSION ${LSD_VERSION_MAJOR} )
#TARGET_LINK_LIBRARIES(codelithic_cgi pthread cgicc)

#install(TARGETS codelithic DESTINATION /opt/codelithic/libs)
#install(DIRECTORY src/codelithic/include/codelithic DESTINATION /opt/codelithic/include)
#install(FILES rpm/codelithic.libconf.conf DESTINATION /etc/ld.so.conf.d)

#make distclean
set(LSD_ARC "x86_64")
set(RPM_BASE "${CMAKE_CURRENT_BINARY_DIR}/_CPack_Packages/Linux/RPM")
set(VERSION "${LSD_VERSION_MAJOR}.${LSD_VERSION_MINOR}.${LSD_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR "RPM")

set(CPACK_PACKAGE_NAME "codelithicMt")
set(CPACK_PACKAGE_RELEASE "1")
set(PACKAGE_ARC "x86_64")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-CPACKPACKAGERELEASE.el7.${PACKAGE_ARC}")
set(CPACK_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/rpm/codelithic.spec.in" "${CMAKE_CURRENT_BINARY_DIR}/codelithic.spec" @ONLY IMMEDIATE)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/rpm/buildrpm.sh" "${CMAKE_CURRENT_BINARY_DIR}/buildrpm.sh" @ONLY IMMEDIATE)
#i use my template
#set(CPACK_RPM_USER_BINARY_SPECFILE "${CMAKE_CURRENT_BINARY_DIR}/my_project.spec")
include(CPack)


