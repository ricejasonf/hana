/*!
@file
Defines `parmexpr::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_APPEND_HPP
#define BOOST_HANA_APPEND_HPP

#include <parmexpr/hana/fwd/append.hpp>

#include <parmexpr/hana/at.hpp>
#include <parmexpr/hana/concat.hpp>
#include <parmexpr/hana/concept/monad_plus.hpp>
#include <parmexpr/hana/concept/sequence.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/dispatch.hpp>
#include <parmexpr/hana/core/make.hpp>
#include <parmexpr/hana/length.hpp>
#include <parmexpr/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename X>
    constexpr auto append_t::operator()(Xs&& xs, X&& x) const {
        using M = typename hana::tag_of<Xs>::type;
        using Append = BOOST_HANA_DISPATCH_IF(append_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::append(xs, x) requires 'xs' to be a MonadPlus");
    #endif

        return Append::apply(static_cast<Xs&&>(xs), static_cast<X&&>(x));
    }
    //! @endcond

    template <typename M, bool condition>
    struct append_impl<M, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::concat(static_cast<Xs&&>(xs),
                                hana::lift<M>(static_cast<X&&>(x)));
        }
    };

    template <typename S>
    struct append_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename X, std::size_t ...i>
        static constexpr auto append_helper(Xs&& xs, X&& x, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<i>(static_cast<Xs&&>(xs))..., static_cast<X&&>(x)
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return append_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                 std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_APPEND_HPP
