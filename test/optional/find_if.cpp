// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/find_if.hpp>
#include <parmexpr/hana/optional.hpp>

#include <laws/base.hpp>
namespace hana = parmexpr::hana;
using hana::test::ct_eq;


int main() {
    ct_eq<2> x{};
    ct_eq<3> y{};

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(hana::just(x), hana::equal.to(x)),
        hana::just(x)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(hana::just(x), hana::equal.to(y)),
        hana::nothing
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(hana::nothing, hana::equal.to(x)),
        hana::nothing
    ));

    // Previously, there was a bug that would make this fail.
    auto non_const_nothing = hana::nothing;
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(non_const_nothing, hana::equal.to(x)),
        hana::nothing
    ));
}
