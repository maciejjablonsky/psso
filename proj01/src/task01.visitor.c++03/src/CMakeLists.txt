add_library(task01.visitor.c++03 INTERFACE)
find_package(fmt REQUIRED)
find_package(Boost REQUIRED)
target_include_directories(task01.visitor.c++03 INTERFACE include)
target_link_libraries(task01.visitor.c++03 INTERFACE fmt::fmt Boost::headers)
target_compile_features(task01.visitor.c++03 INTERFACE cxx_std_17)
