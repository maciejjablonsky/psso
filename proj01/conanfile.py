from conans import ConanFile, CMake

class PSSO_P01ConanFile(ConanFile):
    name = "PSSO-P01"
    settings = "os", "arch", "compiler", "build_type"
    build_requires = "cmake/3.21.3"
    requires = "fmt/7.1.3", "gtest/cci.20210126", "boost/1.77.0"
    generators = "cmake_paths", "cmake_find_package"
    _cmake = None

    def build(self):
        self._cmake = CMake(self)
        self._cmake.definitions['PSSO_TESTING_ENABLED'] = 'ON'
        self._cmake.configure()
        self._cmake.build()
        self._cmake.test()
