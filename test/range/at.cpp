// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/at.hpp>
#include <parmexpr/hana/core/make.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/range.hpp>
namespace hana = parmexpr::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::make_range(hana::int_c<0>, hana::int_c<10>)[hana::int_c<2>],
        hana::int_c<2>
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::at(hana::make_range(hana::int_c<0>, hana::int_c<1>), hana::int_c<0>),
        hana::int_c<0>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::at(hana::make_range(hana::int_c<0>, hana::int_c<2>), hana::int_c<0>),
        hana::int_c<0>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::at(hana::make_range(hana::int_c<0>, hana::int_c<2>), hana::int_c<1>),
        hana::int_c<1>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::at(hana::make_range(hana::int_c<4>, hana::int_c<90>), hana::int_c<46>),
        hana::int_c<50>
    ));
}
