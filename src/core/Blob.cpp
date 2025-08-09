#include "Blob.hpp"
#include "ObjectID.hpp"
#include <openssl/sha.h>

namespace noto {

Blob::Blob(const std::vector<uint8_t>& data)
   : m_data(data), m_id(ObjectID::fromData(data)) {}

ObjectType Blob::type() const {
   return ObjectType::Blob;
}

ObjectID Blob::id() const {
   return m_id;
}

std::vector<uint8_t> Blob::serialize() const {
   return m_data;
}

const std::vector<uint8_t>& Blob::data() const {
   return m_data;
}

} // namespace noto
