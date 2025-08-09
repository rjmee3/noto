#pragma once
#include "Object.hpp"
#include <string>

namespace noto {

class Patch : public Object {
public:
   Patch(const std::string& oldPath,
         const std::string& newPath,
         const std::string& diff);

   ObjectType type() const override;
   ObjectID id() const override;
   std::vector<uint8_t> serialize() const override;

   const std::string& oldPath() const;
   const std::string& newPath() const;
   const std::string& diff() const;

private:
      std::string m_oldPath;
      std::string m_newPath;
      std::string m_diff;
      ObjectID m_id;
};

} // namespace noto
