// Copyright Jason Rice 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/at_key.hpp>
#include <parmexpr/hana/core/to.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/hash.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/map.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/pair.hpp>
#include <parmexpr/hana/tuple.hpp>
namespace hana = parmexpr::hana;


struct A { };
struct B { };

struct the_hash;

namespace parmexpr { namespace hana {
    template <>
    struct hash_impl<A> {
        static constexpr auto apply(A const&) {
            return hana::type_c<the_hash>;
        }
    };

    template <>
    struct hash_impl<B> {
        static constexpr auto apply(B const&) {
            return hana::type_c<the_hash>;
        }
    };

    template <>
    struct equal_impl<A, A> {
        static constexpr auto apply(A const&, A const&) {
            return hana::true_c;
        }
    };

    template <>
    struct equal_impl<B, B> {
        static constexpr auto apply(B const&, B const&) {
            return hana::true_c;
        }
    };
}}

int main() {
    constexpr auto key1 = A{};
    constexpr auto key2 = B{};

    BOOST_HANA_CONSTANT_CHECK(hana::equal(key1, key1));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(key2, key2));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::equal(key1, key2)));

    // ensure the hashes actually collide
    BOOST_HANA_CONSTANT_CHECK(hana::equal(hana::hash(key1), hana::hash(key2)));

    {
        auto map = hana::to_map(hana::make_tuple(
            hana::make_pair(key1, key1),
            hana::make_pair(key2, key2)
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, key1),
            key1
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, key2),
            key2
        ));
    }

    {
        auto map = hana::to_map(hana::make_tuple(
            hana::make_pair(key2, key2),
            hana::make_pair(key1, key1)
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, key1),
            key1
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, key2),
            key2
        ));
    }

    {
        auto map = hana::to_map(hana::make_tuple(
            hana::make_pair(key1, key1),
            hana::make_pair(hana::int_c<56>, hana::int_c<56>),
            hana::make_pair(key2, key2)
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, key1),
            key1
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, hana::int_c<56>),
            hana::int_c<56>
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, key2),
            key2
        ));
    }

    {
        auto map = hana::to_map(hana::make_tuple(
            hana::make_pair(key1, key1),
            hana::make_pair(hana::int_c<56>, hana::int_c<56>),
            hana::make_pair(key2, key2),
            hana::make_pair(hana::int_c<42>, hana::int_c<42>)
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, key1),
            key1
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, hana::int_c<56>),
            hana::int_c<56>
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, key2),
            key2
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::at_key(map, hana::int_c<42>),
            hana::int_c<42>
        ));
    }
}
