
#ifndef SITE_ENTITY_H
#define SITE_ENTITY_H

#include <cgicc/Cgicc.h>
#include <cgicc/FormEntry.h>

#include "PageParameters.hpp"

namespace codelithic {
namespace site {
class Entity {
 public:
  std::string id;
  std::string ver;

  Entity();

  virtual ~Entity();

  virtual bool isValid() { return m_valid; };

  virtual void dump() {}

 protected:
  bool m_valid;

 private:
};
}  // namespace site
}  // namespace codelithic
#endif /* SITE_ENTITY_H */
