# JFrog Conan v1.66

import os, sys
import conan, conan.tools.cmake, conan.tools.files

class QuickJSConan(conan.ConanFile):
    print(f'RUNNING {__file__} @ {os.getcwd()}', file=sys.stderr)

    name = 'QuickJS'

    license = 'MIT'
    author = 'Fabrice Bellard', 'Charlie Gordon'
    url = 'https://github.com/shynur/quickjs'
    #description = ''
    topics = 'js', 'javascript', 'es2023', 'es2024', 'ECMAScript', 'interpreter', 'embedded'

    settings = 'os', 'compiler', 'build_type', 'arch'
    options = {
        'shared': [True, False],
        'fPIC': [True],
    }
    default_options = {
        'shared': True,
        'fPIC': True,
    }

    exports_sources = 'Version.txt', 'src/*'

    def set_version(self):
        self.version = conan.tools.files.load(
            self,
            'Version.txt' #next(
            #    p for p in (f'{d}/Version.txt' for d in ['.', '../export_source']) if os.path.exists(p)
            #)
        )

    def config_options(self):
        if self.settings.os == 'Windows':
            del self.options.fPIC

    def layout(self):
        conan.tools.cmake.cmake_layout(self, src_folder='src')

    def generate(self):
        tc = conan.tools.cmake.CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = conan.tools.cmake.CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = conan.tools.cmake.CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["quickjs"]
