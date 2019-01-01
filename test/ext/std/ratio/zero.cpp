// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/ext/std/ratio.hpp>
#include <parmexpr/hana/zero.hpp>

#include <ratio>
namespace hana = parmexpr::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::zero<hana::ext::std::ratio_tag>(),
        std::ratio<0, 1>{}
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::zero<hana::ext::std::ratio_tag>(),
        std::ratio<0, 2>{}
    ));
}
