// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HANA_TEST_AUTO_DROP_WHILE_HPP
#define BOOST_HANA_TEST_AUTO_DROP_WHILE_HPP

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/bool.hpp>
#include <parmexpr/hana/drop_while.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/functional/id.hpp>
#include <parmexpr/hana/not_equal.hpp>

#include <laws/base.hpp>
#include "test_case.hpp"


TestCase test_drop_while{[]{
    namespace hana = parmexpr::hana;
    using hana::test::ct_eq;

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(), hana::id),
        MAKE_TUPLE()
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(hana::true_c), hana::id),
        MAKE_TUPLE()
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(hana::false_c), hana::id),
        MAKE_TUPLE(hana::false_c)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(hana::true_c, hana::true_c), hana::id),
        MAKE_TUPLE()
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(hana::true_c, hana::false_c), hana::id),
        MAKE_TUPLE(hana::false_c)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(hana::false_c, hana::true_c), hana::id),
        MAKE_TUPLE(hana::false_c, hana::true_c)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(hana::false_c, hana::false_c), hana::id),
        MAKE_TUPLE(hana::false_c, hana::false_c)
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(ct_eq<0>{}, ct_eq<1>{}), hana::not_equal.to(ct_eq<99>{})),
        MAKE_TUPLE()
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(ct_eq<0>{}, ct_eq<1>{}, ct_eq<2>{}), hana::not_equal.to(ct_eq<1>{})),
        MAKE_TUPLE(ct_eq<1>{}, ct_eq<2>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(ct_eq<0>{}, ct_eq<1>{}, ct_eq<2>{}, ct_eq<3>{}), hana::not_equal.to(ct_eq<3>{})),
        MAKE_TUPLE(ct_eq<3>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::drop_while(MAKE_TUPLE(ct_eq<0>{}, ct_eq<1>{}, ct_eq<2>{}, ct_eq<3>{}), hana::not_equal.to(ct_eq<0>{})),
        MAKE_TUPLE(ct_eq<0>{}, ct_eq<1>{}, ct_eq<2>{}, ct_eq<3>{})
    ));
}};

#endif // !BOOST_HANA_TEST_AUTO_DROP_WHILE_HPP
