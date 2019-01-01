// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/ext/std/integer_sequence.hpp>
#include <parmexpr/hana/ext/std/integral_constant.hpp>
#include <parmexpr/hana/find_if.hpp>
#include <parmexpr/hana/optional.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>
namespace hana = parmexpr::hana;


struct undefined { };


int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<>{},
                      hana::equal.to(undefined{})),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0>{},
                      hana::equal.to(std::integral_constant<std::size_t, 0>{})),
        hana::just(std::integral_constant<std::size_t, 0>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0>{},
                      hana::equal.to(std::integral_constant<std::size_t, 1>{})),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1>{},
                      hana::equal.to(std::integral_constant<std::size_t, 0>{})),
        hana::just(std::integral_constant<std::size_t, 0>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1>{},
                      hana::equal.to(std::integral_constant<std::size_t, 1>{})),
        hana::just(std::integral_constant<std::size_t, 1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1>{},
                      hana::equal.to(std::integral_constant<std::size_t, 2>{})),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1, 2>{},
                      hana::equal.to(std::integral_constant<std::size_t, 0>{})),
        hana::just(std::integral_constant<std::size_t, 0>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1, 2>{},
                      hana::equal.to(std::integral_constant<std::size_t, 1>{})),
        hana::just(std::integral_constant<std::size_t, 1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1, 2>{},
                      hana::equal.to(std::integral_constant<std::size_t, 2>{})),
        hana::just(std::integral_constant<std::size_t, 2>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1, 2>{},
                      hana::equal.to(std::integral_constant<std::size_t, 3>{})),
        hana::nothing
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1, 2, 3>{},
                      hana::equal.to(std::integral_constant<std::size_t, 0>{})),
        hana::just(std::integral_constant<std::size_t, 0>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1, 2, 3>{},
                      hana::equal.to(std::integral_constant<std::size_t, 1>{})),
        hana::just(std::integral_constant<std::size_t, 1>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1, 2, 3>{},
                      hana::equal.to(std::integral_constant<std::size_t, 2>{})),
        hana::just(std::integral_constant<std::size_t, 2>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1, 2, 3>{},
                      hana::equal.to(std::integral_constant<std::size_t, 3>{})),
        hana::just(std::integral_constant<std::size_t, 3>{})
    ));
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        hana::find_if(std::index_sequence<0, 1, 2, 3>{},
                      hana::equal.to(std::integral_constant<std::size_t, 4>{})),
        hana::nothing
    ));
}
