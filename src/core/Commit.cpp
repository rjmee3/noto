#include "Commit.hpp"
#include "ObjectID.hpp"
#include <sstream>

namespace noto {

Commit::Commit(const ObjectID& tree,
               const std::vector<ObjectID>& parents,
               const std::string& author,
               const std::string& message,
               uint64_t timestamp)
   : m_tree(tree), m_parents(parents), m_author(author), m_message(message), m_timestamp(timestamp) {
   std::ostringstream oss;
   oss << "tree " << m_tree.toHex() << "\n";
   for (const auto& parent: m_parents) {
      oss << "parent " << parent.toHex() << "\n";
   }
   oss << "author " << m_author << "\n";
   oss << "timestamp " << m_timestamp << "\n";
   oss << "\n" << m_message << "\n";

   std::string data = oss.str();
   m_id = ObjectID::fromData(std::vector<uint8_t>(data.begin(), data.end()));
}

ObjectType Commit::type() const {
   return ObjectType::Commit;
}

ObjectID Commit::id() const {
   return m_id;
}

std::vector<uint8_t> Commit::serialize() const {
   std::ostringstream oss;
   oss << "tree " << m_tree.toHex() << "\n";
   for (const auto& parent : m_parents) {
      oss << "parent " << parent.toHex() << "\n";
   }
   oss << "author " << m_author << "\n";
   oss << "timestamp " << m_timestamp << "\n";
   oss << "\n" << m_message << "\n";

   std::string str = oss.str();
   return std::vector<uint8_t>(str.begin(), str.end());
}

const ObjectID& Commit::tree() const {
   return m_tree;
}

const std::vector<ObjectID>& Commit::parents() const {
   return m_parents;
}

const std::string& Commit::author() const {
   return m_author;
}

const std::string& Commit::message() const {
   return m_message;
}

uint64_t Commit::timestamp() const {
   return m_timestamp;
}

}
