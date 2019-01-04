/*!
@file
Defines `parmexpr::hana::lazy`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LAZY_HPP
#define BOOST_HANA_LAZY_HPP

#include <parmexpr/hana/fwd/lazy.hpp>

#include <parmexpr/hana/basic_tuple.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/make.hpp>
#include <parmexpr/hana/detail/decay.hpp>
#include <parmexpr/hana/detail/operators/adl.hpp>
#include <parmexpr/hana/detail/operators/monad.hpp>
#include <parmexpr/hana/functional/apply.hpp>
#include <parmexpr/hana/functional/compose.hpp>
#include <parmexpr/hana/functional/on.hpp>
#include <parmexpr/hana/fwd/ap.hpp>
#include <parmexpr/hana/fwd/duplicate.hpp>
#include <parmexpr/hana/fwd/eval.hpp>
#include <parmexpr/hana/fwd/extend.hpp>
#include <parmexpr/hana/fwd/extract.hpp>
#include <parmexpr/hana/fwd/flatten.hpp>
#include <parmexpr/hana/fwd/lift.hpp>
#include <parmexpr/hana/fwd/transform.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // lazy
    //////////////////////////////////////////////////////////////////////////
    template <typename Indices, typename F, typename ...Args>
    struct lazy_apply_t;

    namespace detail { struct lazy_secret { }; }

    template <std::size_t ...n, typename F, typename ...Args>
    struct lazy_apply_t<std::index_sequence<n...>, F, Args...>
        : detail::operators::adl<>
    {
        template <typename ...T>
        constexpr lazy_apply_t(detail::lazy_secret, T&& ...t)
            : storage_{static_cast<T&&>(t)...}
        { }

        basic_tuple<F, Args...> storage_;
        using hana_tag = lazy_tag;
    };

    template <typename X>
    struct lazy_value_t : detail::operators::adl<> {
        template <typename Y>
        constexpr lazy_value_t(detail::lazy_secret, Y&& y)
            : storage_{static_cast<Y&&>(y)}
        { }

        basic_tuple<X> storage_;
        using hana_tag = lazy_tag;

        // If this is called, we assume that `X` is in fact a function.
        template <typename ...Args>
        constexpr lazy_apply_t<
            std::make_index_sequence<sizeof...(Args)>,
            X, typename detail::decay<Args>::type...
        > operator()(Args&& ...args) const& {
            return {detail::lazy_secret{},
                    hana::at_c<0>(storage_), static_cast<Args&&>(args)...};
        }

        template <typename ...Args>
        constexpr lazy_apply_t<
            std::make_index_sequence<sizeof...(Args)>,
            X, typename detail::decay<Args>::type...
        > operator()(Args&& ...args) && {
            return {detail::lazy_secret{},
                static_cast<X&&>(hana::at_c<0>(storage_)),
                static_cast<Args&&>(args)...
            };
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // make<lazy_tag>
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct make_impl<lazy_tag> {
        template <typename X>
        static constexpr lazy_value_t<typename detail::decay<X>::type> apply(X&& x) {
            return {detail::lazy_secret{}, static_cast<X&&>(x)};
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Operators
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <>
        struct monad_operators<lazy_tag> { static constexpr bool value = true; };
    }

    //////////////////////////////////////////////////////////////////////////
    // eval for lazy_tag
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct eval_impl<lazy_tag> {
        // lazy_apply_t
        template <std::size_t ...n, typename F, typename ...Args>
        static constexpr decltype(auto)
        apply(lazy_apply_t<std::index_sequence<n...>, F, Args...> const& expr) {
            return hana::at_c<0>(expr.storage_)(
                hana::at_c<n+1>(expr.storage_)...
            );
        }

        template <std::size_t ...n, typename F, typename ...Args>
        static constexpr decltype(auto)
        apply(lazy_apply_t<std::index_sequence<n...>, F, Args...>& expr) {
            return hana::at_c<0>(expr.storage_)(
                hana::at_c<n+1>(expr.storage_)...
            );
        }

        template <std::size_t ...n, typename F, typename ...Args>
        static constexpr decltype(auto)
        apply(lazy_apply_t<std::index_sequence<n...>, F, Args...>&& expr) {
            return static_cast<F&&>(hana::at_c<0>(expr.storage_))(
                static_cast<Args&&>(hana::at_c<n+1>(expr.storage_))...
            );
        }

        // lazy_value_t
        template <typename X>
        static constexpr X const& apply(lazy_value_t<X> const& expr)
        { return hana::at_c<0>(expr.storage_); }

        template <typename X>
        static constexpr X& apply(lazy_value_t<X>& expr)
        { return hana::at_c<0>(expr.storage_); }

        template <typename X>
        static constexpr X apply(lazy_value_t<X>&& expr)
        { return static_cast<X&&>(hana::at_c<0>(expr.storage_)); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Functor
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct transform_impl<lazy_tag> {
        template <typename Expr, typename F>
        static constexpr auto apply(Expr&& expr, F&& f) {
            return hana::make_lazy(hana::compose(static_cast<F&&>(f), hana::eval))(
                static_cast<Expr&&>(expr)
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Applicative
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct lift_impl<lazy_tag> {
        template <typename X>
        static constexpr lazy_value_t<typename detail::decay<X>::type>
        apply(X&& x) {
            return {detail::lazy_secret{}, static_cast<X&&>(x)};
        }
    };

    template <>
    struct ap_impl<lazy_tag> {
        template <typename F, typename X>
        static constexpr decltype(auto) apply(F&& f, X&& x) {
            return hana::make_lazy(hana::on(hana::apply, hana::eval))(
                static_cast<F&&>(f), static_cast<X&&>(x)
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Monad
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct flatten_impl<lazy_tag> {
        template <typename Expr>
        static constexpr decltype(auto) apply(Expr&& expr) {
            return hana::make_lazy(hana::compose(hana::eval, hana::eval))(
                static_cast<Expr&&>(expr)
            );
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Comonad
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct extract_impl<lazy_tag> {
        template <typename Expr>
        static constexpr decltype(auto) apply(Expr&& expr)
        { return hana::eval(static_cast<Expr&&>(expr)); }
    };

    template <>
    struct duplicate_impl<lazy_tag> {
        template <typename Expr>
        static constexpr decltype(auto) apply(Expr&& expr)
        { return hana::make_lazy(static_cast<Expr&&>(expr)); }
    };

    template <>
    struct extend_impl<lazy_tag> {
        template <typename Expr, typename F>
        static constexpr decltype(auto) apply(Expr&& expr, F&& f) {
            return hana::make_lazy(static_cast<F&&>(f))(static_cast<Expr&&>(expr));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LAZY_HPP
