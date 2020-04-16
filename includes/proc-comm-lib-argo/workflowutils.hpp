//
// Created by bla on 15/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_WORKFLOWUTILS_HPP
#define PROC_COMM_LIB_ARGO_WORKFLOWUTILS_HPP

namespace proc_comm_lib_argo {

    class Workflow_utils {
    public:
        static std::string convertYamlToJson(std::string_view yaml);
        static std::string prettyPrintJson(std::string_view json);

    private:
        // Disallow creating an instance of this object
        Workflow_utils();
    };

}

#endif //PROC_COMM_LIB_ARGO_WORKFLOWUTILS_HPP
