#include <iostream>
#include <quickjsxx.hpp>

#ifdef _WIN32
__declspec(dllexport)
#endif
void print_pkg_info();

static auto _nothing = [] {
    print_pkg_info();
    return 0;
}();

int main() {
    const auto ctx = quickjsxx::Context{std::make_shared<quickjsxx::Runtime>()};

    const auto result = ctx.Eval(R"(console.log('Hello, world!'))"sv);

    //if (::JS_IsException(result))
      //  ::js_std_dump_error(ctx);
}

void print_pkg_info() {
    #ifdef NDEBUG
    std::cout << "QuickJS: Hello World Release!\n";
    #else
    std::cout << "QuickJS: Hello World Debug!\n";
    #endif

    // ARCHITECTURES
    #ifdef _M_X64
    std::cout << "  QuickJS: _M_X64 defined\n";
    #endif

    #ifdef _M_IX86
    std::cout << "  QuickJS: _M_IX86 defined\n";
    #endif

    #ifdef _M_ARM64
    std::cout << "  QuickJS: _M_ARM64 defined\n";
    #endif

    #if __i386__
    std::cout << "  QuickJS: __i386__ defined\n";
    #endif

    #if __x86_64__
    std::cout << "  QuickJS: __x86_64__ defined\n";
    #endif

    #if __aarch64__
    std::cout << "  QuickJS: __aarch64__ defined\n";
    #endif

    // Libstdc++
    #if defined _GLIBCXX_USE_CXX11_ABI
    std::cout << "  QuickJS: _GLIBCXX_USE_CXX11_ABI "<< _GLIBCXX_USE_CXX11_ABI << "\n";
    #endif

    // COMPILER VERSIONS
    #if _MSC_VER
    std::cout << "  QuickJS: _MSC_VER" << _MSC_VER<< "\n";
    #endif

    #if _MSVC_LANG
    std::cout << "  QuickJS: _MSVC_LANG" << _MSVC_LANG<< "\n";
    #endif

    #if __cplusplus
    std::cout << "  QuickJS: __cplusplus" << __cplusplus<< "\n";
    #endif

    #if __INTEL_COMPILER
    std::cout << "  QuickJS: __INTEL_COMPILER" << __INTEL_COMPILER<< "\n";
    #endif

    #if __GNUC__
    std::cout << "  QuickJS: __GNUC__" << __GNUC__<< "\n";
    #endif

    #if __GNUC_MINOR__
    std::cout << "  QuickJS: __GNUC_MINOR__" << __GNUC_MINOR__<< "\n";
    #endif

    #if __clang_major__
    std::cout << "  QuickJS: __clang_major__" << __clang_major__<< "\n";
    #endif

    #if __clang_minor__
    std::cout << "  QuickJS: __clang_minor__" << __clang_minor__<< "\n";
    #endif

    #if __apple_build_version__
    std::cout << "  QuickJS: __apple_build_version__" << __apple_build_version__<< "\n";
    #endif

    // SUBSYSTEMS

    #if __MSYS__
    std::cout << "  QuickJS: __MSYS__" << __MSYS__<< "\n";
    #endif

    #if __MINGW32__
    std::cout << "  QuickJS: __MINGW32__" << __MINGW32__<< "\n";
    #endif

    #if __MINGW64__
    std::cout << "  QuickJS: __MINGW64__" << __MINGW64__<< "\n";
    #endif

    #if __CYGWIN__
    std::cout << "  QuickJS: __CYGWIN__" << __CYGWIN__<< "\n";
    #endif
}
