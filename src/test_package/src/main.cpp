#include <iostream>
#include <quickjsxx.hpp>
#include "print_pkg_info.hpp"
#include "script.hpp"

int main() {
    const auto ctx = quickjsxx::Context{quickjsxx::Runtime::Create()};

    const auto result = ctx.Eval(code);

    //if (::JS_IsException(result))
      //  ::js_std_dump_error(ctx);
}
