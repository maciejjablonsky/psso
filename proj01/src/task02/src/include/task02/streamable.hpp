#pragma once
#include <concepts>
#include <cstddef>
#include <vector>

namespace psso
{
using range = std::pmr::vector<std::byte>;
namespace
{
range hex_to_range(const std::string& hex)
{
    assert(hex.length() % 2 == 0);
    range output;
    output.reserve(hex.length() / 2);
    for (auto start = 0; start < hex.length(); start += 2)
    {
        auto val = static_cast<std::byte>(
            std::stoi(hex.substr(start, 2), nullptr, 16));
        output.push_back(val);
    }
    return output;
}

template <typename It> range to_range(It first, It last)
{
    psso::range r;
    r.resize(last - first);
    std::transform(first, last, std::begin(r), [](auto value) {
        return static_cast<psso::range::value_type>(value);
    });
    return r;
}

template <size_t N> range to_range(const char (&txt)[N])
{
    return to_range(std::begin(txt), std::end(txt) - 1);
}
}

template <typename Stream>
concept ByteInputStreamable = requires(Stream s, std::byte byte)
{
    {s.read(&byte, 1)};
    {
        s.gcount()
    }
    ->std::convertible_to<std::streamsize>;
};

template <typename Stream>
concept ByteOutputStreamable = requires(Stream s, std::byte byte)
{
    {s.write(&byte, 1)};
};
} // namespace psso
