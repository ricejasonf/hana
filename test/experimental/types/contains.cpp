// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/contains.hpp>
#include <parmexpr/hana/experimental/types.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/type.hpp>
namespace hana = parmexpr::hana;


template <int> struct x;
struct undefined { };

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::contains(
        hana::experimental::types<>{},
        undefined{}
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        hana::experimental::types<x<0>>{},
        hana::type_c<x<0>>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::contains(
        hana::experimental::types<x<0>>{},
        hana::type_c<x<999>>
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        hana::experimental::types<x<0>, x<1>>{},
        hana::type_c<x<0>>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        hana::experimental::types<x<0>, x<1>>{},
        hana::type_c<x<1>>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::contains(
        hana::experimental::types<x<0>, x<1>>{},
        hana::type_c<x<999>>
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        hana::experimental::types<x<0>, x<1>, x<2>>{},
        hana::type_c<x<0>>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        hana::experimental::types<x<0>, x<1>, x<2>>{},
        hana::type_c<x<1>>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        hana::experimental::types<x<0>, x<1>, x<2>>{},
        hana::type_c<x<2>>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::contains(
        hana::experimental::types<x<0>, x<1>, x<2>>{},
        hana::type_c<x<999>>
    )));

    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        hana::experimental::types<x<0>, x<1>, x<2>, x<3>>{},
        hana::type_c<x<0>>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        hana::experimental::types<x<0>, x<1>, x<2>, x<3>>{},
        hana::type_c<x<1>>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        hana::experimental::types<x<0>, x<1>, x<2>, x<3>>{},
        hana::type_c<x<2>>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::contains(
        hana::experimental::types<x<0>, x<1>, x<2>, x<3>>{},
        hana::type_c<x<3>>
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::contains(
        hana::experimental::types<x<0>, x<1>, x<2>, x<3>>{},
        hana::type_c<x<999>>
    )));
}
