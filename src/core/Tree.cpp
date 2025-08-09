#include "Tree.hpp"
#include "ObjectID.hpp"

namespace noto {

Tree::Tree(const std::vector<TreeEntry>& entries)
   : m_entries(entries) {
   std::vector<uint8_t> serialized;
   for (const auto& entry : entries) {
      std::string line = (entry.type == TreeEntryType::Blob ? "blob " : "tree ") +
                          entry.name + " " + entry.id.toHex() + "\n";
      serialized.insert(serialized.end(), line.begin(), line.end());
   }
   m_id = ObjectID::fromData(serialized);
}

ObjectType Tree::type() const {
   return ObjectType::Tree;
}

ObjectID Tree::id() const {
   return m_id;
}

std::vector<uint8_t> Tree::serialize() const {
   std::vector<uint8_t> result;
   for (const auto& entry : m_entries) {
      std::string line = (entry.type == TreeEntryType::Blob ? "blob " : "tree ") +
                          entry.name + " " + entry.id.toHex() + "\n";
      result.insert(result.end(), line.begin(), line.end());
   }
   return result;
}

const std::vector<TreeEntry>& Tree::entries() const {
   return m_entries;
}

} // namespace noto
