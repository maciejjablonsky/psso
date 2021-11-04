#pragma once
#include <task02/streamable.hpp>
#include <task02/rc4.hpp>

namespace psso
{
template <ByteOutputStreamable Upstream> class CipherOutputStream
{
  private:
    Upstream upstream_;
    RC4 cipher_{psso::to_range("dupa!@#$")};

  public:
    CipherOutputStream(Upstream&& upstream) : upstream_(std::move(upstream))
    {
    }

    CipherOutputStream& write(const std::byte* s, std::streamsize count)
    {
        auto encrypted = cipher_.encrypt(to_range(s, s + count));
        upstream_.write(encrypted.data(), encrypted.size());
        return *this;
    }
};
} // namespace psso