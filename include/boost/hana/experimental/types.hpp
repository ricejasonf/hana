/*!
@file
Defines `boost::hana::experimental::types`.

@copyright Louis Dionne 2013-2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXPERIMENTAL_TYPES_HPP
#define BOOST_HANA_EXPERIMENTAL_TYPES_HPP

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/metafunction.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/fwd/ap.hpp>
#include <boost/hana/fwd/append.hpp>
#include <boost/hana/detail/any_of.hpp>
#include <boost/hana/detail/unpack_flatten.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/chain.hpp>
#include <boost/hana/fwd/concat.hpp>
#include <boost/hana/fwd/contains.hpp>
#include <boost/hana/fwd/core/is_a.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/flatten.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/lift.hpp>
#include <boost/hana/fwd/prepend.hpp>
#include <boost/hana/fwd/transform.hpp>
#include <boost/hana/fwd/tuple.hpp>
#include <boost/hana/fwd/unpack.hpp>
#include <boost/hana/functional/on.hpp>
#include <boost/hana/type.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    namespace experimental {
        //! @ingroup group-experimental
        //! Container optimized for holding types.
        //!
        //! It is often useful to manipulate a sequence that contains types
        //! only, without any associated runtime value. This container allows
        //! storing and manipulating pure types in a much more compile-time
        //! efficient manner than using `hana::tuple`, which must assume that
        //! its contents might have runtime values.
        template <typename ...T>
        struct types;

        struct types_tag;

        //////////////////////////////////////////////////////////////////////

        template <typename ...T>
        struct types {
            using type = types;
        };

        constexpr auto make_types = make<types_tag>;

        constexpr auto to_types = to<types_tag>;
    } // end namespace experimental

    template <typename ...T>
    struct tag_of<experimental::types<T...>> {
        using type = experimental::types_tag;
    };

    template <>
    struct to_impl<hana::experimental::types_tag, hana::tuple_tag> {
        template <typename ...T>
        static constexpr auto apply(hana::tuple<T...> const&)
            -> hana::experimental::types<T...>
        { return {}; }
    };

    template <typename F>
    struct to_impl<hana::experimental::types_tag, F, when<
        hana::Foldable<F>::value
        && !hana::is_a<hana::experimental::types_tag, F>
    >> : embedding<Sequence<F>::value> {
        template <typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs)
        { return hana::unpack(static_cast<Xs&&>(xs),
            hana::experimental::make_types ^hana::on^ hana::decltype_); }
    };

    template <>
    struct make_impl<experimental::types_tag> {
        template <typename ...T>
        static constexpr auto apply(T const&...)
            -> const experimental::types<typename T::type...>
        {
            return {};
        }
    };

    namespace types_detail {
        template <typename T>
        struct member_representation {
            using type = hana::type<T>;
        };

        template <typename ...T>
        struct member_representation<hana::experimental::types<T...>> {
            using type = hana::experimental::types<T...>;
        };

        template <typename ...T>
        using member_rep_t = typename member_representation<T...>::type;
    }
    // Foldable
    template <>
    struct unpack_impl<hana::experimental::types_tag> {
        template <typename ...T, typename F, typename = typename std::enable_if<
            !hana::Metafunction<F>::value
        >::type>
        static constexpr decltype(auto) apply(hana::experimental::types<T...> const&, F&& f) {
            return static_cast<F&&>(f)(types_detail::member_rep_t<T>{}...);
        }

        template <typename ...T, typename F, typename = typename std::enable_if<
            hana::Metafunction<F>::value
        >::type>
        static constexpr hana::type<typename F::template apply<T...>::type>
        apply(hana::experimental::types<T...> const&, F const&) { return {}; }
    };

    template <>
    struct length_impl<hana::experimental::types_tag> {
        template <typename ...T>
        static constexpr auto apply(experimental::types<T...> const&)
            -> hana::size_t<sizeof...(T)>
        { return {}; }
    };

    // Functor
    template <>
    struct transform_impl<hana::experimental::types_tag> {
        template <typename ...T, typename F, typename = typename std::enable_if<
            !hana::Metafunction<F>::value
        >::type>
        static constexpr auto apply(hana::experimental::types<T...> const&, F&& f)
            -> hana::experimental::types<typename decltype(f(types_detail::member_rep_t<T>{}))::type...>
        { return {}; }

        template <typename ...T, typename F, typename = typename std::enable_if<
            hana::Metafunction<F>::value
        >::type>
        static constexpr hana::experimental::types<typename F::template apply<T>::type...>
        apply(hana::experimental::types<T...> const&, F const&) { return {}; }
    };

    namespace types_detail {
        template <std::size_t I, typename T>
        struct elt { using type = T; };

        template <typename Indices, typename ...T>
        struct indexer;

        template <std::size_t ...I, typename ...T>
        struct indexer<std::index_sequence<I...>, T...>
            : elt<I, T>...
        { };

        template <std::size_t I, typename T>
        elt<I, T> get_elt(elt<I, T> const&);
    }

    // Iterable
    template <>
    struct at_impl<hana::experimental::types_tag> {
        template <typename ...T, typename N>
        static constexpr auto
        apply(hana::experimental::types<T...> const&, N const&) {
            using Indexer = types_detail::indexer<std::make_index_sequence<sizeof...(T)>, T...>;
            using Nth = typename decltype(types_detail::get_elt<N::value>(Indexer{}))::type;
            return types_detail::member_rep_t<Nth>{};
        }
    };

    template <>
    struct is_empty_impl<hana::experimental::types_tag> {
        template <typename ...T>
        static constexpr hana::bool_<sizeof...(T) == 0>
        apply(hana::experimental::types<T...> const&)
        { return {}; }
    };

    template <>
    struct drop_front_impl<hana::experimental::types_tag> {
        template <std::size_t n, typename Indexer, std::size_t ...i>
        static hana::experimental::types<
            typename decltype(types_detail::get_elt<i + n>(Indexer{}))::type...
        > helper(std::index_sequence<i...>);

        template <typename ...T, typename N>
        static constexpr auto
        apply(hana::experimental::types<T...> const&, N const&) {
            constexpr std::size_t n = N::value > sizeof...(T) ? sizeof...(T) : N::value;
            using Indices = std::make_index_sequence<sizeof...(T) - n>;
            using Indexer = types_detail::indexer<std::make_index_sequence<sizeof...(T)>, T...>;
            return decltype(helper<n, Indexer>(Indices{})){};
        }
    };

    // Searchable
    template <>
    struct contains_impl<hana::experimental::types_tag> {
        template <typename U>
        struct is_same_as {
            template <typename T>
            struct apply {
                static constexpr bool value = std::is_same<U, T>::value;
            };
        };

        template <typename ...T, typename U>
        static constexpr auto apply(hana::experimental::types<T...> const&, U const&)
            -> hana::bool_<
                detail::any_of<is_same_as<typename U::type>::template apply, T...>::value
            >
        { return {}; }

        static constexpr hana::false_ apply(...) { return {}; }
    };

    // Comparable
    template <>
    struct equal_impl<hana::experimental::types_tag, hana::experimental::types_tag> {
        template <typename Types>
        static constexpr hana::true_ apply(Types const&, Types const&)
        { return {}; }

        template <typename Ts, typename Us>
        static constexpr hana::false_ apply(Ts const&, Us const&)
        { return {}; }
    };

    namespace types_detail {
        template <typename ...Xs>
        struct make_flatten_indices {
            using type = detail::flatten_indices<
                decltype(hana::length(Xs{}))::value...
            >;
        };

        // Alternate implementation of `unpack_flatten` that uses `experimental::types`
        template <typename Xs, typename F>
        constexpr decltype(auto) unpack_flatten(Xs&& xs, F&& f) {
            using Indices = typename decltype(hana::unpack(experimental::to_types(xs),
                hana::metafunction<make_flatten_indices>))::type;
            return Indices::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f),
                            std::make_index_sequence<Indices::flat_length>{});
        }
    }

    // Applicative

    template <>
    struct ap_impl<hana::experimental::types_tag> {
        template <typename F, typename X>
        static constexpr decltype(auto) apply(F&& f, X&& x) {
            return hana::chain(
                static_cast<F&&>(f),
                hana::partial(hana::transform, static_cast<X&&>(x))
            );
        }
    };

    template <>
    struct lift_impl<hana::experimental::types_tag> {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::experimental::make_types(static_cast<X&&>(x)); }
    };

    // Monad

    template <>
    struct flatten_impl<experimental::types_tag> {
        template <typename Xs>
        static constexpr auto apply(Xs&& xs) {
            return types_detail::unpack_flatten(static_cast<Xs&&>(xs), hana::experimental::make_types);
        }
    };

    // MonadPlus

    template <>
    struct append_impl<experimental::types_tag> {
        template <typename ...T, typename U>
        static constexpr auto apply(experimental::types<T...> const&, U const&)
            -> experimental::types<T..., U>
        { return {}; }
    };

    template <>
    struct concat_impl<experimental::types_tag> {
        template <typename ...T, typename ...U>
        static constexpr auto apply(experimental::types<T...> const&, experimental::types<U...> const&)
            -> experimental::types<T..., U...>
        { return {}; }
    };

    template <>
    struct prepend_impl<experimental::types_tag> {
        template <typename ...T, typename U>
        static constexpr auto apply(experimental::types<T...> const&, U const&)
            -> experimental::types<U, T...>
        { return {}; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXPERIMENTAL_TYPES_HPP
