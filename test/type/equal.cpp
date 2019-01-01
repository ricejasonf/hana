// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/not_equal.hpp> // for operator !=
#include <parmexpr/hana/type.hpp>
namespace hana = parmexpr::hana;


struct T;
struct U;

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(hana::type_c<T>, hana::type_c<T>));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(hana::type_c<T>, hana::type_c<U>)));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(hana::type_c<void>, hana::type_c<U>)));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(hana::type_c<T>, hana::type_c<void>)));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(hana::type_c<void>, hana::type_c<void>));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(hana::type_c<T&>, hana::type_c<T&>));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(hana::type_c<T&>, hana::type_c<T&&>)));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(hana::type_c<T const>, hana::type_c<T>)));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(hana::type_c<T const>, hana::type_c<T const>));

    // make sure we don't read from a non-constexpr variable in hana::equal
    auto t = hana::type_c<T>;
    static_assert(hana::equal(t, hana::type_c<T>), "");

    // check operators
    BOOST_HANA_CONSTANT_CHECK(hana::type_c<T> == hana::type_c<T>);
    BOOST_HANA_CONSTANT_CHECK(hana::type_c<T> != hana::type_c<U>);
}
