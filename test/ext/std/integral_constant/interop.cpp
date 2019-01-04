// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/std/integral_constant.hpp>

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/not_equal.hpp>

#include <type_traits>
namespace hana = parmexpr::hana;


int main() {
    // Interoperation with hana::integral_constant
    BOOST_HANA_CONSTANT_CHECK(std::integral_constant<int, 1>{} == hana::int_c<1>);
    BOOST_HANA_CONSTANT_CHECK(std::integral_constant<int, 1>{} == hana::long_c<1>);

    BOOST_HANA_CONSTANT_CHECK(std::integral_constant<int, 2>{} != hana::int_c<3>);
}
