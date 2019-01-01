// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/is_subset.hpp>
#include <parmexpr/hana/map.hpp>
#include <parmexpr/hana/not.hpp>

#include <laws/base.hpp>
#include <support/minimal_product.hpp>
namespace hana = parmexpr::hana;


template <int i>
auto key() { return hana::test::ct_eq<i>{}; }

template <int i>
auto val() { return hana::test::ct_eq<-i>{}; }

template <int i, int j>
auto p() { return ::minimal_product(key<i>(), val<j>()); }

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::is_subset(
        hana::make_map(),
        hana::make_map()
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::is_subset(
        hana::make_map(),
        hana::make_map(p<1, 1>())
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::is_subset(
        hana::make_map(),
        hana::make_map(p<1, 1>(), p<2, 2>())
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::is_subset(
        hana::make_map(p<1, 1>()),
        hana::make_map(p<1, 1>(), p<2, 2>())
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::is_subset(
        hana::make_map(p<2, 2>(), p<1, 1>()),
        hana::make_map(p<1, 1>(), p<2, 2>())
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::is_subset(
        hana::make_map(p<3, 3>(), p<1, 1>()),
        hana::make_map(p<1, 1>(), p<2, 2>())
    )));
}
