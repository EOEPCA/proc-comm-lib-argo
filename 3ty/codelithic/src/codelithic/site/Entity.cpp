
#include "codelithic/site/Entity.hpp"

namespace codelithic {
namespace site {

Entity::Entity() {
  m_valid = false;
  id = "";
  ver = "0.1";
}

Entity::~Entity() {}

}  // namespace site
}