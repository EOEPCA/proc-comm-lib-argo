#ifndef BEEBLEBROX_FACTORYROUTES_HPP
#define BEEBLEBROX_FACTORYROUTES_HPP

#include <memory>
#include <vector>

#include "codelithic/site/Routes.hpp"

namespace Beeblebrox {
namespace Routes {

class FactoryRoutes {
 public:
  FactoryRoutes() = default;
  virtual ~FactoryRoutes() = default;

  const std::vector<std::unique_ptr<codelithic::site::Route>>& getRoutes()
      const {
    return routes;
  }

  virtual void prepareRoutes() = 0;

 protected:
  std::vector<std::unique_ptr<codelithic::site::Route>> routes;
};
}  // namespace Routes
}  // namespace Beeblebrox

#endif  // BEEBLEBROX_FACTORYROUTES_HPP