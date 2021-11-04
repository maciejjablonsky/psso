#pragma once
#include <algorithm>
#include <bitset>
#include <boost/bimap.hpp>
#include <boost/dynamic_bitset.hpp>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <vector>

namespace psso
{
using range = std::pmr::vector<std::byte>;

namespace detail
{
using bm_type = boost::bimap<char, uint8_t>;

template <typename L, typename R>
boost::bimap<L, R> make_bimap(
    std::initializer_list<typename boost::bimap<L, R>::value_type> list)
{
    return boost::bimap<L, R>(list.begin(), list.end());
}
const bm_type char_value_ = make_bimap<char, uint8_t>(
    {{' ', 0},   {'a', 1},  {'b', 2},  {'c', 3},  {'d', 4},  {'e', 5},
     {'f', 6},   {'g', 7},  {'h', 8},  {'i', 9},  {'j', 10}, {'k', 11},
     {'l', 12},  {'m', 13}, {'n', 14}, {'o', 15}, {'p', 16}, {'q', 17},
     {'r', 18},  {'s', 19}, {'t', 20}, {'u', 21}, {'v', 22}, {'w', 23},
     {'x', 24},  {'y', 25}, {'z', 26}, {'.', 27}, {'*', 28}, {',', 29},
     {'\\', 30}, {'2', 31}, {'A', 32}, {'B', 33}, {'C', 34}, {'D', 35},
     {'E', 36},  {'F', 37}, {'G', 38}, {'H', 39}, {'I', 40}, {'J', 41},
     {'K', 42},  {'L', 43}, {'M', 44}, {'N', 45}, {'O', 46}, {'P', 47},
     {'Q', 48},  {'R', 49}, {'S', 50}, {'T', 51}, {'U', 52}, {'V', 53},
     {'W', 54},  {'0', 55}, {'1', 56}, {'3', 57}, {'4', 58}, {'5', 59},
     {'6', 60},  {'7', 61}, {'8', 62}, {'9', 63}});

uint8_t to_value(std::byte ch)
{
    if (auto result = char_value_.left.find(static_cast<char>(ch));
        result != char_value_.left.end())
    {
        return result->get_right();
    }
    return 0;
}

std::byte to_char(uint8_t byte)
{
    if (auto result = char_value_.right.find(byte);
        result != char_value_.right.end())
    {
        return static_cast<std::byte>(result->get_left());
    }
    return static_cast<std::byte>(' ');
}
} // namespace detail

unsigned long long subset_as_value(const boost::dynamic_bitset<>& bitset,
                                   size_t first,
                                   size_t last)
{
    unsigned long long value = 0;
    for (auto i = 0; first != last; ++first, ++i)
    {
        unsigned long long bit_value = bitset.test(first) & 0x1ULL;
        value |= bit_value << i;
    }
    return value;
}

boost::dynamic_bitset<> subset_as_bitset(const boost::dynamic_bitset<>& bitset,
                                         size_t first,
                                         size_t last)
{
    boost::dynamic_bitset output{last - first};
    for (auto i = 0; first != last; ++first, ++i)
    {
        output.test_set(i, bitset.test(first));
    }
    return output;
}

boost::dynamic_bitset<> concat_bitsets(const boost::dynamic_bitset<>& left,
                                       const boost::dynamic_bitset<>& right)
{
    boost::dynamic_bitset output{left.size() + right.size()};
    for (auto i = 0; i < left.size(); ++i)
    {
        output.test_set(i, left.test(i));
    }
    output <<= right.size();
    for (auto i = 0; i < right.size(); ++i)
    {
        output.test_set(i, right.test(i));
    }
    return output;
}

boost::dynamic_bitset<> range_to_bitset(const range& bytes)
{
    boost::dynamic_bitset output{bytes.size() * 8};
    for (auto byte : bytes)
    {
        output <<= 8;
        auto value = std::to_integer<uint8_t>(byte);
        for (auto i = 0; i < 8; ++i)
        {
            auto tmp  = 0x1 << i;
            auto tmp2 = value & tmp;
            auto tmp3 = tmp2 >> i;
            output.test_set(i, tmp3);
        }
    }
    return output;
}

class Compressor
{
  public:
    inline static const int SIX_BIT  = 6;
    inline static const int FIVE_BIT = 5;

    range encode(const range& txt, int bit = SIX_BIT)
    {
        range encoded{[&bit, &txt] {
            if (bit == SIX_BIT)
            {
                return static_cast<size_t>(3.0f * std::ceil(txt.size() / 4.0f));
            }
            else
            {
                return static_cast<size_t>(5.0f * std::ceil(txt.size() / 8.0f));
            }
        }()};
        boost::dynamic_bitset binary(txt.size() * bit);
        for (auto char_to_encode : txt)
        {
            boost::dynamic_bitset char_bits(bit,
                                            detail::to_value(char_to_encode));
            binary <<= char_bits.size();
            for (auto i = 0; i < char_bits.size(); ++i)
            {
                binary.test_set(i, char_bits.test(i));
            }
        }
        if (auto remainder = binary.size() % 8; remainder != 0)
        {
            binary.resize(binary.size() + 8 - remainder);
            binary <<= 8 - remainder;
        }
        for (auto i = 0; i < binary.size(); i += 8)
        {
            encoded[i / 8] = static_cast<std::byte>(subset_as_value(
                binary, binary.size() - i - 8, binary.size() - i));
        }
        return encoded;
    }

    range decode(const boost::dynamic_bitset<>& encoded, int bit = SIX_BIT)
    {
        range decoded_output;
        for (auto i = 0; i < encoded.size(); i += bit)
        {
            auto value = subset_as_value(
                encoded, encoded.size() - i - bit, encoded.size() - i);
            decoded_output.push_back(detail::to_char(value));
        }
        return decoded_output;
    }
};
} // namespace psso
