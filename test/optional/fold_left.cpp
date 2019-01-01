// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/fold_left.hpp>
#include <parmexpr/hana/optional.hpp>

#include <laws/base.hpp>
namespace hana = parmexpr::hana;


int main() {
    hana::test::ct_eq<2> x{};
    hana::test::ct_eq<3> s{};
    hana::test::_injection<0> f{};

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::fold_left(hana::just(x), s, f),
        f(s, x)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::fold_left(hana::nothing, s, f),
        s
    ));
}
