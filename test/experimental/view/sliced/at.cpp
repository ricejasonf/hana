// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/at.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/experimental/view.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/tuple.hpp>

#include <laws/base.hpp>
#include <support/seq.hpp>
namespace hana = parmexpr::hana;
using hana::test::ct_eq;


int main() {
    auto container = ::seq;

    {
        auto storage = container(ct_eq<0>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 0>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<0>),
            ct_eq<0>{}
        ));
    }

    {
        auto storage = container(ct_eq<0>{}, ct_eq<1>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 0>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<0>),
            ct_eq<0>{}
        ));
    }{
        auto storage = container(ct_eq<0>{}, ct_eq<1>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 1>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<0>),
            ct_eq<1>{}
        ));
    }{
        auto storage = container(ct_eq<0>{}, ct_eq<1>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 0, 1>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<0>),
            ct_eq<0>{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<1>),
            ct_eq<1>{}
        ));
    }{
        auto storage = container(ct_eq<0>{}, ct_eq<1>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 1, 0>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<0>),
            ct_eq<1>{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<1>),
            ct_eq<0>{}
        ));
    }{
        auto storage = container(ct_eq<0>{}, ct_eq<1>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 0, 0>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<0>),
            ct_eq<0>{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<1>),
            ct_eq<0>{}
        ));
    }

    {
        auto storage = container(ct_eq<0>{}, ct_eq<1>{}, ct_eq<2>{}, ct_eq<3>{});
        auto sliced = hana::experimental::sliced(storage, hana::tuple_c<int, 1, 3>);
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<0>),
            ct_eq<1>{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at(sliced, hana::size_c<1>),
            ct_eq<3>{}
        ));
    }
}
