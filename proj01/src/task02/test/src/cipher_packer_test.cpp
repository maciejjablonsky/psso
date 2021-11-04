#include <array>
#include <filesystem>
#include <gtest/gtest.h>
#include <task02/cipher_input_stream.hpp>
#include <task02/cipher_output_stream.hpp>
#include <task02/file_input_stream.hpp>
#include <task02/file_output_stream.hpp>
#include <task02/packer_output_stream.hpp>
#include <task02/packing.hpp>
#include <task02/unpacker_input_stream.hpp>
#include <vector>

std::filesystem::path resource_path()
{
    return RESOURCE_PATH;
}

template <psso::ByteInputStreamable InStream,
          psso::ByteOutputStreamable OutStream>
void pass(InStream& in, OutStream& out, std::streamsize buffer_size)
{
    psso::range buffer{static_cast<size_t>(buffer_size)};
    in.read(buffer.data(), buffer.size());
    while (in.gcount() > 0)
    {
        out.write(buffer.data(), in.gcount());
        in.read(buffer.data(), buffer.size());
    }
}

bool content_equals(const std::filesystem::path& left_path,
                    const std::filesystem::path& right_path)
{
    auto in_left    = psso::FileInputStream{left_path};
    assert(in_left.good());
    auto in_rigth   = psso::FileInputStream{right_path};
    assert(in_rigth.good());
    auto size_left  = std::filesystem::file_size(left_path);
    auto size_right = std::filesystem::file_size(right_path);
    std::pmr::vector<std::byte> buffer_left{size_left};
    std::pmr::vector<std::byte> buffer_right{size_right};
    bool result = false;

    if (!in_left.read(buffer_left.data(), buffer_left.size()))
    {
        throw std::runtime_error(
            std::format("Failed to open {}", left_path.string()));
    }
    if (!in_rigth.read(buffer_right.data(), buffer_right.size()))
    {
        throw std::runtime_error(
            std::format("Failed to open {}", right_path.string()));
    }

    return buffer_left == buffer_right;
}

TEST(CipherPackerTest, Packer)
{
    {
        auto in  = psso::FileInputStream{resource_path() / "plainText.txt", std::ios::binary};
        auto out = psso::PackerOutputStream{
            psso::FileOutputStream{resource_path() / "compressedText.txt", std::ios::binary}};
        pass(in, out, 64);
    }
    {
        auto in = psso::UnpackerInputStream{
            psso::FileInputStream{resource_path() / "compressedText.txt", std::ios::binary}};
        auto out = psso::FileOutputStream{resource_path() / "out.txt", std::ios::binary};
        pass(in, out, 32);
    }
    EXPECT_EQ(std::filesystem::file_size(resource_path() / "plainText.txt"),
              std::filesystem::file_size(resource_path() / "out.txt"));
    EXPECT_TRUE(content_equals(resource_path() / "plainText.txt",
                               resource_path() / "out.txt"));
}

TEST(CipherPackerTest, Cipher)
{
    {
        auto in  = psso::FileInputStream{resource_path() / "plainText.txt", std::ios::binary};
        auto out = psso::CipherOutputStream{
            psso::FileOutputStream{resource_path() / "encryptedText.txt", std::ios::binary}};
        pass(in, out, 64);
    }
    {
        auto in = psso::CipherInputStream{
            psso::FileInputStream{resource_path() / "encryptedText.txt", std::ios::binary}};
        auto out = psso::FileOutputStream{resource_path() / "out.txt", std::ios::binary};
        pass(in, out, 32);
    }
    EXPECT_EQ(std::filesystem::file_size(resource_path() / "plainText.txt"),
              std::filesystem::file_size(resource_path() / "out.txt"));
    EXPECT_TRUE(content_equals(resource_path() / "plainText.txt",
                               resource_path() / "out.txt"));
}

TEST(CipherPackerTest, CipherAndPacker)
{
    {
        auto in  = psso::FileInputStream{resource_path() / "plainText.txt", std::ios::binary};
        auto out = psso::PackerOutputStream{
            psso::CipherOutputStream{psso::FileOutputStream{
                resource_path() / "encryptedCompressedText.txt", std::ios::binary}}};
        pass(in, out, 32);
    }
    {
        auto in = psso::UnpackerInputStream{
            psso::CipherInputStream{psso::FileInputStream{
                resource_path() / "encryptedCompressedText.txt", std::ios::binary}}};
        auto out = psso::FileOutputStream{resource_path() / "out.txt", std::ios::binary};
        pass(in, out, 64);
    }
    EXPECT_EQ(std::filesystem::file_size(resource_path() / "plainText.txt"),
              std::filesystem::file_size(resource_path() / "out.txt"));
    EXPECT_TRUE(content_equals(resource_path() / "plainText.txt",
                               resource_path() / "out.txt"));
}
