#include "ObjectID.hpp"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace noto {

ObjectID::ObjectID() {
   m_bytes.fill(0);
}

ObjectID::ObjectID(const std::vector<uint8_t>& data) {
   if (data.size != SIZE) {
      throw std::invalid_argument("ObjectID ctor expects a vector of length " + SIZE);
   }
   std::copy_n(data.begin(), SIZE, m_bytes.begin());
}

ObjectID ObjectID::fromHex(const std::string& hex) {
   if (hex.size() != SIZE * 2) {
      throw std::invalid_argument("Hex string must be 64 characters for SHA-256");
   }

   ObjectID id;
   for (size_t i = 0; i < SIZE; ++i) {
      std::string byteStr = hex.substr(i * 2, 2);
      unsigned int byteVal = 0;
      std::istringstream iss(byteStr);
      iss >> std::hex >> byteVal;
      if (iss.fail()) {
         throw std::invalid_argument("Invalid hex string");
      }
      id.m_bytes[i] = static_cast<uint8_t>(byteVal);
   }
   return id;
}

ObjectID ObjectID::fromData(const std::vector<uint8_t>& data) {
   unsigned char digest[SHA256_DIGEST_LENGTH];
   SHA256_CTX ctx;
   SHA256_Init(&ctx);
   if (!data.empty()) {
      SHA_256_Update(&ctx, data.data(), data.size());
   }
   SHA256_Final(digest, &ctx);

   ObjectID id;
   for (size_t i = 0; i < SIZE; ++i) {
      id.m_bytes[i] = static_cast<uint8_t>(digest[i]);
   }
   return id;
}

std::string ObjectID::toHex() const {
   std::ostringstream oss;
   oss << std::hex << std::setfill('0');
   for (auto b : m_bytes) {
      oss << std::setw(2) << static_cast<int>(b);
   }
   return oss.str();
}

const std::array<uint8_t, ObjectID::SIZE>& ObjectID::bytes() const {
   return m_bytes;
}

bool ObjectID::operator==(const ObjectID& other) const {
   return m_bytes == other.m_bytes;
}

bool ObjectID::operator!=(const ObjectID& other) const {
   return !(*this == other);
}

} // namespace noto
