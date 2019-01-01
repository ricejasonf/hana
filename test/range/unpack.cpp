// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/core/make.hpp>
#include <parmexpr/hana/core/tag_of.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/range.hpp>
#include <parmexpr/hana/unpack.hpp>

#include <laws/base.hpp>

#include <type_traits>
namespace hana = parmexpr::hana;


int main() {
    hana::test::_injection<0> f{};

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::unpack(hana::make_range(hana::int_c<0>, hana::int_c<0>), f),
        f()
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::unpack(hana::make_range(hana::int_c<0>, hana::int_c<1>), f),
        f(hana::int_c<0>)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::unpack(hana::make_range(hana::int_c<0>, hana::int_c<2>), f),
        f(hana::int_c<0>, hana::int_c<1>)
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::unpack(hana::make_range(hana::int_c<0>, hana::int_c<3>), f),
        f(hana::int_c<0>, hana::int_c<1>, hana::int_c<2>)
    ));

    // Previously, we would only unpack with `std::size_t`s. Make
    // sure this does not happen.
    hana::unpack(hana::make_range(hana::int_c<0>, hana::int_c<1>), [](auto x) {
        using T = hana::tag_of_t<decltype(x)>;
        static_assert(std::is_same<typename T::value_type, int>{}, "");
    });
}
