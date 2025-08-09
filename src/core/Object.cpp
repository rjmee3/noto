#include "Object.hpp"
#include "ObjectID.hpp"
#include <openssl/sha.h>
#include <stdexcept>
#include <sstream>

namespace noto {

// ComputeID hashes arbitrary content and returns an ObjectID.
// The content parameter should be the serialized bytes used to identify the object
// (e.g., type||length||payload).
ObjectID Object::computeID(const std::vector<uint8_t>& content) {
   return ObjectID::fromData(content);
}

std::string Object::typeToString(ObjectType t) {
   switch (t) {
      case ObjectType::Blob:   return "blob";
      case ObjectType::Patch:  return "patch";
      case ObjectType::Tree:   return "tree";
      case ObjectType::Commit: return "commit";
      default:                 return "unknown";
   }
}

} // namespace noto