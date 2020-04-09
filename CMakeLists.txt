cmake_minimum_required(VERSION 3.15)
project(proc_comm_lib_argo)

set(CMAKE_CXX_STANDARD 17)

include_directories(includes)

set(YAML_CPP_BUILD_TESTS OFF: FORCE)
add_subdirectory(includes/yaml-cpp-yaml-cpp-0.6.3)
include_directories(includes/yaml-cpp-yaml-cpp-0.6.3/include)



set(src_main src/main.cpp
        src/api/argoworkflowapi.cpp
        includes/proc_comm_lib_argo/argoworkflowapi.hpp
        includes/proc_comm_lib_argo/application.hpp
        src/model/workflow.cpp
        src/model/workflow.hpp
        includes/nlohmann/json.hpp)



add_executable(proc_comm_lib_argo ${src_main})

target_link_libraries(proc_comm_lib_argo yaml-cpp)

add_subdirectory(tests)