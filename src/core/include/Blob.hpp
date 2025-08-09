#pragma once
#include "Object.hpp"

namespace noto {

class Blob : public Object {
public:
   explicit Blob(const std::vector<uint8_t>& data);

   ObjectType type() const override;
   ObjectID id() const override;
   std::vector<uint8_t> serialize() const override;

   const std::vector<uint8_t>& data() const;

private:
   std::vector<uint8_t> m_data;
   ObjectID m_id;
};

} // namespace noto
