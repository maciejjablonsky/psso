find_package(fmt REQUIRED)

add_library(
  task01.visitor.c++03.example
  INTERFACE
  include/task01.visitor.c++03.example/visitable.hpp
  include/task01.visitor.c++03.example/binary_tree_visitor.hpp
  include/task01.visitor.c++03.example/binary_tree_leaf.hpp
  include/task01.visitor.c++03.example/binary_tree_node.hpp
  include/task01.visitor.c++03.example/summation_visitor.hpp
  include/task01.visitor.c++03.example/traversal_visitor.hpp)
target_include_directories(task01.visitor.c++03.example INTERFACE include)
set_target_properties(task01.visitor.c++03.example PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(task01.visitor.c++03.example INTERFACE fmt::fmt)

add_executable(task01.visitor.c++03.example.app client.cpp)
target_link_libraries(task01.visitor.c++03.example.app PUBLIC task01.visitor.c++03.example fmt::fmt)
