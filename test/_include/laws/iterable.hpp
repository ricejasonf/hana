// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HANA_TEST_LAWS_ITERABLE_HPP
#define BOOST_HANA_TEST_LAWS_ITERABLE_HPP

#include <parmexpr/hana/any_of.hpp>
#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/at.hpp>
#include <parmexpr/hana/back.hpp>
#include <parmexpr/hana/bool.hpp>
#include <parmexpr/hana/concept/comparable.hpp>
#include <parmexpr/hana/concept/foldable.hpp>
#include <parmexpr/hana/concept/sequence.hpp>
#include <parmexpr/hana/core/make.hpp>
#include <parmexpr/hana/core/to.hpp>
#include <parmexpr/hana/core/when.hpp>
#include <parmexpr/hana/drop_front.hpp>
#include <parmexpr/hana/drop_front_exactly.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/eval_if.hpp>
#include <parmexpr/hana/find_if.hpp>
#include <parmexpr/hana/for_each.hpp>
#include <parmexpr/hana/front.hpp>
#include <parmexpr/hana/functional/always.hpp>
#include <parmexpr/hana/functional/capture.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/is_empty.hpp>
#include <parmexpr/hana/lazy.hpp>
#include <parmexpr/hana/length.hpp>
#include <parmexpr/hana/minus.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/optional.hpp>
#include <parmexpr/hana/range.hpp>
#include <parmexpr/hana/tuple.hpp>

#include <laws/base.hpp>


namespace parmexpr { namespace hana { namespace test {
    template <typename It, typename = hana::when<true>>
    struct TestIterable : TestIterable<It, laws> {
        using TestIterable<It, laws>::TestIterable;
    };

    template <typename It>
    struct TestIterable<It, laws> {
        template <typename Xs>
        TestIterable(Xs xs) {
            hana::for_each(xs, [](auto xs) {
                static_assert(Iterable<decltype(xs)>{}, "");

                BOOST_HANA_CONSTANT_CHECK(
                    hana::is_empty(xs) ^iff^ hana::is_empty(hana::to<tuple_tag>(xs))
                );

                only_when_(hana::not_(hana::is_empty(xs)), hana::make_lazy([](auto xs) {
                    BOOST_HANA_CHECK(hana::equal(
                        hana::front(xs),
                        hana::front(hana::to<tuple_tag>(xs))
                    ));

                    BOOST_HANA_CHECK(hana::equal(
                        hana::to<tuple_tag>(hana::drop_front_exactly(xs)),
                        hana::drop_front_exactly(hana::to<tuple_tag>(xs))
                    ));

                    // methods
                    // back(xs) == at(xs, length(xs)-1)
                    BOOST_HANA_CHECK(hana::equal(
                        hana::back(xs),
                        hana::at(xs, hana::minus(hana::length(xs), hana::size_c<1>))
                    ));

                })(xs));

                // drop_front(xs, 0) == xs
                BOOST_HANA_CHECK(hana::equal(
                    hana::drop_front(xs, size_c<0>),
                    xs
                ));

                // at(xs, n) == front(drop_front(xs, n))
                hana::for_each(hana::make_range(size_c<0>, hana::length(xs)),
                hana::capture(xs)([](auto xs, auto n) {
                    BOOST_HANA_CHECK(hana::equal(
                        hana::at(xs, n),
                        hana::front(hana::drop_front(xs, n))
                    ));
                }));

                // Searchable
                hana::eval_if(hana::is_empty(xs),
                    hana::make_lazy([](auto xs) {
                        BOOST_HANA_CONSTANT_CHECK(
                            hana::not_(hana::any_of(xs, hana::always(true_c)))
                        );

                        BOOST_HANA_CONSTANT_CHECK(hana::equal(
                            hana::find_if(xs, hana::always(true_c)),
                            nothing
                        ));
                    })(xs),
                    hana::make_lazy([](auto xs) {
                        BOOST_HANA_CHECK(
                            hana::any_of(xs, hana::always(true_c))
                        );
                        BOOST_HANA_CHECK(
                            hana::not_(hana::any_of(xs, hana::always(false_c)))
                        );

                        BOOST_HANA_CHECK(hana::equal(
                            hana::find_if(xs, hana::always(true_c)),
                            hana::just(hana::front(xs))
                        ));
                    })(xs)
                );

            });
        }
    };

    template <typename S>
    struct TestIterable<S, when<Sequence<S>::value>>
        : TestIterable<S, laws>
    {
        template <int i>
        using x = ct_eq<i>;

        template <int i = 0>
        struct invalid { };

        struct undefined { };

        template <typename Xs>
        TestIterable(Xs xs) : TestIterable<S, laws>{xs} {
            constexpr auto list = make<S>;

            //////////////////////////////////////////////////////////////////
            // front
            //////////////////////////////////////////////////////////////////
            BOOST_HANA_CONSTANT_CHECK(equal(
                front(list(x<0>{})),
                x<0>{}
            ));
            BOOST_HANA_CONSTANT_CHECK(equal(
                front(list(x<0>{}, invalid<>{})),
                x<0>{}
            ));
            BOOST_HANA_CONSTANT_CHECK(equal(
                front(list(x<0>{}, invalid<1>{}, invalid<2>{})),
                x<0>{}
            ));

            BOOST_HANA_CONSTEXPR_CHECK(equal(
                front(list(1)), 1
            ));
            BOOST_HANA_CONSTEXPR_CHECK(equal(
                front(list(1, '2')), 1
            ));
            BOOST_HANA_CONSTEXPR_CHECK(equal(
                front(list(1, '2', 3.3)), 1
            ));

            //////////////////////////////////////////////////////////////////
            // back
            //////////////////////////////////////////////////////////////////
            BOOST_HANA_CONSTANT_CHECK(equal(
                back(list(x<0>{})),
                x<0>{}
            ));
            BOOST_HANA_CONSTANT_CHECK(equal(
                back(list(invalid<0>{}, x<1>{})),
                x<1>{}
            ));
            BOOST_HANA_CONSTANT_CHECK(equal(
                back(list(invalid<0>{}, invalid<1>{}, x<2>{})),
                x<2>{}
            ));

            BOOST_HANA_CONSTEXPR_CHECK(equal(
                back(list(1)), 1
            ));
            BOOST_HANA_CONSTEXPR_CHECK(equal(
                back(list(1, '2')), '2'
            ));
            BOOST_HANA_CONSTEXPR_CHECK(equal(
                back(list(1, '2', 3.3)), 3.3
            ));
        }
    };
}}} // end namespace parmexpr::hana::test

#endif // !BOOST_HANA_TEST_LAWS_ITERABLE_HPP
