#pragma once
#include <task02/rc4.hpp>
#include <task02/streamable.hpp>

namespace psso
{
template <ByteInputStreamable Upstream> class CipherInputStream
{
  private:
    Upstream upstream_;
    RC4 cipher_{psso::to_range("dupa!@#$")};
    std::streamsize last_read_characters_ = 0;

  public:
    CipherInputStream(Upstream&& upstream) : upstream_(std::move(upstream))
    {
    }

    CipherInputStream& read(std::byte* s, std::streamsize count)
    {
        range current_read;
        current_read.resize(count);
        upstream_.read(current_read.data(), current_read.size());
        current_read.resize(upstream_.gcount());
        auto decrypted        = cipher_.decrypt(current_read);
        last_read_characters_ = decrypted.size();
        std::copy(std::begin(decrypted), std::end(decrypted), s);
        return *this;
    }

    std::streamsize gcount() const
    {
        return last_read_characters_;
    }
};
} // namespace psso