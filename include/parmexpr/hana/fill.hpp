/*!
@file
Defines `parmexpr::hana::fill`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FILL_HPP
#define BOOST_HANA_FILL_HPP

#include <parmexpr/hana/fwd/fill.hpp>

#include <parmexpr/hana/concept/functor.hpp>
#include <parmexpr/hana/concept/sequence.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/dispatch.hpp>
#include <parmexpr/hana/core/make.hpp>
#include <parmexpr/hana/functional/always.hpp>
#include <parmexpr/hana/transform.hpp>
#include <parmexpr/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto fill_t::operator()(Xs&& xs, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using Fill = BOOST_HANA_DISPATCH_IF(fill_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::fill(xs, value) requires 'xs' to be a Functor");
    #endif

        return Fill::apply(static_cast<Xs&&>(xs),
                           static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct fill_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& v) {
            return hana::transform(static_cast<Xs&&>(xs),
                                   hana::always(static_cast<Value&&>(v))
            );
        }
    };

    template <typename S>
    struct fill_impl<S, when<Sequence<S>::value>> {
        //! @cond
        template <typename V>
        struct filler {
            V const& v;
            template <typename ...Xs>
            constexpr auto operator()(Xs const& ...xs) const {
                return hana::make<S>(((void)xs, v)...);
            }
        };
        //! @endcond

        template <typename Xs, typename V>
        static constexpr auto apply(Xs const& xs, V const& v) {
            return hana::unpack(xs, filler<V>{v});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FILL_HPP
