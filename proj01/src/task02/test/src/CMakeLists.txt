find_package(GTest)

add_executable(task02.test main.cpp cipher_packer_test.cpp rc4_test.cpp)
target_link_libraries(task02.test task02 GTest::gtest)
target_compile_definitions(task02.test PRIVATE RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../data")
add_test(NAME task02.test COMMAND task02.test)
