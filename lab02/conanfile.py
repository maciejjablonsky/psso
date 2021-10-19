from conans import ConanFile, CMake

class PSSOCorba(ConanFile):
    version = '1.0.0'
    name = 'PSSOCorba'
    generators = 'cmake_find_package', 'cmake_paths'
    settings = 'os', 'compiler', 'arch', 'build_type'
    build_requires = 'cmake/3.20.0'
    def build(self):
        cmake = CMake(self)
        cmake.definitions['ENABLE_CORBA'] = 'ON'
        cmake.definitions['CORBA_IMPLEMENTATION'] = "OMNIORB"
        cmake.configure()
        cmake.build()
