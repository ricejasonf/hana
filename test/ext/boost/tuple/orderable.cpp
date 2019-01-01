// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/tuple.hpp>

#include <parmexpr/hana/tuple.hpp>

#include <laws/comparable.hpp>
#include <laws/orderable.hpp>

#include <parmexpr/tuple/tuple.hpp>
namespace hana = parmexpr::hana;


template <int i>
using eq = hana::test::ct_eq<i>;

template <int i>
using ord = hana::test::ct_ord<i>;

int main() {
    //////////////////////////////////////////////////////////////////////////
    // Setup for the laws below
    //////////////////////////////////////////////////////////////////////////
    auto eq_tuples = hana::make_tuple(
          ::parmexpr::make_tuple()
        , ::parmexpr::make_tuple(eq<0>{})
        , ::parmexpr::make_tuple(eq<0>{}, eq<1>{})
        , ::parmexpr::make_tuple(eq<0>{}, eq<1>{}, eq<2>{})
        , ::parmexpr::make_tuple(eq<0>{}, eq<1>{}, eq<2>{}, eq<3>{}, eq<4>{})
    );

    auto ord_tuples = hana::make_tuple(
          ::parmexpr::make_tuple()
        , ::parmexpr::make_tuple(ord<0>{})
        , ::parmexpr::make_tuple(ord<0>{}, ord<1>{})
        , ::parmexpr::make_tuple(ord<0>{}, ord<1>{}, ord<2>{})
        , ::parmexpr::make_tuple(ord<0>{}, ord<1>{}, ord<2>{}, ord<3>{}, ord<4>{})
    );

    //////////////////////////////////////////////////////////////////////////
    // Comparable and Orderable
    //////////////////////////////////////////////////////////////////////////
    hana::test::TestComparable<hana::ext::parmexpr::tuple_tag>{eq_tuples};
    hana::test::TestOrderable<hana::ext::parmexpr::tuple_tag>{ord_tuples};
}
