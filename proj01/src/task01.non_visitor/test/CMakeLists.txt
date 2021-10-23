find_package(GTest REQUIRED)

add_executable(task01.non_visitor.test main.cpp in_fix_test.cpp)
target_link_libraries(task01.non_visitor.test GTest::gtest task01.non_visitor)
add_test(NAME task01.non_visitor.test COMMAND $<TARGET_FILE:task01.non_visitor.test>)
