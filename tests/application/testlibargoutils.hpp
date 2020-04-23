//
// Created by bla on 23/04/20.
//

#ifndef PROC_COMM_LIB_ARGO_TESTLIBARGOUTILS_HPP
#define PROC_COMM_LIB_ARGO_TESTLIBARGOUTILS_HPP

#include <eoepca/argo/eoepcaargo.hpp>
#include <memory>

namespace testing {
    class TestLibArgoUtils {
    public:
        std::unique_ptr<EOEPCA::EOEPCAargo> static getLibArgo() {
            auto lib = std::make_unique<EOEPCA::EOEPCAargo>("./cmake-build-debug/libeoepcaargo.so");
            if (!lib->IsValid()) {
                lib = std::make_unique<EOEPCA::EOEPCAargo>("/project/build/libeoepcaargo.so");
            }
            if (!lib->IsValid()) {
                std::cout << "Library not found\n";
                return nullptr;
            }
            return lib;
        }
    };
}

#endif //PROC_COMM_LIB_ARGO_TESTLIBARGOUTILS_HPP
