// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/div.hpp>
#include <parmexpr/hana/mod.hpp>
#include <parmexpr/hana/tuple.hpp>

#include <laws/euclidean_ring.hpp>
namespace hana = parmexpr::hana;


int main() {
    hana::test::TestEuclideanRing<int>{hana::make_tuple(0,1,2,3,4,5)};
    hana::test::TestEuclideanRing<long>{hana::make_tuple(0l,1l,2l,3l,4l,5l)};

    // div
    {
        static_assert(hana::div(6, 4) == 6 / 4, "");
        static_assert(hana::div(7, -3) == 7 / -3, "");
    }

    // mod
    {
        static_assert(hana::mod(6, 4) == 6 % 4, "");
        static_assert(hana::mod(7, -3) == 7 % -3, "");
    }
}
