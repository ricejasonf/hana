// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HANA_TEST_LAWS_EUCLIDEAN_RING_HPP
#define BOOST_HANA_TEST_LAWS_EUCLIDEAN_RING_HPP

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/bool.hpp>
#include <parmexpr/hana/concept/comparable.hpp>
#include <parmexpr/hana/concept/constant.hpp>
#include <parmexpr/hana/concept/euclidean_ring.hpp>
#include <parmexpr/hana/core/when.hpp>
#include <parmexpr/hana/div.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/for_each.hpp>
#include <parmexpr/hana/lazy.hpp>
#include <parmexpr/hana/mod.hpp>
#include <parmexpr/hana/mult.hpp>
#include <parmexpr/hana/not_equal.hpp>
#include <parmexpr/hana/plus.hpp>
#include <parmexpr/hana/value.hpp>
#include <parmexpr/hana/zero.hpp>

#include <laws/base.hpp>


namespace parmexpr { namespace hana { namespace test {
    template <typename D, typename = when<true>>
    struct TestEuclideanRing : TestEuclideanRing<D, laws> {
        using TestEuclideanRing<D, laws>::TestEuclideanRing;
    };

    template <typename D>
    struct TestEuclideanRing<D, laws> {
        template <typename Xs>
        TestEuclideanRing(Xs xs) {
            hana::for_each(xs, [](auto x) {
                static_assert(EuclideanRing<decltype(x)>{}, "");
            });

#ifdef BOOST_HANA_WORKAROUND_MSVC_DECLTYPEAUTO_RETURNTYPE_662735
            zero<D>(); // force adding zero<D>'s member function to pending temploid list
#endif

            foreach2(xs, [](auto a, auto b) {

                // commutativity
                BOOST_HANA_CHECK(hana::equal(
                    hana::mult(a, b),
                    hana::mult(b, a)
                ));

                only_when_(hana::not_equal(b, zero<D>()),
                hana::make_lazy([](auto a, auto b) {
                    BOOST_HANA_CHECK(hana::equal(
                        hana::plus(
                            hana::mult(hana::div(a, b), b),
                            hana::mod(a, b)
                        ),
                        a
                    ));

                    BOOST_HANA_CHECK(hana::equal(
                        hana::mod(zero<D>(), b),
                        zero<D>()
                    ));
                })(a, b));

            });
        }
    };

    template <typename C>
    struct TestEuclideanRing<C, when<Constant<C>::value>>
        : TestEuclideanRing<C, laws>
    {
        template <typename Xs>
        TestEuclideanRing(Xs xs) : TestEuclideanRing<C, laws>{xs} {
            foreach2(xs, [](auto x, auto y) {
                only_when_(hana::not_equal(zero<C>(), y),
                hana::make_lazy([](auto x, auto y) {
                    BOOST_HANA_CHECK(hana::equal(
                        hana::div(hana::value(x), hana::value(y)),
                        hana::value(hana::div(x, y))
                    ));

                    BOOST_HANA_CHECK(hana::equal(
                        hana::mod(hana::value(x), hana::value(y)),
                        hana::value(hana::mod(x, y))
                    ));

                })(x, y));
            });
        }
    };
}}} // end namespace parmexpr::hana::test

#endif // !BOOST_HANA_TEST_LAWS_EUCLIDEAN_RING_HPP
