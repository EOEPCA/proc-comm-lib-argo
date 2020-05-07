cmake_minimum_required(VERSION 3.10)
project(proc-comm-lib-argo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MACOSX_RPATH OFF)
set(CMAKE_CXX_FLAGS "-fPIC")


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(includes)
include_directories(3ty)

# LIBUUID
add_subdirectory(3ty/libuuid-1.0.3/uuid)
include_directories(3ty/libuuid-1.0.3)

# CODELITHIC
include_directories(3ty/codelithic/src/codelithic/include)

# YAML-CPP
set(YAML_CPP_BUILD_TESTS OFF: FORCE)
add_subdirectory(3ty/yaml-cpp-yaml-cpp-0.6.3)
include_directories(3ty/yaml-cpp-yaml-cpp-0.6.3/include)


# BEEBLEBOX
add_subdirectory(3ty/beeblebrox)
include_directories(3ty/beeblebrox/includes)


add_subdirectory(3ty/y2j-master)


set(src_main src/main.cpp )


SET(INCLUDE_LIB_SRC
        includes/eoepca/argo/eoepcaargo.hpp
        )

SET(LIB_SRC
        src/api/workflowapi.cpp
        includes/proc-comm-lib-argo/api/workflowapi.hpp
        src/api/workflowgenerator.cpp
        includes/proc-comm-lib-argo/api/workflowgenerator.hpp
        src/api/workflowutils.cpp
        includes/proc-comm-lib-argo/api/workflowutils.hpp
        src/api/apiconfiguration.cpp
        includes/proc-comm-lib-argo/api/apiconfiguration.hpp
        src/api/apiexception.cpp
        includes/eoepca/argo/model/apiexception.hpp
        includes/eoepca/argo/model/apiresponse.hpp
        includes/eoepca/argo/model/workflow.hpp
        src/eoepca_lib_argo.cpp
        includes/eoepca/argo/model/nlohmann.hpp
        )

SET(MODS_LIBS
        z m dl
        )


add_library(eoepcaargo SHARED ${INCLUDE_LIB_SRC} ${LIB_SRC})
TARGET_LINK_LIBRARIES(eoepcaargo ${MODS_LIBS}  yaml-cpp beeblebrox y2j  )

add_executable(proc-comm-lib-argo ${src_main} ${LIB_SRC})

target_link_libraries(proc-comm-lib-argo yaml-cpp beeblebrox y2j ${MODS_LIBS})


if((NOT DEFINED ENV{RUN_TESTS}) OR ($ENV{RUN_TESTS}))
    add_subdirectory(tests)
ENDIF()


