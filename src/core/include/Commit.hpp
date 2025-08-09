#pragma once
#include "Object.hpp"
#include "ObjectID.hpp"
#include <string>
#include <vector>

namespace noto {

class Commit : public Object {
public:
   Commit(const ObjectID& tree,
          const std::vector<ObjectID>& parents,
          const std::string& author,
          const std::string& message,
          uint64_t timestamp);
   
   ObjectType type() const override;
   ObjectID id() const override;
   std::vector<uint8_t> serialize() const override;

   const ObjectID& tree() const;
   const std::vector<ObjectID>& parents() const;
   const std::string& author() const;
   const std::string& message() const;
   uint64_t timestamp() const;

private:
   ObjectID m_tree;
   std::vector<ObjectID> m_parents;
   std::string m_author;
   std::string m_message;
   uint64_t m_timestamp;
   ObjectID m_id;
};

} // namespace noto