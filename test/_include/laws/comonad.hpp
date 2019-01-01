// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HANA_TEST_LAWS_COMONAD_HPP
#define BOOST_HANA_TEST_LAWS_COMONAD_HPP

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/concept/comonad.hpp>
#include <parmexpr/hana/concept/comparable.hpp>
#include <parmexpr/hana/core/when.hpp>
#include <parmexpr/hana/concept/foldable.hpp>
#include <parmexpr/hana/concept/functor.hpp>

#include <laws/base.hpp>


namespace parmexpr { namespace hana { namespace test {
    template <typename W, typename = when<true>>
    struct TestComonad : TestComonad<W, laws> {
        using TestComonad<W, laws>::TestComonad;
    };

    template <typename W>
    struct TestComonad<W, laws> {
        template <typename Ws>
        TestComonad(Ws ws) {
            hana::for_each(ws, [](auto w) {
                static_assert(Comonad<decltype(w)>{}, "");

                // extract(duplicate(w)) == w
                BOOST_HANA_CHECK(hana::equal(
                    hana::extract(hana::duplicate(w)),
                    w
                ));

                // transform(duplicate(w), extract) == w
                BOOST_HANA_CHECK(hana::equal(
                    hana::transform(hana::duplicate(w), extract),
                    w
                ));

                // duplicate(duplicate(w)) == transform(duplicate(w), duplicate)
                BOOST_HANA_CHECK(hana::equal(
                    hana::duplicate(hana::duplicate(w)),
                    hana::transform(hana::duplicate(w), duplicate)
                ));
            });
        }
    };
}}} // end namespace parmexpr::hana::test

#endif // !BOOST_HANA_TEST_LAWS_COMONAD_HPP
