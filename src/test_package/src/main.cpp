#include <iostream>
#include <quickjsxx.hpp>
#include "print_pkg_info.hpp"

int main() {
    const auto ctx = quickjsxx::Context{quickjsxx::Runtime::Create()};

    const auto result = ctx.Eval(R"(console.log('Hello, world!'))"sv);

    //if (::JS_IsException(result))
      //  ::js_std_dump_error(ctx);
}

static auto _nothing = [] {
    print_pkg_info();
    return 0;
}();
