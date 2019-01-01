// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/not_equal.hpp> // for operator !=
#include <parmexpr/hana/string.hpp>
namespace hana = parmexpr::hana;


int main() {
    // equal
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        BOOST_HANA_STRING("abcd"),
        BOOST_HANA_STRING("abcd")
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(
        BOOST_HANA_STRING("abcd"),
        BOOST_HANA_STRING("abcde")
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(
        BOOST_HANA_STRING("abcd"),
        BOOST_HANA_STRING("")
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(
        BOOST_HANA_STRING(""),
        BOOST_HANA_STRING("abcde")
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        BOOST_HANA_STRING(""),
        BOOST_HANA_STRING("")
    ));

    // check operators
    BOOST_HANA_CONSTANT_CHECK(
        BOOST_HANA_STRING("abcd")
            ==
        BOOST_HANA_STRING("abcd")
    );

    BOOST_HANA_CONSTANT_CHECK(
        BOOST_HANA_STRING("abcd")
            !=
        BOOST_HANA_STRING("abc")
    );
}
