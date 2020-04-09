//
// Created by bla on 07/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_ARGOWORKFLOWAPI_HPP
#define PROC_COMM_LIB_ARGO_ARGOWORKFLOWAPI_HPP



#include <iostream>
#include "application.hpp"


namespace proc_comm_lib_argo {



    class argo_workflow_api {

    };


    class WorkflowUtils {


    public:
        WorkflowUtils() {};

        ~WorkflowUtils() {};


        // creat workflow yaml from application class
        std::string create_workflow_yaml(Run* run);
        //std::string create_workflow_yaml();
    };
}

#endif //PROC_COMM_LIB_ARGO_ARGOWORKFLOWAPI_HPP
