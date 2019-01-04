/*!
@file
Defines `parmexpr::hana::product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PRODUCT_HPP
#define BOOST_HANA_PRODUCT_HPP

#include <parmexpr/hana/fwd/product.hpp>

#include <parmexpr/hana/concept/foldable.hpp>
#include <parmexpr/hana/concept/ring.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/dispatch.hpp>
#include <parmexpr/hana/fold_left.hpp>
#include <parmexpr/hana/integral_constant.hpp> // required by fwd decl
#include <parmexpr/hana/mult.hpp>
#include <parmexpr/hana/one.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename R>
    template <typename Xs>
    constexpr decltype(auto) product_t<R>::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Product = BOOST_HANA_DISPATCH_IF(product_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Ring<R>::value,
        "hana::product<R> requires 'R' to be a Ring");

        static_assert(hana::Foldable<S>::value,
        "hana::product<R>(xs) requires 'xs' to be Foldable");
    #endif

        return Product::template apply<R>(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename T, bool condition>
    struct product_impl<T, when<condition>> : default_ {
        template <typename R, typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            return hana::fold_left(static_cast<Xs&&>(xs), hana::one<R>(), hana::mult);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PRODUCT_HPP
