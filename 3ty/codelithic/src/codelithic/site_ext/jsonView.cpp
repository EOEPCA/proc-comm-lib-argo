
#include "codelithic/site_ext/jsonView.h"
#include "codelithic/site_ext/HTTPJsonHeader.hpp"
#include "codelithic/site_ext/codelithic_site_define.hpp"

namespace codelithic {
namespace site {
namespace ext {

jsonView::jsonView(std::string content) : ViewContent(std::move(content)) {}

cgicc::HTTPHeader *jsonView::getMyHeader() { return new HTTPJsonHeader{}; }

}  // namespace ext
}  // namespace site
}  // namespace codelithic
