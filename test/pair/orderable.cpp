// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/greater.hpp>
#include <parmexpr/hana/greater_equal.hpp>
#include <parmexpr/hana/less.hpp>
#include <parmexpr/hana/less_equal.hpp>
#include <parmexpr/hana/pair.hpp>
#include <parmexpr/hana/tuple.hpp>

#include <laws/base.hpp>
#include <laws/orderable.hpp>
namespace hana = parmexpr::hana;
using hana::test::ct_ord;


int main() {
    BOOST_HANA_CONSTANT_CHECK(
        hana::make_pair(ct_ord<1>{}, ct_ord<2>{}) <
        hana::make_pair(ct_ord<3>{}, ct_ord<2>{})
    );

    BOOST_HANA_CONSTANT_CHECK(
        hana::make_pair(ct_ord<1>{}, ct_ord<2>{}) <=
        hana::make_pair(ct_ord<3>{}, ct_ord<2>{})
    );

    BOOST_HANA_CONSTANT_CHECK(
        hana::make_pair(ct_ord<3>{}, ct_ord<2>{}) >=
        hana::make_pair(ct_ord<1>{}, ct_ord<2>{})
    );

    BOOST_HANA_CONSTANT_CHECK(
        hana::make_pair(ct_ord<3>{}, ct_ord<2>{}) >
        hana::make_pair(ct_ord<1>{}, ct_ord<2>{})
    );

    hana::test::TestOrderable<hana::pair_tag>{hana::make_tuple(
          hana::make_pair(ct_ord<3>{}, ct_ord<3>{})
        , hana::make_pair(ct_ord<3>{}, ct_ord<4>{})
        , hana::make_pair(ct_ord<4>{}, ct_ord<3>{})
        , hana::make_pair(ct_ord<4>{}, ct_ord<4>{})
    )};
}
