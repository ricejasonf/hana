// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/tuple.hpp>

#include <parmexpr/hana/tuple.hpp>

#include <laws/applicative.hpp>
#include <laws/base.hpp>
#include <laws/functor.hpp>
#include <laws/monad.hpp>

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
    );

    auto eq_values = hana::make_tuple(eq<0>{}, eq<2>{});

    auto eq_tuples_tuples = hana::make_tuple(
          ::parmexpr::make_tuple()
        , ::parmexpr::make_tuple(
            ::parmexpr::make_tuple(eq<0>{}))
        , ::parmexpr::make_tuple(
            ::parmexpr::make_tuple(eq<0>{}),
            ::parmexpr::make_tuple(eq<1>{}, eq<2>{}))
        , ::parmexpr::make_tuple(
            ::parmexpr::make_tuple(eq<0>{}),
            ::parmexpr::make_tuple(eq<1>{}, eq<2>{}),
            ::parmexpr::make_tuple(eq<3>{}, eq<4>{}))
    );

    //////////////////////////////////////////////////////////////////////////
    // Functor up to Monad
    //////////////////////////////////////////////////////////////////////////
    hana::test::TestFunctor<hana::ext::parmexpr::tuple_tag>{eq_tuples, eq_values};
    hana::test::TestApplicative<hana::ext::parmexpr::tuple_tag>{eq_tuples};
    hana::test::TestMonad<hana::ext::parmexpr::tuple_tag>{eq_tuples, eq_tuples_tuples};
}
