#include <iostream>
#include <quickjsxx.hpp>
#include <print>
#include "print_pkg_info.hpp"
#include "script.hpp"

int main() {
    const auto ctx = quickjsxx::Context::Create(quickjsxx::Runtime::Create());

    std::cout << std::get<double>(ctx->Eval(R"( 2 )").GetValue()) << '\n';

    std::cout << std::get<std::intmax_t>(ctx->Eval(R"( 996n )").GetValue()) << '\n';

    ctx->Eval(R"( console.log('come from console.log') )");

    std::cout << std::get<std::string>(ctx->Eval(R"( 'jjjjjjjjjj' )").GetValue()) << '\n';

    auto promise = ctx->Eval(R"( 0, async function() {
        await new Promise(r => setTimeout(r, 1000))
        console.log(233)
        return 42
    }())");
    promise.await();
    std::cout << std::get<double>(promise.GetValue()) << '\n';

    ctx->Eval(R"(  )");
}
