from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, CMakeDeps, cmake_layout, CMakeToolchain
from conan.tools.apple import fix_apple_shared_install_name
from conan.errors import ConanInvalidConfiguration
from conan.tools.files import copy

class MaxBotConan(ConanFile):
    name = "maxbot"
    description = "maxbot communication toolkit"
    version = "0.0.1"

    settings = "os", "compiler", "build_type", "arch"

    options = {
        "shared": [True, False],
        "fPIC": [True, False]
    }

    default_options = {
        "shared": True,
        "fPIC": True
    }

    exports_sources = "../include/*"

    package_type = "header-library"

    no_copy_source = True

    def package(self):
        copy(self, "*.h", self.source_folder, self.package_folder)

    def package_info(self):
        self.cpp_info.bindirs = []
        self.cpp_info.libdirs = []