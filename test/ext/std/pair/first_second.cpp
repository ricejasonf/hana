// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/ext/std/pair.hpp>
#include <parmexpr/hana/first.hpp>
#include <parmexpr/hana/second.hpp>

#include <laws/base.hpp>

#include <utility>
namespace hana = parmexpr::hana;
using hana::test::ct_eq;


int main() {
    // first
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::first(std::make_pair(ct_eq<0>{}, ct_eq<1>{})),
        ct_eq<0>{}
    ));

    // second
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::second(std::make_pair(ct_eq<0>{}, ct_eq<1>{})),
        ct_eq<1>{}
    ));
}
