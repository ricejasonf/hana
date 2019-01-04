// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/concept/struct.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/keys.hpp>

#include "minimal_struct.hpp"
#include <laws/base.hpp>
#include <support/seq.hpp>
namespace hana = parmexpr::hana;
using hana::test::ct_eq;


template <int i = 0>
struct undefined { };

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::keys(obj()),
        ::seq()
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::keys(obj(undefined<0>{})),
        ::seq(hana::int_c<0>)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::keys(obj(undefined<0>{}, undefined<1>{})),
        ::seq(hana::int_c<0>, hana::int_c<1>)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::keys(obj(undefined<0>{}, undefined<1>{}, undefined<2>{})),
        ::seq(hana::int_c<0>, hana::int_c<1>, hana::int_c<2>)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::keys(obj(undefined<0>{}, undefined<1>{}, undefined<2>{}, undefined<3>{})),
        ::seq(hana::int_c<0>, hana::int_c<1>, hana::int_c<2>, hana::int_c<3>)
    ));
}
