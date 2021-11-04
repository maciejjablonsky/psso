#pragma once
#include <algorithm>
#include <array>
#include <boost/range/combine.hpp>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <string>
#include <vector>

namespace psso
{
using range = std::pmr::vector<std::byte>;
namespace
{
template <typename It, typename PatternIt>
It fill_with_pattern(It first,
                     It last,
                     PatternIt pattern_first,
                     PatternIt pattern_last)
{
    while (first != last)
    {
        auto to_fill = std::min(last - first, pattern_last - pattern_first);
        std::copy_n(pattern_first, to_fill, first);
        first += to_fill;
    }
    return first;
}


} // namespace
class RC4
{
  private:
    range s_box{256};
    range k_box{256};

    int i_ = 0;
    int j_ = 0;
  public:
    RC4(const psso::range& key)
    {
        assert(key.size() >= 1 && key.size() <= 256 &&
               "Key length must be in <1:256>");
        prepare_k_box(key);
        prepare_s_box();
    }

  private:
    auto algorithm(const psso::range& message)
    {
        auto key_stream = this->key_stream(message.size());
        psso::range processed;
        processed.resize(message.size());
        std::transform(std::begin(message),
                       std::end(message),
                       std::begin(key_stream),
                       std::begin(processed),
                       [](auto message_value, auto key_stream_value) {
                           return key_stream_value ^ message_value;
                       });
        return processed;
    }

  public:
    auto encrypt(const psso::range& plain_message)
    {
        return algorithm(plain_message);
    }

    auto decrypt(const psso::range& encrypted_message)
    {
        return algorithm(encrypted_message);
    }

  private:
    void prepare_k_box(const psso::range& key)
    {
        fill_with_pattern(
            std::begin(k_box), std::end(k_box), std::begin(key), std::end(key));
    }

    void prepare_s_box()
    {
        auto i = 0;
        for (auto& value : s_box)
        {
            value = static_cast<std::byte>(i);
            ++i;
        }
        scramble();
    }

    void scramble()
    {
        uint8_t j = 0;
        for (auto i = 0; i < 256; ++i)
        {
            j = j + std::to_integer<uint8_t>(s_box[i]) +
                std::to_integer<uint8_t>(k_box[i]);
            j %= 256;
            std::swap(s_box[i], s_box[j]);
        }
    }

    range key_stream(const auto message_length)
    {
        range output;
        output.resize(message_length);
        std::generate(
            std::begin(output), std::end(output), [&i = i_, &j = j_, &s_box = s_box] {
                i = (i + 1) % 256;
                j = (j + std::to_integer<uint8_t>(s_box[i])) % 256;
                std::swap(s_box[i], s_box[j]);
                auto out_index = (std::to_integer<uint8_t>(s_box[i]) +
                                  std::to_integer<uint8_t>(s_box[j])) %
                                 256;
                return s_box[out_index];
            });
        return output;
    }
};
} // namespace psso
