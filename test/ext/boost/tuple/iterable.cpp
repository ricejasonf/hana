// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/tuple.hpp>

#include <parmexpr/hana/tuple.hpp>

#include <laws/base.hpp>
#include <laws/foldable.hpp>
#include <laws/iterable.hpp>

#include <parmexpr/tuple/tuple.hpp>
namespace hana = parmexpr::hana;


template <int i>
using eq = hana::test::ct_eq<i>;

int main() {
    //////////////////////////////////////////////////////////////////////////
    // Setup for the laws below
    //////////////////////////////////////////////////////////////////////////
    auto eq_tuples = hana::make_tuple(
          ::parmexpr::make_tuple()
        , ::parmexpr::make_tuple(eq<0>{})
        , ::parmexpr::make_tuple(eq<0>{}, eq<1>{})
        , ::parmexpr::make_tuple(eq<0>{}, eq<1>{}, eq<2>{})
    );

    //////////////////////////////////////////////////////////////////////////
    // Foldable, Iterable
    //////////////////////////////////////////////////////////////////////////
    hana::test::TestFoldable<hana::ext::parmexpr::tuple_tag>{eq_tuples};
    hana::test::TestIterable<hana::ext::parmexpr::tuple_tag>{eq_tuples};
}
