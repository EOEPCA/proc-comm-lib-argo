cmake_minimum_required(VERSION 3.10)
project(proc_comm_lib_argo)

set(CMAKE_CXX_STANDARD 17)

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
        includes/proc_comm_lib_argo/argoworkflowapi.hpp
        src/model/workflow.cpp
        src/model/workflow.hpp
        src/eoepca_lib_argo.cpp
        )

SET(MODS_LIBS
        z m dl
        )


add_library(eoepcaargo SHARED ${INCLUDE_LIB_SRC} ${LIB_SRC}  )
TARGET_LINK_LIBRARIES(eoepcaargo ${MODS_LIBS}  )

add_executable(proc_comm_lib_argo ${src_main})

target_link_libraries(proc_comm_lib_argo yaml-cpp ${MODS_LIBS})

add_subdirectory(tests)