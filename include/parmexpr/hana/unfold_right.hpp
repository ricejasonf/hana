/*!
@file
Defines `parmexpr::hana::unfold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNFOLD_RIGHT_HPP
#define BOOST_HANA_UNFOLD_RIGHT_HPP

#include <parmexpr/hana/fwd/unfold_right.hpp>

#include <parmexpr/hana/concept/sequence.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/dispatch.hpp>
#include <parmexpr/hana/empty.hpp>
#include <parmexpr/hana/first.hpp>
#include <parmexpr/hana/functional/partial.hpp>
#include <parmexpr/hana/optional.hpp>
#include <parmexpr/hana/prepend.hpp>
#include <parmexpr/hana/second.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename S>
    struct unfold_right_t {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unfold_right<S> requires 'S' to be a Sequence");
    #endif

        template <typename State, typename F>
        constexpr auto operator()(State&& state, F&& f) const {
            return unfold_right_impl<S>::apply(
                static_cast<State&&>(state),
                static_cast<F&&>(f)
            );
        }
    };
    //! @endcond

    template <typename S, bool condition>
    struct unfold_right_impl<S, when<condition>> : default_ {
        struct unfold_right_helper {
            template <typename F, typename P>
            constexpr auto operator()(F&& f, P&& p) const {
                return hana::prepend(
                    unfold_right_impl::apply(
                        hana::second(static_cast<P&&>(p)),
                        static_cast<F&&>(f)
                    ),
                    hana::first(static_cast<P&&>(p))
                );
            }
        };

        template <typename Init, typename F>
        static constexpr auto apply(Init&& init, F&& f) {
            decltype(auto) elt = f(static_cast<Init&&>(init));
            return hana::maybe(hana::empty<S>(),
                hana::partial(unfold_right_helper{}, static_cast<F&&>(f)),
                static_cast<decltype(elt)&&>(elt)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNFOLD_RIGHT_HPP
