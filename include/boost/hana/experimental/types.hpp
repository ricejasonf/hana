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
#include <boost/hana/detail/any_of.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/contains.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/transform.hpp>
#include <boost/hana/fwd/unpack.hpp>
#include <boost/hana/type.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    namespace experimental {
        //! @ingroup group-datatypes
        //! @todo
        template <typename ...T>
        struct types;

        //! Tag representing a `hana::types` container.
        //! @relates hana::types
        struct types_tag;

        //////////////////////////////////////////////////////////////////////

        template <typename ...T>
        struct types { };
    } // end namespace experimental

    template <typename ...T>
    struct tag_of<experimental::types<T...>> {
        using type = experimental::types_tag;
    };

    // Foldable
    template <>
    struct unpack_impl<hana::experimental::types_tag> {
        template <typename ...T, typename F, typename = typename std::enable_if<
            !hana::Metafunction<F>::value
        >::type>
        static constexpr decltype(auto) apply(hana::experimental::types<T...> const&, F&& f) {
            return static_cast<F&&>(f)(hana::type<T>{}...);
        }

        template <typename ...T, typename F, typename = typename std::enable_if<
            hana::Metafunction<F>::value
        >::type>
        static constexpr hana::type<typename F::template apply<T...>::type>
        apply(hana::experimental::types<T...> const&, F const&) { return {}; }
    };

    // Functor
    template <>
    struct transform_impl<hana::experimental::types_tag> {
        template <typename ...T, typename F, typename = typename std::enable_if<
            !hana::Metafunction<F>::value
        >::type>
        static constexpr auto apply(hana::experimental::types<T...> const&, F&& f)
            -> hana::experimental::types<typename decltype(f(hana::type<T>{}))::type...>
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
            return hana::type<Nth>{};
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXPERIMENTAL_TYPES_HPP
