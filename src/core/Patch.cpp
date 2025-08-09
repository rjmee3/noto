#include "Patch.hpp"
#include "ObjectID.hpp"

namespace noto {

Patch::Patch(const std::string& oldPath,
             const std::string& newPath,
             const std::string& diff)
   : m_oldPath(oldPath), m_newPath(newPath), m_diff(diff) {
   std::vector<uint8_t> data(m_diff.begin(), m_diff.end());
   m_id = ObjectID::fromData(data);
}

ObjectType Patch::type() const {
   return ObjectType::Patch;
}

ObjectID Patch::id() const {
   return m_id;
}

std::vector<uint8_t> Patch::serialize() const {
   std::string combined = m_oldPath + "\n" + m_newPath + "\n" + m_diff;
   return std::vector<uint8_t>(combined.begin(), combined.end());
}

const std::string& Patch::oldPath() const {
   return m_oldPath;
}

const std::string& Patch::newPath() const {
   return m_newPath;
}

const std::string& Patch::diff() const {
   return m_diff;
}

} // namespace noto