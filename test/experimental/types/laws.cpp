// Copyright Louis Dionne 2013-2016
// Copyright Jason Rice 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <boost/hana/experimental/types.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>

#include <laws/base.hpp>
#include <laws/comparable.hpp>
#include <laws/foldable.hpp>
#include <laws/iterable.hpp>
#include <laws/monad.hpp>
//#include <laws/monadplus.hpp>
namespace hana = boost::hana;
namespace hanaxp = boost::hana::experimental;
using hana::test::ct_eq;

template <int i>
using ct_t = hana::type<ct_eq<i>>;

int main() {
    auto eqs = hana::make_tuple(
          hanaxp::make_types()
        , hanaxp::make_types(ct_t<0>{})
        , hanaxp::make_types(ct_t<0>{}, ct_t<1>{})
        , hanaxp::make_types(ct_t<0>{}, ct_t<1>{}, ct_t<2>{})
    );

    auto nested_eqs = hana::make_tuple(
        hanaxp::make_types(
              hanaxp::make_types()
            , hanaxp::make_types(ct_t<0>{})
            , hanaxp::make_types(ct_t<0>{}, ct_t<1>{})
            , hanaxp::make_types(ct_t<0>{}, ct_t<1>{}, ct_t<2>{})
        )
    );


    hana::test::TestComparable<hana::experimental::types_tag>{eqs};
    hana::test::TestFoldable<hana::experimental::types_tag>{eqs};
    hana::test::TestIterable<hana::experimental::types_tag>{eqs};
    hana::test::TestMonad<hana::experimental::types_tag>{eqs, nested_eqs};
//    hana::test::TestMonadPlus<hana::experimental::types_tag>{eqs};
}
