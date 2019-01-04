// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/bool.hpp>
#include <parmexpr/hana/eval_if.hpp>
#include <parmexpr/hana/fwd/not.hpp>
#include <parmexpr/hana/fwd/while.hpp>
#include <parmexpr/hana/if.hpp>
namespace hana = parmexpr::hana;


// This test makes sure that if_ can be used with non-copyable branches.

template <bool Value>
struct Boolean { };

namespace parmexpr { namespace hana {
    template <bool Value>
    struct while_impl<Boolean<Value>> {
        // Not implemented
    };

    template <bool Value>
    struct not_impl<Boolean<Value>> {
        // Not implemented
    };

    template <bool Value>
    struct eval_if_impl<Boolean<Value>> {
        template <typename Cond, typename Then, typename Else>
        static constexpr decltype(auto) apply(Cond const&, Then&& t, Else&& e) {
            return hana::eval_if(hana::bool_c<Value>, static_cast<Then&&>(t),
                                                      static_cast<Else&&>(e));
        }
    };
}}

template <int v>
struct NonCopyable {
    static constexpr int value = v;
    NonCopyable() = default;
    NonCopyable(NonCopyable const&) = delete;
    NonCopyable(NonCopyable&&) = default;

    NonCopyable& operator=(NonCopyable const&) = delete;
    NonCopyable& operator=(NonCopyable&&) = default;
};

static_assert(hana::if_(Boolean<true>{}, NonCopyable<3>{}, NonCopyable<4>{}).value == 3, "");
static_assert(hana::if_(Boolean<false>{}, NonCopyable<3>{}, NonCopyable<4>{}).value == 4, "");

int main() { }
