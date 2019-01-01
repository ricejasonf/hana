/*!
@file
Defines `parmexpr::hana::flatten`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FLATTEN_HPP
#define BOOST_HANA_FLATTEN_HPP

#include <parmexpr/hana/fwd/flatten.hpp>

#include <parmexpr/hana/concept/monad.hpp>
#include <parmexpr/hana/concept/sequence.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/dispatch.hpp>
#include <parmexpr/hana/core/make.hpp>
#include <parmexpr/hana/detail/unpack_flatten.hpp>
#include <parmexpr/hana/functional/id.hpp>
#include <parmexpr/hana/fwd/chain.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs>
    constexpr auto flatten_t::operator()(Xs&& xs) const {
        using M = typename hana::tag_of<Xs>::type;
        using Flatten = BOOST_HANA_DISPATCH_IF(flatten_impl<M>,
            hana::Monad<M>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::flatten(xs) requires 'xs' to be a Monad");
#endif

        return Flatten::apply(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename M, bool condition>
    struct flatten_impl<M, when<condition>> : default_ {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs)
        { return hana::chain(static_cast<Xs&&>(xs), hana::id); }
    };

    template <typename S>
    struct flatten_impl<S, when<Sequence<S>::value>> {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            return detail::unpack_flatten(static_cast<Xs&&>(xs), hana::make<S>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FLATTEN_HPP
