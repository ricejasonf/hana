// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/tuple.hpp>

#include <parmexpr/hana/bool.hpp>
#include <parmexpr/hana/tuple.hpp>

#include <laws/base.hpp>
#include <laws/searchable.hpp>

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

    auto eq_tuple_keys = hana::make_tuple(
        eq<3>{}, eq<5>{}, eq<7>{}
    );

    //////////////////////////////////////////////////////////////////////////
    // Searchable
    //////////////////////////////////////////////////////////////////////////
    {
        hana::test::TestSearchable<hana::ext::parmexpr::tuple_tag>{eq_tuples, eq_tuple_keys};

        auto bools = hana::make_tuple(
              ::parmexpr::make_tuple(hana::true_c)
            , ::parmexpr::make_tuple(hana::false_c)
            , ::parmexpr::make_tuple(hana::true_c, hana::true_c)
            , ::parmexpr::make_tuple(hana::true_c, hana::false_c)
            , ::parmexpr::make_tuple(hana::false_c, hana::true_c)
            , ::parmexpr::make_tuple(hana::false_c, hana::false_c)
        );
        hana::test::TestSearchable<hana::ext::parmexpr::tuple_tag>{
            bools,
            hana::make_tuple(hana::true_c, hana::false_c)
        };
    }
}
