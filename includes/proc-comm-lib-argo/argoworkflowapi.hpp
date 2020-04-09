//
// Created by bla on 07/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_ARGOWORKFLOWAPI_HPP
#define PROC_COMM_LIB_ARGO_ARGOWORKFLOWAPI_HPP


#include <iostream>
#include <eoepca/argo/application.hpp>
#include <string>
#include <list>

namespace proc_comm_lib_argo {



    class argo_workflow_api {

    };


    class WorkflowUtils {


    public:
        WorkflowUtils() {};

        ~WorkflowUtils() {};


        // create workflow yaml from application class
        void  create_workflow_yaml(Run* run,std::list<std::string>& argoWorkflows);

    };
}

#endif //PROC_COMM_LIB_ARGO_ARGOWORKFLOWAPI_HPP
