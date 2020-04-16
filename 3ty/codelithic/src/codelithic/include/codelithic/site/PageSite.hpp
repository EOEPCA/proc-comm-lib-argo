

#ifndef PAGE_H
#define PAGE_H

#include <vector>

#include "Routes.hpp"

namespace codelithic {

namespace site {

class Page {
 public:
  Page();

  virtual ~Page();

  virtual std::vector<Route *> getRoutes() = 0;

 protected:
 private:
};
}  // namespace site
}  // namespace codelithic
#endif /* PAGE_H */
