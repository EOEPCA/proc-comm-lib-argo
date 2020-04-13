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
        std::map<std::string, std::string> params{};
        std::string application{""};
        std::string dockerImage{""};
    public:
        Application() = default;
        Application(const Application&) = delete;
        Application(Application&&) = delete;

        ~Application() = default;
        const std::string& getApplication() const { return application; }
        void setApplication(const std::string& application) {
            Application::application = application;
        }
        void addParam(std::string key, std::string value) { params.insert(std::make_pair(key, value)); }
        const std::map<std::string, std::string> getParams() const { return params; }
        const std::string& getDockerImage() const { return dockerImage; }
        void setDockerImage(const std::string& img) { dockerImage = img; }
    };
    class Run {
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

    };
}  // namespace proc-comm-lib-argo

#endif