#pragma once
#include <array>
#include <string>
#include <vector>

namespace noto {

class ObjectID {
public:
   static constexpr size_t SIZE = 32;

   ObjectID();
   explicit ObjectID(const std::vector<uint8_t>& data);

   static ObjectID fromHex(const std::string& hex);
   static ObjectID fromData(const std::vector<uint8_t>& data);

   std::string toHex() const;
   const std::array<uint8_t, SIZE>& bytes() const;

   bool operator==(const ObjectID& other) const;
   bool operator!=(const ObjectID& other) const;

private:
   std::array<uint8_t, SIZE> m_bytes;
};

} // namespace noto
