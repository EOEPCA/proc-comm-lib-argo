

#ifndef HAIRLANCEPAGE_H
#define HAIRLANCEPAGE_H

#include <string>
#include <vector>
#include "codelithic/site/PageParameters.hpp"
#include "codelithic/site/PageSite.hpp"
#include "codelithic/site/Routes.hpp"
//#include "Constants.h"

namespace codelithic {
namespace site {
namespace ext {

class SitePage : public codelithic::site::Page {
 public:
  SitePage();

 private:
  std::vector<codelithic::site::Route *> _rs;

 protected:
  std::vector<codelithic::site::Route *> getRoutes() override;

  void addRoute(codelithic::site::Route *r);

  virtual void prepareRoutePage() = 0;

  void htmlEncode(std::string &data);
};
}  // namespace ext
}  // namespace site
}  // namespace codelithic
#endif /* HAIRLANCEPAGE_H */

//        auto connection =
//        Codelitich::MongoDb::mongo_access::instance().get_connection(); if
//        (!connection) return false; auto db =
//        connection->database("Hairlance");