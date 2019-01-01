// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/contains.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/string.hpp>
namespace hana = parmexpr::hana;


struct invalid { };

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        BOOST_HANA_STRING("abcd"),
        hana::char_c<'a'>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        BOOST_HANA_STRING("abcd"),
        hana::char_c<'c'>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::contains(
        BOOST_HANA_STRING("abcd"),
        hana::char_c<'e'>
    )));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::contains(
        BOOST_HANA_STRING("abcd"),
        invalid{}
    )));
}
