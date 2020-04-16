#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <unordered_map>

#include <cgicc/Cgicc.h>
#include "codelithic/site/define.hpp"

#include <list>

#ifndef NO_FCGI

#include "FCgiIO.h"

#endif

#include "PageSite.hpp"

#include "PageParameters.hpp"
#include "Routes.hpp"

namespace codelithic {
namespace site {

class Controller {
 public:
  Controller();

  virtual ~Controller();

#ifndef NO_FCGI

  void setRequest(FCGX_Request &request, cgicc::Cgicc &CGI);

#else
#endif

  virtual void *parseRequest(FCGX_REQUEST &request,
                             PageParameters &pageParameter);

 private:
  //        std::unordered_map<std::string,codelithic::SitePage*>
  //        *pages=nullptr;
 public:
  // void registerPage(Page *page);

  void registerRoute(Route *route);

  unsigned long getRoutesSize();

 protected:
  Routes *routes = nullptr;
};
}  // namespace site
}  // namespace codelithic
#endif /* CONTROLLER_H */
