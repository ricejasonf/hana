// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/tuple.hpp>

#include <parmexpr/hana/bool.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/functional/always.hpp>
#include <parmexpr/hana/tuple.hpp>

#include <laws/base.hpp>
#include <laws/monad_plus.hpp>

#include <parmexpr/tuple/tuple.hpp>
namespace hana = parmexpr::hana;


template <int i>
using eq = hana::test::ct_eq<i>;

int main() {
    //////////////////////////////////////////////////////////////////////////
    // Setup for the laws below
    //////////////////////////////////////////////////////////////////////////
    auto eq_tuples = hana::make_tuple(
          ::parmexpr::make_tuple(eq<0>{})
        , ::parmexpr::make_tuple(eq<0>{}, eq<1>{})
        , ::parmexpr::make_tuple(eq<0>{}, eq<1>{}, eq<2>{})
    );

    auto eq_values = hana::make_tuple(eq<0>{}, eq<1>{}, eq<2>{});
    auto predicates = hana::make_tuple(
        hana::equal.to(eq<0>{}), hana::equal.to(eq<1>{}), hana::equal.to(eq<2>{}),
        hana::always(hana::false_c), hana::always(hana::true_c)
    );

    //////////////////////////////////////////////////////////////////////////
    // MonadPlus
    //////////////////////////////////////////////////////////////////////////
    hana::test::TestMonadPlus<hana::ext::parmexpr::tuple_tag>{eq_tuples, predicates, eq_values};
}
