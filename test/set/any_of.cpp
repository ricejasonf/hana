// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/any_of.hpp>
#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/set.hpp>

#include <laws/base.hpp>
namespace hana = parmexpr::hana;
using hana::test::ct_eq;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::any_of(
        hana::make_set(),
        hana::equal.to(ct_eq<1>{})
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::any_of(
        hana::make_set(ct_eq<1>{}),
        hana::equal.to(ct_eq<1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::any_of(
        hana::make_set(ct_eq<1>{}),
        hana::equal.to(ct_eq<2>{})
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::any_of(
        hana::make_set(ct_eq<1>{}, ct_eq<2>{}),
        hana::equal.to(ct_eq<1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::any_of(
        hana::make_set(ct_eq<1>{}, ct_eq<2>{}),
        hana::equal.to(ct_eq<2>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::any_of(
        hana::make_set(ct_eq<1>{}, ct_eq<2>{}),
        hana::equal.to(ct_eq<3>{})
    )));
}
