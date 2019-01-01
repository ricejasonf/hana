// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/type.hpp>
namespace hana = parmexpr::hana;


struct T { };

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::alignof_(T{}),
        hana::size_c<alignof(T)>
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::alignof_(hana::type_c<T>),
        hana::size_c<alignof(T)>
    ));

    // make sure we don't read from non-constexpr variables
    {
        auto t = hana::type_c<T>;
        auto x = 1;
        constexpr auto r1 = hana::alignof_(t); (void)r1;
        constexpr auto r2 = hana::alignof_(x); (void)r2;
    }
}
