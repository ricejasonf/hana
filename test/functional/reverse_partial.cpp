// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/functional/reverse_partial.hpp>

#include <laws/base.hpp>
namespace hana = parmexpr::hana;
using hana::test::ct_eq;


int main() {
    constexpr auto rp = hana::reverse_partial;
    hana::test::_injection<0> f{};

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f)(),
        f()
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f)(ct_eq<1>{}),
        f(ct_eq<1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f)(ct_eq<1>{}, ct_eq<2>{}),
        f(ct_eq<1>{}, ct_eq<2>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f)(ct_eq<1>{}, ct_eq<2>{}, ct_eq<3>{}),
        f(ct_eq<1>{}, ct_eq<2>{}, ct_eq<3>{})
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f, ct_eq<1>{})(),
        f(ct_eq<1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f, ct_eq<1>{})(ct_eq<2>{}),
        f(ct_eq<2>{}, ct_eq<1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f, ct_eq<1>{})(ct_eq<2>{}, ct_eq<3>{}),
        f(ct_eq<2>{}, ct_eq<3>{}, ct_eq<1>{})
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f, ct_eq<1>{}, ct_eq<2>{})(),
        f(ct_eq<1>{}, ct_eq<2>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f, ct_eq<1>{}, ct_eq<2>{})(ct_eq<3>{}),
        f(ct_eq<3>{}, ct_eq<1>{}, ct_eq<2>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f, ct_eq<1>{}, ct_eq<2>{})(ct_eq<3>{}, ct_eq<4>{}),
        f(ct_eq<3>{}, ct_eq<4>{}, ct_eq<1>{}, ct_eq<2>{})
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        rp(f, ct_eq<1>{}, ct_eq<2>{}, ct_eq<3>{})(),
        f(ct_eq<1>{}, ct_eq<2>{}, ct_eq<3>{})
    ));
}
