/*
 * Copyright (C) 2025-2026  Xie Qi
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, version 2.0.  If a copy of the MPL was not distributed with
 * this file, You can obtain one at <http://mozilla.org/MPL/2.0/>.
 */

/* clang-format off */

#pragma once
#include <string>
#include <type_traits>
#include <stdexcept>
#include <format>
#include <variant>
#include <optional>
#include <memory>
using namespace std::literals;
#include "quickjs.h"
#include "quickjs-libc.h"

namespace quickjsxx <%

class Runtime;
class Context;
class Value;

class Runtime: public std::enable_shared_from_this<Runtime> {
        std::remove_pointer_t<decltype(::JS_NewRuntime())> *const prt;
        friend Context;

        Runtime();
    public:
        ~Runtime();
        static auto Create(auto&&...) -> std::shared_ptr<Runtime>;
};

class Context: public std::enable_shared_from_this<Context> {
        const std::shared_ptr<Runtime> rt;
        std::remove_pointer_t<decltype(::JS_NewContext(NULL))> *const pctx;
        friend Value;

        Context(const std::shared_ptr<Runtime> rt);
    public:
        ~Context();
        static auto Create(auto&&...) -> std::shared_ptr<Context>;

        auto Eval(const std::string& code) -> Value;
};

class Value {
        std::weak_ptr<Context> ctx;
        ::JSValue val;

        Value(const std::shared_ptr<Context> ctx, const ::JSValue val);
        friend Context;
    public:
        Value(const Value&);
        friend void swap(Value&, Value&);
        auto& operator=(Value);
        ~Value();

        auto await() -> decltype(*this);

        auto GetValue() const -> std::variant<
            std::monostate,  // undefined
            std::nullptr_t,  // null
            bool,
            double,  // Number
            std::string,
            std::intmax_t,  // BigInt
            const void *
        >;
};

%>

inline
auto quickjsxx::Value::await() -> decltype(*this) {
    const auto ctx = this->ctx.lock();

    this->val = ::js_std_await(ctx->pctx, this->val);
    if (::JS_IsException(this->val))
        ::js_std_dump_error(ctx->pctx);

    return *this;
}

inline
auto quickjsxx::Value::GetValue() const -> std::variant<
    std::monostate,
    std::nullptr_t,
    bool,
    double,
    std::string,
    std::intmax_t,
    const void *
> {
    if (::JS_IsNumber(this->val)) {
        double number;
        ::JS_ToFloat64(this->ctx.lock()->pctx, &number, this->val);
        return number;
    }

    if (::JS_IsBigInt(this->ctx.lock()->pctx, this->val)) {
        std::int64_t bigint;
        ::JS_ToBigInt64(this->ctx.lock()->pctx, &bigint, this->val);
        return static_cast<std::intmax_t>(bigint);
    }

    if (::JS_IsBool(this->val)) {
        return JS_VALUE_GET_BOOL(this->val) != 0;
    }

    if (::JS_IsNull(this->val)) {
        return nullptr;
    }

    if (::JS_IsUndefined(this->val)) {
        return std::monostate{};
    }

    if (::JS_IsException(this->val)) {
        throw std::runtime_error{"quickjsxx: JS Exception Value"};
    }

    if (::JS_IsUninitialized(this->val)) {
        throw std::runtime_error{"quickjsxx: JS Uninitialized Value"};
    }

    if (::JS_IsString(this->val)) {
        const auto ctx = this->ctx.lock();

        const char *const cstr = ::JS_ToCString(ctx->pctx, this->val);
        const auto string = std::string{cstr};
        ::JS_FreeCString(ctx->pctx, cstr);

        return string;
    }

    if (::JS_IsSymbol(this->val)) {
        throw std::runtime_error{"quickjsxx: JS Symbol Value"};
    }

    if (::JS_IsObject(this->val)) {
        return JS_VALUE_GET_PTR(this->val);
    }

    throw std::runtime_error{
        std::format(
            "quickjsxx: Unknown ::JSValue Tag: {}",
            JS_VALUE_GET_TAG(this->val)
        )
    };
}


inline
auto quickjsxx::Context::Create(auto&&... args) -> std::shared_ptr<Context> {
    const auto ctx = std::shared_ptr<Context>{new Context{std::forward<decltype(args)>(args)...}};

    auto promise = ctx->Eval(
        R"(
            0, async function() {
                globalThis.std = await import('std')
                globalThis.os = await import('os')
            }()
        )"
    );
    promise.await();

    ctx->Eval(
        R"(
            globalThis.setTimeout = os.setTimeout
            globalThis.setInterval = os.setInterval
        )"
    );

    return ctx;
}

inline
auto& quickjsxx::Value::operator=(Value other) {
    swap(*this, other);
    return *this;
}

inline
void quickjsxx::swap(Value& a, Value& b) {
    using std::swap;
    swap(a.ctx, b.ctx);
    swap(a.val, b.val);
}

inline
quickjsxx::Value::~Value() {
    ::JS_FreeValue(this->ctx.lock()->pctx, this->val);
}

inline
quickjsxx::Value::Value(const Value& other):
ctx{other.ctx},
val{
    ::JS_DupValue(other.ctx.lock()->pctx, other.val)
} {}

inline
quickjsxx::Value::Value(const std::shared_ptr<quickjsxx::Context> ctx, ::JSValue val):
ctx{ctx},
val{val} {}

inline
quickjsxx::Context::~Context() {
    ::JS_FreeContext(this->pctx);
}

inline
auto quickjsxx::Context::Eval(const std::string& code)
-> quickjsxx::Value {
    const auto val = ::JS_Eval(
        this->pctx,
        code.c_str(), code.length(),
        ("<"s + __func__ + ">").c_str(),
        JS_EVAL_TYPE_GLOBAL
    );
    if (::JS_IsException(val))
        ::js_std_dump_error(this->pctx);

    return {this->shared_from_this(), val};
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
    ::js_init_module_std(this->pctx, "std");
    ::js_init_module_os(this->pctx, "os");

    ::js_std_add_helpers(this->pctx, 0, NULL);
}

inline
quickjsxx::Runtime::Runtime():
prt{[] {
    const auto prt = ::JS_NewRuntime();
    if (!prt)
        throw std::runtime_error{"Failed to create QuickJS runtime"};
    return prt;
}()} {
    ::js_std_init_handlers(this->prt);

    ::JS_SetModuleLoaderFunc2(
        this->prt,
        NULL,
        ::js_module_loader,
        ::js_module_check_attributes,
        NULL
    );
}

inline
quickjsxx::Runtime::~Runtime() {
    ::JS_FreeRuntime(this->prt);
}

inline
auto quickjsxx::Runtime::Create(auto&&... args) -> std::shared_ptr<Runtime> {
    return std::shared_ptr<Runtime>{new Runtime{std::forward<decltype(args)>(args)...}};
}
