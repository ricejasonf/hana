// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/optional.hpp>

#include <laws/base.hpp>
namespace hana = parmexpr::hana;
using hana::test::ct_eq;


int main() {
    auto lvalue = hana::just(ct_eq<3>{});
    ct_eq<3>& ref = *lvalue;
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        ref,
        ct_eq<3>{}
    ));

    auto const const_lvalue = hana::just(ct_eq<3>{});
    ct_eq<3> const& const_ref = *const_lvalue;
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        const_ref,
        ct_eq<3>{}
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        *hana::just(ct_eq<3>{}),
        ct_eq<3>{}
    ));
}
