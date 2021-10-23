# Requirements
- `conan` package manager
  - install with `pip install conan` or use provided binaries for your system.
- C++ compiler with support for c++20
  - I've tested with `MSVC 19.29.3`

# Building

From `proj01` directory call:


```$ conan install . -if build -s build_type=Release```
  - This will install required dependencies into `build` directory
  - The dot means relative path to `conanfile.py`


```$ conan build . -if build -bf build```
  - This will configure cmake, build code and run tests.
