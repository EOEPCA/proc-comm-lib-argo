cmake_minimum_required(VERSION 3.5)
project(beeblebrox)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MACOSX_RPATH OFF)

set(CMAKE_CXX_FLAGS "-fPIC")

SET(requiredlibs)

FIND_PACKAGE(CURL)

IF(CURL_FOUND)
    INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
    SET(requiredlibs ${requiredlibs} ${CURL_LIBRARIES} )
ELSE(CURL_FOUND)
    MESSAGE(FATAL_ERROR "Could not find the CURL library and development files.")
ENDIF(CURL_FOUND)



include_directories("includes")

SET(BEEBLEBROX_COMMON_FILES
        includes/beeblebrox/routes/FactoryRoutes.hpp
        #		sources/beeblebrox/FactoryRoutes.cpp
        includes/beeblebrox/INIReader.hpp
        includes/beeblebrox/Uuid.hpp
        includes/beeblebrox/Sha1.hpp sources/beeblebrox/Sha1.cpp
        includes/beeblebrox/uri.hpp sources/beeblebrox/uri.cpp
        includes/beeblebrox/auth.hpp
        includes/beeblebrox/httpcontentstring.hpp
        includes/beeblebrox/httpresponsestring.hpp
        includes/beeblebrox/httpresponsestream.hpp
        includes/beeblebrox/httpcontentdockerstdin.hpp
        includes/beeblebrox/httpresponsevnddockerrawstream.hpp
        includes/beeblebrox/httpcontentfile.hpp
        includes/beeblebrox/authuserpassword.hpp
        #		sources/beeblebrox/authuserpassword.cpp
        includes/beeblebrox/identifier.hpp
        #		sources/beeblebrox/identifier.cpp
        includes/beeblebrox/httpresponsefile.hpp
        #        sources/beeblebrox/httpresponsefile.cpp
        includes/beeblebrox/stringutil.hpp sources/beeblebrox/stringutil.cpp
        # includes/beeblebrox/entities/entity.hpp
        includes/beeblebrox/query.hpp
        includes/beeblebrox/httpresponse.hpp
        includes/beeblebrox/define.hpp
        includes/beeblebrox/Logfile.hpp
        #		sources/beeblebrox/Logfile.cpp

        includes/beeblebrox/cookie.hpp
        )


SET(BEEBLEBROX_HANDS_FILES
        includes/zaphodhands/uridocker.hpp
        includes/zaphodhands/zaphodhand.hpp
        includes/zaphodhands/zaphodhanddocker.hpp
        includes/zaphodhands/zaphodhandftp.hpp
        includes/zaphodhands/hand.hpp
        )

SET(MAIN_FILE

        sources/beeblebrox/main.cpp
        )

#set(LSD_VERSION_MAJOR 1)
#set(LSD_VERSION_MINOR 1)
#set(LSD_VERSION_PATCH 1)
#set(LSD_VERSION ${LSD_VERSION_MAJOR}.${LSD_VERSION_MINOR}.${LSD_VERSION_PATCH})
#
#add_library(codelithic SHARED ${CODELITHIC_CORE} ${FCGI_IO} ${CODELITHIC_SITES} ${CODELITHIC_PERSISTANCE})
#set_target_properties(codelithic PROPERTIES VERSION ${LSD_VERSION}
#        SOVERSION ${LSD_VERSION_MAJOR})
#
##SET_TARGET_PROPERTIES(codelithic PROPERTIES IMPORTED_LOCATION ${CGICC_STATIC_LIB})
#TARGET_LINK_LIBRARIES(codelithic pthread fcgi++ fcgi cgicc)


add_library(beeblebrox STATIC ${BEEBLEBROX_COMMON_FILES} ${BEEBLEBROX_HANDS_FILES})
TARGET_LINK_LIBRARIES(beeblebrox  ${requiredlibs} uuid pthread)#
#${MAIN_FILE} codelithic

add_executable(testxx ${MAIN_FILE})
#${BEEBLEBROX_COMMON_FILES}
TARGET_LINK_LIBRARIES(testxx beeblebrox )
#codelithic

# include(CPack)
# install(DIRECTORY Templates/beeblebrox DESTINATION /var/www/html/Templates/beeblebrox)

