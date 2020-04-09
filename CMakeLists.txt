cmake_minimum_required(VERSION 3.10)
project(proc-comm-lib-argo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MACOSX_RPATH OFF)
set(CMAKE_CXX_FLAGS "-fPIC")

include_directories(includes)
include_directories(3ty)
set(YAML_CPP_BUILD_TESTS OFF: FORCE)
add_subdirectory(3ty/yaml-cpp-yaml-cpp-0.6.3)
include_directories(3ty/yaml-cpp-yaml-cpp-0.6.3/include)



set(src_main src/main.cpp
       )


SET(INCLUDE_LIB_SRC
        includes/eoepca/argo/eoepcaargo.hpp
        )

SET(LIB_SRC
        src/api/argoworkflowapi.cpp
        includes/proc-comm-lib-argo/argoworkflowapi.hpp
        src/model/workflow.cpp
        src/model/workflow.hpp
        src/eoepca_lib_argo.cpp
        )

SET(MODS_LIBS
        z m dl
        )


add_library(eoepcaargo SHARED ${INCLUDE_LIB_SRC} ${LIB_SRC}  )
TARGET_LINK_LIBRARIES(eoepcaargo ${MODS_LIBS}  yaml-cpp  )

add_executable(proc-comm-lib-argo ${src_main})

target_link_libraries(proc-comm-lib-argo yaml-cpp ${MODS_LIBS})

add_subdirectory(tests)