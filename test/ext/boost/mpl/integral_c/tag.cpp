// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/mpl/integral_c.hpp>

#include <parmexpr/hana/core/tag_of.hpp>

#include <parmexpr/mpl/bool.hpp>
#include <parmexpr/mpl/char.hpp>
#include <parmexpr/mpl/int.hpp>
#include <parmexpr/mpl/integral_c.hpp>
#include <parmexpr/mpl/long.hpp>
#include <parmexpr/mpl/size_t.hpp>

#include <cstddef>
#include <type_traits>
namespace hana = parmexpr::hana;
namespace mpl = parmexpr::mpl;


static_assert(std::is_same<
    hana::tag_of_t<mpl::bool_<true>>,
    hana::ext::parmexpr::mpl::integral_c_tag<bool>
>::value, "");

static_assert(std::is_same<
    hana::tag_of_t<mpl::int_<0>>,
    hana::ext::parmexpr::mpl::integral_c_tag<int>
>::value, "");

static_assert(std::is_same<
    hana::tag_of_t<mpl::long_<0>>,
    hana::ext::parmexpr::mpl::integral_c_tag<long>
>::value, "");

static_assert(std::is_same<
    hana::tag_of_t<mpl::size_t<0>>,
    hana::ext::parmexpr::mpl::integral_c_tag<std::size_t>
>::value, "");

static_assert(std::is_same<
    hana::tag_of_t<mpl::integral_c<int, 0>>,
    hana::ext::parmexpr::mpl::integral_c_tag<int>
>::value, "");

static_assert(std::is_same<
    hana::tag_of_t<mpl::char_<0>>,
    hana::ext::parmexpr::mpl::integral_c_tag<char>
>::value, "");

int main() { }
