#include "path.h"

NAMESPACE_BEGIN(filesystem)

filesystem::path& path::remove_filename() {
  if (!leafs.empty()) {
    leafs.pop_back();
  }
  return *this;
}

filesystem::path& path::replace_filename(const class filesystem::path& p) {
  remove_filename() /= p;
  return *this;
}

filesystem::path& path::operator/= (const filesystem::path& rhs) {
  if (rhs.empty()) {
    return *this;
  }
  if (this->empty()) {
    *this = rhs;
  } else {
    std::copy(std::begin(rhs.leafs), std::end(rhs.leafs), std::back_inserter(leafs));
    this->type = rhs.type;
  }

  return *this;
}

NAMESPACE_END(filesystem)
