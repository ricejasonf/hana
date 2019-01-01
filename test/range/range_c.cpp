// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/core/make.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/range.hpp>
namespace hana = parmexpr::hana;


int main() {
    using T = int;
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::range_c<T, 0, 0>,
        hana::make_range(hana::integral_c<T, 0>, hana::integral_c<T, 0>)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::range_c<T, 0, 1>,
        hana::make_range(hana::integral_c<T, 0>, hana::integral_c<T, 1>)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::range_c<T, 0, 2>,
        hana::make_range(hana::integral_c<T, 0>, hana::integral_c<T, 2>)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::range_c<T, 1, 1>,
        hana::make_range(hana::integral_c<T, 1>, hana::integral_c<T, 1>)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::range_c<T, 1, 2>,
        hana::make_range(hana::integral_c<T, 1>, hana::integral_c<T, 2>)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::range_c<T, 1, 3>,
        hana::make_range(hana::integral_c<T, 1>, hana::integral_c<T, 3>)
    ));
}
