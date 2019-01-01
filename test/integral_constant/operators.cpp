// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/integral_constant.hpp>

#include <parmexpr/hana/and.hpp>
#include <parmexpr/hana/div.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/greater.hpp>
#include <parmexpr/hana/greater_equal.hpp>
#include <parmexpr/hana/less.hpp>
#include <parmexpr/hana/less_equal.hpp>
#include <parmexpr/hana/minus.hpp>
#include <parmexpr/hana/mod.hpp>
#include <parmexpr/hana/mult.hpp>
#include <parmexpr/hana/negate.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/not_equal.hpp>
#include <parmexpr/hana/or.hpp>
#include <parmexpr/hana/plus.hpp>
namespace hana = parmexpr::hana;


// Arithmetic operators
BOOST_HANA_CONSTANT_CHECK(+hana::int_c<1> == hana::int_c<1>);
BOOST_HANA_CONSTANT_CHECK(-hana::int_c<1> == hana::int_c<-1>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<1> + hana::int_c<2> == hana::int_c<3>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<1> - hana::int_c<2> == hana::int_c<-1>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<3> * hana::int_c<2> == hana::int_c<6>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<6> / hana::int_c<3> == hana::int_c<2>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<6> % hana::int_c<4> == hana::int_c<2>);
BOOST_HANA_CONSTANT_CHECK(~hana::int_c<6> == hana::int_c<~6>);
BOOST_HANA_CONSTANT_CHECK((hana::int_c<6> & hana::int_c<3>) == hana::int_c<6 & 3>);
BOOST_HANA_CONSTANT_CHECK((hana::int_c<4> | hana::int_c<2>) == hana::int_c<4 | 2>);
BOOST_HANA_CONSTANT_CHECK((hana::int_c<6> ^ hana::int_c<3>) == hana::int_c<6 ^ 3>);
BOOST_HANA_CONSTANT_CHECK((hana::int_c<6> << hana::int_c<3>) == hana::int_c<(6 << 3)>);
BOOST_HANA_CONSTANT_CHECK((hana::int_c<6> >> hana::int_c<3>) == hana::int_c<(6 >> 3)>);

// Comparison operators
BOOST_HANA_CONSTANT_CHECK(hana::int_c<0> == hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<1> != hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<0> < hana::int_c<1>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<0> <= hana::int_c<1>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<0> <= hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<1> > hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<1> >= hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<0> >= hana::int_c<0>);

// Logical operators
BOOST_HANA_CONSTANT_CHECK(hana::int_c<3> || hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(hana::int_c<3> && hana::int_c<1>);
BOOST_HANA_CONSTANT_CHECK(!hana::int_c<0>);
BOOST_HANA_CONSTANT_CHECK(!!hana::int_c<3>);

int main() { }
