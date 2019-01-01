// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/ext/std/tuple.hpp>
#include <parmexpr/hana/lift.hpp>

#include <tuple>
namespace hana = parmexpr::hana;


int main() {
    // Make sure we workaround the bug at:
    // http://llvm.org/bugs/show_bug.cgi?id=19616
    BOOST_HANA_CONSTEXPR_CHECK(hana::equal(
        hana::lift<hana::ext::std::tuple_tag>(std::make_tuple(1)),
        std::make_tuple(std::make_tuple(1))
    ));
}
