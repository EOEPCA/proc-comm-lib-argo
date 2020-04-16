
#ifndef JSONVIEW_H
#define JSONVIEW_H

#include "codelithic/site/View.hpp"

namespace codelithic {
namespace site {
namespace ext {

class jsonView : public codelithic::site::ViewContent {
 public:
  explicit jsonView(std::string content);

 private:
 protected:
  cgicc::HTTPHeader *getMyHeader() override;
};
}  // namespace ext
}  // namespace site
}  // namespace codelithic
#endif /* JSONVIEW_H */
