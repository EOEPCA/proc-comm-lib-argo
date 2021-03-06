

#include "codelithic/site_ext/PageSite.hpp"

namespace codelithic {

namespace site {
namespace ext {

SitePage::SitePage() {}

std::vector<codelithic::site::Route *> SitePage::getRoutes() {
  prepareRoutePage();
  return _rs;
}

void SitePage::addRoute(site::Route *r) { _rs.push_back(r); }

void SitePage::htmlEncode(std::string &data) {
  std::string buffer;
  buffer.reserve(data.size());
  for (size_t pos = 0; pos != data.size(); ++pos) {
    switch (data[pos]) {
      case '&':
        buffer.append("&amp;");
        break;
      case '\"':
        buffer.append("&quot;");
        break;
      case '\'':
        buffer.append("&apos;");
        break;
      case '<':
        buffer.append("&lt;");
        break;
      case '>':
        buffer.append("&gt;");
        break;
      default:
        buffer.append(&data[pos], 1);
        break;
    }
  }
  data.swap(buffer);
}

}  // namespace ext
}  // namespace site
}  // namespace codelithic
