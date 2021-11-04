#include <boost/range/combine.hpp>
#include <charconv>
#include <gtest/gtest.h>
#include <string>
#include <task02/rc4.hpp>
#include <task02/streamable.hpp>

TEST(RC4_Test, KeyEncryption)
{
    psso::RC4 cipher{psso::to_range("Key")};
    const auto plain_text = psso::to_range("Plaintext");
    auto result           = cipher.encrypt(plain_text);

    const auto expected_cipher_text = psso::hex_to_range("BBF316E8D940AF0AD3");

    for (auto&& [expected, result] :
         boost::combine(expected_cipher_text, result))
    {
        EXPECT_EQ(expected, result);
    }
}

TEST(RC4_Test, KeyDecryption)
{
    psso::RC4 cipher{psso::to_range("Key")};
    const auto cipher_text = psso::hex_to_range("BBF316E8D940AF0AD3");
    auto result            = cipher.decrypt(cipher_text);

    const auto expected_plain_text = psso::to_range("Plaintext");

    ASSERT_TRUE(std::equal(std::begin(expected_plain_text),
                           std::end(expected_plain_text),
                           std::begin(result)));
}

TEST(RC4_Test, WikiEncryption)
{
    psso::RC4 cipher{psso::to_range("Wiki")};
    const auto plain_text = psso::to_range("pedia");
    auto result           = cipher.encrypt(plain_text);

    const auto expected_cipher_text = psso::hex_to_range("1021BF0420");

    ASSERT_TRUE(std::equal(std::begin(expected_cipher_text),
                           std::end(expected_cipher_text),
                           std::begin(result)));
}

TEST(RC4_Test, WikiDecryption)
{
    psso::RC4 cipher{psso::to_range("Wiki")};
    const auto cipher_text = psso::hex_to_range("1021BF0420");
    auto result            = cipher.decrypt(cipher_text);

    const auto expected_plain_text = psso::to_range("pedia");

    ASSERT_TRUE(std::equal(std::begin(expected_plain_text),
                           std::end(expected_plain_text),
                           std::begin(result)));
}
