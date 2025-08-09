#pragma once
#include "Object.hpp"
#include <vector>
#include <string>

namespace noto {

enum class TreeEntryType {
   Blob,
   Tree
};

struct TreeEntry {
   TreeEntryType type;
   std::string name;
   ObjectID id;
};

class Tree : public Object {
public:
   Tree(const std::vector<TreeEntry>& entries);

   ObjectType type() const override;
   ObjectID id() const override;
   std::vector<uint8_t> serialize() const override;

   const std::vector<TreeEntry>& entries() const;

private:
   std::vector<TreeEntry> m_entries;
   ObjectID m_id;
};

} // namespace noto
