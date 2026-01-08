#pragma once
#include <string>
#include <type_traits>
#include <stdexcept>
#include <memory>
using namespace std::literals;
#include "quickjs.h"
#include "quickjs-libc.h"

namespace quickjsxx <%

class Runtime;
class Context;
using Realm = Context;
class Value;

class Runtime: std::enable_shared_from_this<Runtime> {
        std::remove_pointer_t<decltype(::JS_NewRuntime())> *const prt;
        friend Context;

        Runtime();
    public:
        ~Runtime();

        static auto Create() -> std::shared_ptr<Runtime>;
};

class Context {
        const std::shared_ptr<Runtime> rt;
        std::remove_pointer_t<decltype(::JS_NewContext(NULL))> *const pctx;
    public:
        Context(const std::shared_ptr<Runtime> rt);
        ~Context();

        auto Eval(const std::string_view code) const -> Value;
};

class Value {
        ::JSValue val;

        Value(::JSValue val);
        friend Context;
    public:
        Value(const Value&);
        friend void swap(Value&, Value&);
        auto& operator=(Value);
        ~Value();
};

%>

inline
auto& quickjsxx::Value::operator=(Value other) {
    swap(*this, other);
    return *this;
}

inline
void quickjsxx::swap(Value& a, Value& b) {
    using std::swap;
    swap(a.val, b.val);
}

inline
quickjsxx::Value::~Value() {
    ::JS_FreeValue(NULL, this->val);
}

inline
quickjsxx::Value::Value(const Value& other):
val{
    ::JS_DupValue(NULL, other.val)
} {}

inline
quickjsxx::Value::Value(::JSValue val):
val{
    val
} {}

inline
quickjsxx::Context::~Context() {
    ::JS_FreeContext(this->pctx);
}

inline
auto quickjsxx::Context::Eval(const std::string_view code) const -> quickjsxx::Value {
    const auto val = ::JS_Eval(
        this->pctx,
        code.data(), code.length(),
        "<input>",
        JS_EVAL_TYPE_GLOBAL
    );
    return Value{val};
}

inline
quickjsxx::Context::Context(const std::shared_ptr<Runtime> rt):
rt{rt},
pctx{[this] {
    const auto pctx = ::JS_NewContext(this->rt->prt);
        if (!pctx)
            throw std::runtime_error{"Failed to create QuickJS context"};
        return pctx;
}()} {
    ::js_std_add_helpers(this->pctx, 0, NULL);
}

inline
quickjsxx::Runtime::Runtime():
prt{[] {
    const auto prt = ::JS_NewRuntime();
    if (!prt)
        throw std::runtime_error{"Failed to create QuickJS runtime"};
    return prt;
}()} {}

inline
quickjsxx::Runtime::~Runtime() {
    ::JS_FreeRuntime(this->prt);
}

inline
auto quickjsxx::Runtime::Create() -> std::shared_ptr<Runtime> {
    return std::shared_ptr<Runtime>{new Runtime{}};
}
