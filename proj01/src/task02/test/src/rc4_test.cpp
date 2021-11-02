#include <boost/range/combine.hpp>
#include <charconv>
#include <gtest/gtest.h>
#include <string>
#include <task02/rc4.hpp>

psso::range hex_to_range(const std::string& hex)
{
    assert(hex.length() % 2 == 0);
    psso::range output;
    output.reserve(hex.length() / 2);
    for (auto start = 0; start < hex.length(); start += 2)
    {
        auto val =
            static_cast<std::byte>(std::stoi(hex.substr(start, 2), nullptr, 16));
        output.push_back(val);
    }
    return output;
}

template <typename It> psso::range to_range(It first, It last)
{
    psso::range r;
    r.resize(last - first);
    std::transform(first, last, std::begin(r), [](auto value) {
        return static_cast<psso::range::value_type>(value);
    });
    return r;
}

template <size_t N> psso::range to_range(const char (&txt)[N])
{
    return to_range(std::begin(txt), std::end(txt) - 1);
}

TEST(RC4_Test, KeyEncryption)
{
    psso::RC4 cipher{to_range("Key")};
    const auto plain_text = to_range("Plaintext");
    auto result           = cipher.encrypt(plain_text);

    const auto expected_cipher_text = hex_to_range("BBF316E8D940AF0AD3");

    for (auto&& [expected, result] :
         boost::combine(expected_cipher_text, result))
    {
        EXPECT_EQ(expected, result);
    }
}

TEST(RC4_Test, KeyDecryption)
{
    psso::RC4 cipher{to_range("Key")};
    const auto cipher_text = hex_to_range("BBF316E8D940AF0AD3");
    auto result            = cipher.decrypt(cipher_text);

    const auto expected_plain_text = to_range("Plaintext");

    ASSERT_TRUE(std::equal(std::begin(expected_plain_text),
                           std::end(expected_plain_text),
                           std::begin(result)));
}

TEST(RC4_Test, WikiEncryption)
{
    psso::RC4 cipher{to_range("Wiki")};
    const auto plain_text = to_range("pedia");
    auto result           = cipher.encrypt(plain_text);

    const auto expected_cipher_text = hex_to_range("1021BF0420");

    ASSERT_TRUE(std::equal(std::begin(expected_cipher_text),
                           std::end(expected_cipher_text),
                           std::begin(result)));
}

TEST(RC4_Test, WikiDecryption)
{
    psso::RC4 cipher{to_range("Wiki")};
    const auto cipher_text = hex_to_range("1021BF0420");
    auto result            = cipher.decrypt(cipher_text);

    const auto expected_plain_text = to_range("pedia");

    ASSERT_TRUE(std::equal(std::begin(expected_plain_text),
                           std::end(expected_plain_text),
                           std::begin(result)));
}
