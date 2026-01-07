#pragma once
#include "quickjs.h"
#include "quickjs-libc.h"
#include <string>
#include <type_traits>
#include <stdexcept>
#include <memory>
using namespace std::literals;


namespace quickjsxx <%

class Runtime;
class Context;
class Value;

class Runtime: std::enable_shared_from_this<Runtime> {
        std::remove_pointer_t<decltype(::JS_NewRuntime())> *const prt;
        friend Context;

        struct consTag{explicit consTag() = default;};
    public:
        Runtime(consTag): prt{[] {
            const auto prt = ::JS_NewRuntime();
            if (!prt)
                throw std::runtime_error{"Failed to create QuickJS runtime"};
            return prt;
        }()} {}
        ~Runtime() {
            ::JS_FreeRuntime(this->prt);
        }

        static auto Create() {
            return std::make_shared<Runtime>(consTag{});
        }
};

class Context {
        const std::shared_ptr<Runtime> rt;
        std::remove_pointer_t<decltype(::JS_NewContext(NULL))> *const pctx;
    public:
        Context(const std::shared_ptr<Runtime> rt)
        : rt{rt},
          pctx{[this] {
            const auto pctx = ::JS_NewContext(this->rt->prt);
            if (!pctx)
                throw std::runtime_error{"Failed to create QuickJS context"};
            return pctx;
        }()} {
            ::js_std_add_helpers(this->pctx, 0, NULL);
        }
        ~Context() {
            ::JS_FreeContext(this->pctx);
        }

        auto Eval(const std::string_view code) const;
};

class Value {
        ::JSValue val;

        Value(::JSValue val): val{val} {}
        friend Context;
    public:
        Value(const Value& other) {
            this->val = ::JS_DupValue(NULL, other.val);
        }
        ~Value() {
            ::JS_FreeValue(NULL, this->val);
        }
};

inline auto Context::Eval(const std::string_view code) const {
    const auto val = ::JS_Eval(
        this->pctx,
        code.data(), code.length(),
        "<input>",
        JS_EVAL_TYPE_GLOBAL
    );
    return Value{val};
}

%>
