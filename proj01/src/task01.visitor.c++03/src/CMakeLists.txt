find_package(fmt REQUIRED)

add_library(
  task01.visitor.c++03
  INTERFACE
  include/task01.visitor.c++03/visitable.hpp
  include/task01.visitor.c++03/binary_tree_visitor.hpp
  include/task01.visitor.c++03/binary_tree_leaf.hpp
  include/task01.visitor.c++03/binary_tree_node.hpp
  include/task01.visitor.c++03/summation_visitor.hpp
  include/task01.visitor.c++03/traversal_visitor.hpp)
target_include_directories(task01.visitor.c++03 INTERFACE include)
set_target_properties(task01.visitor.c++03 PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(task01.visitor.c++03 INTERFACE fmt::fmt)

add_executable(task01.visitor.c++03.app client.cpp)
target_link_libraries(task01.visitor.c++03.app PUBLIC task01.visitor.c++03 fmt::fmt)
