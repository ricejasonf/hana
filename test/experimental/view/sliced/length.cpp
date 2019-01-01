// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/experimental/view.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/length.hpp>
#include <parmexpr/hana/tuple.hpp>

#include <support/seq.hpp>
namespace hana = parmexpr::hana;


template <int> struct undefined { };

int main() {
    auto container = ::seq;

    {
        auto storage = container();
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::length(sliced),
            hana::size_c<0>
        ));
    }

    {
        auto storage = container(undefined<0>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 0>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::length(sliced),
            hana::size_c<1>
        ));
    }{
        auto storage = container(undefined<0>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::length(sliced),
            hana::size_c<0>
        ));
    }

    {
        auto storage = container(undefined<0>{}, undefined<1>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 0>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::length(sliced),
            hana::size_c<1>
        ));
    }{
        auto storage = container(undefined<0>{}, undefined<1>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 0, 1>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::length(sliced),
            hana::size_c<2>
        ));
    }{
        auto storage = container(undefined<0>{}, undefined<1>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 0, 0>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::length(sliced),
            hana::size_c<2>
        ));
    }
}
