// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/core/tag_of.hpp>
#include <parmexpr/hana/ext/parmexpr/tuple.hpp>

#include <parmexpr/tuple/tuple.hpp>

#include <type_traits>
namespace hana = parmexpr::hana;


int main() {
    //////////////////////////////////////////////////////////////////////////
    // make sure the tag is correct
    //////////////////////////////////////////////////////////////////////////
    {
        auto make_cons = [](auto x, auto xs) {
            return parmexpr::tuples::cons<decltype(x), decltype(xs)>{x, xs};
        };

        static_assert(std::is_same<
            hana::tag_of_t<decltype(parmexpr::make_tuple())>,
            hana::ext::parmexpr::tuple_tag
        >::value, "");

        static_assert(std::is_same<
            hana::tag_of_t<decltype(parmexpr::make_tuple(1))>,
            hana::ext::parmexpr::tuple_tag
        >::value, "");

        static_assert(std::is_same<
            hana::tag_of_t<decltype(parmexpr::make_tuple(1, '2'))>,
            hana::ext::parmexpr::tuple_tag
        >::value, "");

        static_assert(std::is_same<
            hana::tag_of_t<decltype(parmexpr::make_tuple(1, '2', 3.3))>,
            hana::ext::parmexpr::tuple_tag
        >::value, "");

        static_assert(std::is_same<
            hana::tag_of_t<decltype(make_cons(1, parmexpr::tuples::null_type{}))>,
            hana::ext::parmexpr::tuple_tag
        >::value, "");

        static_assert(std::is_same<
            hana::tag_of_t<decltype(make_cons(1, make_cons('2', parmexpr::tuples::null_type{})))>,
            hana::ext::parmexpr::tuple_tag
        >::value, "");

        static_assert(std::is_same<
            hana::tag_of_t<decltype(make_cons(1, parmexpr::make_tuple('2', 3.3)))>,
            hana::ext::parmexpr::tuple_tag
        >::value, "");

        static_assert(std::is_same<
            hana::tag_of_t<parmexpr::tuples::null_type>,
            hana::ext::parmexpr::tuple_tag
        >::value, "");
    }
}
