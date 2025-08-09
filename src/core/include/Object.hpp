#pragma once
#include <vector>
#include <string>
#include "ObjectID.hpp"

namespace noto {

enum class ObjectType {
   Blob,
   Patch,
   Tree,
   Commit
};

class Object {
public:
   virtual ~Object() = default;

   virtual ObjectType type() const = 0;
   virtual ObjectID id() const = 0;

   virtual std::vector<uint8_t> serialize() const = 0;
   static ObjectID computeID(const std::vector<uint8_t>& content);

   static std::string typeToString(ObjectType t);
};

} // namespace noto
