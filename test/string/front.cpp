// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/front.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/string.hpp>
namespace hana = parmexpr::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::front(BOOST_HANA_STRING("a")),
        hana::char_c<'a'>
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::front(BOOST_HANA_STRING("ab")),
        hana::char_c<'a'>
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::front(BOOST_HANA_STRING("abc")),
        hana::char_c<'a'>
    ));
}
