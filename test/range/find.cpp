// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/core/make.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/find.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/optional.hpp>
#include <parmexpr/hana/range.hpp>

#include <support/cnumeric.hpp>
namespace hana = parmexpr::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(hana::make_range(hana::int_c<0>, hana::int_c<0>), cnumeric<int, 0>),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(hana::make_range(hana::int_c<0>, hana::int_c<1>), cnumeric<int, 0>),
        hana::just(hana::int_c<0>)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(hana::make_range(hana::int_c<0>, hana::int_c<10>), cnumeric<int, 3>),
        hana::just(hana::int_c<3>)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(hana::make_range(hana::int_c<0>, hana::int_c<10>), cnumeric<int, 9>),
        hana::just(hana::int_c<9>)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(hana::make_range(hana::int_c<-10>, hana::int_c<10>), cnumeric<int, -10>),
        hana::just(hana::int_c<-10>)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(hana::make_range(hana::int_c<-10>, hana::int_c<10>), cnumeric<int, -5>),
        hana::just(hana::int_c<-5>)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(hana::make_range(hana::int_c<-10>, hana::int_c<0>), cnumeric<int, 3>),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find(hana::make_range(hana::int_c<0>, hana::int_c<10>), cnumeric<int, 15>),
        hana::nothing
    ));
}
