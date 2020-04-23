#ifndef EOEPCAARGO_EOEPCAARGO_HPP
#define EOEPCAARGO_EOEPCAARGO_HPP

#include <eoepca/IMod.hpp>
#include <eoepca/argo/application.hpp>
#include <iostream>
#include <string>
#include <list>
#include <eoepca/argo/model/workflow.hpp>
#include <proc-comm-lib-argo/api/apiconfiguration.hpp>
#include <eoepca/argo/model/apiresponse.hpp>


namespace EOEPCA {
    class EOEPCAargo : protected mods::IModInterface {
    public:
        EOEPCAargo() = delete;

        explicit EOEPCAargo(const std::string &path) : mods::IModInterface(path), create_workflow_yaml(nullptr), create_workflow_yaml_from_app(nullptr) {
            if (isValid()) {
                version = (long (*)(void)) dlsym(handle, "version");
                if (!version) {
                    setValid(false);
                    return;
                }

                // Creates a workflow yaml from run
                create_workflow_yaml = (void (*)(proc_comm_lib_argo::Run *, std::list<std::string> &)) dlsym(handle, "create_workflow_yaml");

                // Creates a workflow yaml from app
                create_workflow_yaml_from_app = (void (*)(proc_comm_lib_argo::Application *, std::string &)) dlsym(handle, "create_workflow_yaml_from_app");

                // API Methods
                list_workflows= (void (*)(std::string_view, proc_comm_lib_argo::model::WorkflowList &, std::string_view )) dlsym(handle, "list_workflows");
                get_workflow_from_name = (void (*)(std::string_view, std::string_view, proc_comm_lib_argo::model::Workflow &, std::string_view )) dlsym(handle, "get_workflow_from_name");
                submit_workflow = (void (*)(proc_comm_lib_argo::Application *, std::string_view, proc_comm_lib_argo::model::Workflow &, std::string_view )) dlsym(handle, "submit_workflow");
                delete_workflow_from_name = (void (*)(std::string_view, std::string_view, proc_comm_lib_argo::model::ApiResponse &, std::string_view )) dlsym(handle, "delete_workflow_from_name");

                if (!version) {
                    setValid(false);
                    return;
                }
            }
        }


    public:
        void ResetError() { this->resetError(); }

        bool IsValid() { return this->isValid(); }

        std::string GetLastError() {
            return std::move(std::string(this->getLastError()));
        };

    public:
        long (*version)(void);

        // Workflow generation
        void (*create_workflow_yaml)(proc_comm_lib_argo::Run *, std::list<std::string> &);
        void (*create_workflow_yaml_from_app)(proc_comm_lib_argo::Application *, std::string &);

        // Workflow api
        void (*list_workflows)(std::string_view, proc_comm_lib_argo::model::WorkflowList &, std::string_view );
        void (*get_workflow_from_name)(std::string_view, std::string_view, proc_comm_lib_argo::model::Workflow &, std::string_view );
        void (*submit_workflow)(proc_comm_lib_argo::Application *, std::string_view, proc_comm_lib_argo::model::Workflow &, std::string_view );
        void (*delete_workflow_from_name)(std::string_view, std::string_view, proc_comm_lib_argo::model::ApiResponse &, std::string_view );
    };

} // namespace EOEPCA

#endif // EOEPCAARGO_EOEPCAARGO_HPP
