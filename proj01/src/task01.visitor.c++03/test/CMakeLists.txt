find_package(GTest REQUIRED)
add_executable(task01.visitor.c++03.test main.cpp compute_tree_test.cpp)
target_link_libraries(task01.visitor.c++03.test PUBLIC task01.visitor.c++03
                                                       GTest::gtest)
add_test(NAME task01.visitor.c++03.test COMMAND task01.visitor.c++03.test)
