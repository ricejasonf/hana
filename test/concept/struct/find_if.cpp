// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/concept/struct.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/find_if.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/optional.hpp>

#include "minimal_struct.hpp"
#include <laws/base.hpp>
namespace hana = parmexpr::hana;
using hana::test::ct_eq;


template <int i = 0>
struct undefined { };

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(obj(), undefined<>{}),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(obj(ct_eq<0>{}), hana::equal.to(hana::int_c<0>)),
        hana::just(ct_eq<0>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(obj(undefined<1>{}), hana::equal.to(hana::int_c<1>)),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(obj(ct_eq<0>{}, ct_eq<1>{}), hana::equal.to(hana::int_c<0>)),
        hana::just(ct_eq<0>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(obj(ct_eq<0>{}, ct_eq<1>{}), hana::equal.to(hana::int_c<1>)),
        hana::just(ct_eq<1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(obj(undefined<0>{}, undefined<1>{}), hana::equal.to(hana::int_c<2>)),
        hana::nothing
    ));
}
