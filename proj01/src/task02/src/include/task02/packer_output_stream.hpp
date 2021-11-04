#pragma once
#include <task02/packing.hpp>
#include <task02/streamable.hpp>
namespace psso
{
template <ByteOutputStreamable Upstream> class PackerOutputStream
{
  private:
    Compressor compressor_;
    Upstream upstream_;

  public:
    PackerOutputStream(Upstream&& upstream) : upstream_(std::move(upstream))
    {
    }

    PackerOutputStream& write(const std::byte* s, std::streamsize count)
    {
        auto packed = compressor_.encode(to_range(s, s + count));
        upstream_.write(reinterpret_cast<std::byte*>(packed.data()),
                        packed.size());
        return *this;
    }
}; // namespace psso
} // namespace psso
