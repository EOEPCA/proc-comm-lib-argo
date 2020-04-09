#ifndef EOEPCAARGO_EOEPCAARGO_HPP
#define EOEPCAARGO_EOEPCAARGO_HPP

#include <eoepca/IMod.hpp>
#include <eoepca/argo/application.hpp>
#include <iostream>
#include <string>
#include <list>


namespace EOEPCA {
class EOEPCAargo : protected mods::IModInterface {
public:
  EOEPCAargo() = delete;
  explicit EOEPCAargo(const std::string &path) : mods::IModInterface(path),create_workflow_yaml(nullptr) {
    if (isValid()) {
      version = (long (*)(void))dlsym(handle, "version");
      if (!version) {
        setValid(false);
          std::cout<<"hello1\n";
        return;
      }

      create_workflow_yaml = (std::list<std::string>  (*)(proc_comm_lib_argo::Run *))dlsym(handle, "create_workflow_yaml");
      if (!version) {
        setValid(false);
        std::cout<<"hello2\n";
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
  std::list<std::string> (*create_workflow_yaml)(proc_comm_lib_argo::Run *);
};

} // namespace EOEPCA

#endif // EOEPCAARGO_EOEPCAARGO_HPP
