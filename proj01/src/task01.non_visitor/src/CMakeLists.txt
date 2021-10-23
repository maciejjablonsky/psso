add_library(
  task01.non_visitor
  INTERFACE
  include/task01.non_visitor/tree_node.hpp
  include/task01.non_visitor/binary_tree_node.hpp
  include/task01.non_visitor/simple_tree_node.hpp
  include/task01.non_visitor/parser.hpp)

set_target_properties(task01.non_visitor PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(task01.non_visitor INTERFACE include)
find_package(Boost REQUIRED)
find_package(fmt REQUIRED)
target_link_libraries(task01.non_visitor INTERFACE Boost::headers fmt::fmt)
target_compile_features(task01.non_visitor INTERFACE cxx_std_20)

