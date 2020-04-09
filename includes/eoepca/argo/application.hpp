//
// Created by bla on 07/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_APPLICATION_HPP
#define PROC_COMM_LIB_ARGO_APPLICATION_HPP

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <vector>

namespace proc_comm_lib_argo {
    class Application {
        std::vector<std::string> params{};
        std::string application{""};
    public:
        Application() = default;
        Application(const Application&) = delete;
        Application(Application&&) = delete;

        ~Application() = default;
        const std::string& getApplication() const { return application; }
        void setApplication(const std::string& application) {
            Application::application = application;
        }
        void addParam(std::string pParam) { params.emplace_back(std::move(pParam)); }
        const std::vector<std::string> getParams() const { return params; }
    };
    class Run {
        std::string dockerImage{""};
        std::list<std::unique_ptr<Application>> applications{};
    public:
        Run() {}
        ~Run() {}
        void moveApplication(std::unique_ptr<Application>& theApplication) {
            if (theApplication) {
                applications.emplace_back(std::move(theApplication));
            }
        }
        const std::list<std::unique_ptr<Application>>& getApplications() const {
            return applications;
        }
        const std::string& getDockerImage() const { return dockerImage; }
        void setDockerImage(const std::string& dockerImage) {
            Run::dockerImage = dockerImage;
        }
    };
}  // namespace proc_comm_lib_argo

#endif