// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/ext/std/ratio.hpp>
#include <parmexpr/hana/not.hpp>

#include <ratio>
namespace hana = parmexpr::hana;


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        std::ratio<0>{},
        std::ratio<0>{}
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        std::ratio<3>{},
        std::ratio<3>{}
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        std::ratio<3, 5>{},
        std::ratio<6, 10>{}
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(
        std::ratio<4, 5>{},
        std::ratio<6, 10>{}
    )));
}
