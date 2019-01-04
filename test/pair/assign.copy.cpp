// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/first.hpp>
#include <parmexpr/hana/pair.hpp>
#include <parmexpr/hana/second.hpp>
namespace hana = parmexpr::hana;


constexpr auto in_constexpr_context(int a, short b) {
    hana::pair<int, short> p1(a, b);
    hana::pair<int, short> p2;
    hana::pair<double, long> p3;
    p2 = p1;
    p3 = p2;
    return p3;
}

int main() {
    {
        hana::pair<int, short> p1(3, 4);
        hana::pair<double, long> p2;
        p2 = p1;
        BOOST_HANA_RUNTIME_CHECK(hana::first(p2) == 3);
        BOOST_HANA_RUNTIME_CHECK(hana::second(p2) == 4);
    }

    // make sure that also works in a constexpr context
    // (test fails under GCC <= 6 due to buggy constexpr)
#if BOOST_HANA_CONFIG_GCC >= BOOST_HANA_CONFIG_VERSION(7, 0, 0)
    {
        constexpr auto p = in_constexpr_context(3, 4);
        static_assert(hana::first(p) == 3, "");
        static_assert(hana::second(p) == 4, "");
    }
#endif
}
