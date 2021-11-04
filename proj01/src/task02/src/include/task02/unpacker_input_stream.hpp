#pragma once
#include <cassert>
#include <optional>
#include <task02/packing.hpp>
#include <task02/streamable.hpp>
#include <vector>

namespace psso
{
template <ByteInputStreamable Upstream> class UnpackerInputStream
{
  private:
    Upstream upstream_;
    std::streamsize last_read_characters_ = 0;
    int bit_ = Compressor::SIX_BIT;
    Compressor compressor_;
    boost::dynamic_bitset<> bits_;

  public:
    UnpackerInputStream(Upstream&& upstream) : upstream_(std::move(upstream))
    {
    }

    UnpackerInputStream& read(std::byte* s, std::streamsize count)
    {
        range current_read;
        current_read.resize(count);
        upstream_.read(current_read.data(), current_read.size());
        current_read.resize(upstream_.gcount());

        bits_ = concat_bitsets(bits_, range_to_bitset(current_read));
        auto how_many_symbols =
            ((bits_.size() / bit_) < count) ? (bits_.size() / bit_) : count;
        auto decoded = compressor_.decode(
            subset_as_bitset(bits_, bits_.size() - how_many_symbols * bit_, bits_.size()));
        last_read_characters_ = decoded.size();
        bits_ = subset_as_bitset(bits_, 0, bits_.size() - how_many_symbols * bit_);
        std::copy_n(std::begin(decoded), how_many_symbols, s);
        return *this;
    }

    std::streamsize gcount() const
    {
        return last_read_characters_;
    }
};
} // namespace psso