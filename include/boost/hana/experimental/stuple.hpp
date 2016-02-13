/*!
@file
Defines `boost::hana::experimental::stuple`.

@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXPERIMENTAL_STUPLE_HPP
#define BOOST_HANA_EXPERIMENTAL_STUPLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/any_of.hpp>
#include <boost/hana/experimental/types.hpp>
#include <boost/hana/ext/std/integer_sequence.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/contains.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/transform.hpp>
#include <boost/hana/fwd/unpack.hpp>
#include <boost/hana/sum.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
namespace experimental {

template <typename ...Xn>
struct stuple;

struct stuple_tag;

//////////////////////////////////////////////////////////////////////

namespace stuple_detail {
    struct append_offset_t {
        template <std::size_t ...i, typename Size>
        constexpr auto operator()(std::index_sequence<i...> list, Size size) {
            // offset is sum of all previous sizes
            // which is also the previous offset + size
            return std::index_sequence<i..., (hana::at_c<sizeof...(i)>(list) + size)>{};
        }
    };
    constexpr append_offset_t append_offset;

    template <typename ...Xn>
    using make_offsets = decltype(
        hana::fold_left(
            hana::make_tuple(hana::size_c<sizeof(Xn)>...),
            std::index_sequence<0>,
            stuple_detail::append_offset
        )
    );

    template <typename ...Xn>
    using make_storage = typename std::aligned_storage<
        decltype(hana::sum(std::index_sequence<sizeof(Xn)...>))>::type;
}

//////////////////////////////////////////////////////////////////////

template <std::size_t ...n, typename ...Xn>
struct stuple_impl {
    using Storage = stuple_detail::make_storage<Xn...>;
    using Offsets = stuple_detail::make_offsets<Xn...>;
    using Types = hana::experimental::types<Xn...>;
    Storage storage;

    template <typename ...T>
    constexpr stuple_impl(stuple_detail::cnstr_tag, T&& ...t) {
        constexpr Offsets offsets{}; 
        new (&storage + hana::at_c<n>(offsets)) T(std::move(t));
    }

    // append constructor (original as rvalue only)
    template <typename ...Xs, typename X>
    constexpr stuple_impl(stuple_impl<Xs...>&& xs, X&& x) {
        new (&storage) stuple_impl<Xs...>::Storage(std::move(xs.storage));
        // offset is sizeof original
        new (&storage + sizeof(stuple<Xs...>)) X(std::move(x));
    }
};

template <typename ...Xn>
struct stuple
    : stuple_impl<std::make_index_sequence<sizeof...(Xn)>, Xn...>
{
    using stuple_impl<std::make_index_sequence<sizeof...(Xn)>, Xn...>::stuple_impl;
};

} // end namespace experimental

template <typename ...Xn>
struct tag_of<hana::experimental::stuple<Xn...>> {
    using type = hana::experimental::stuple;
};

template <>
struct make_impl<hana::experimental::stuple_tag> {
    template<typename ...Xs>
    static constexpr auto apply(Xs&& ...xs) {
        return hana::experimental::stuple(std::forward<Xs&&>(xs)...);
    }
};

// Foldable
template <>
struct unpack_impl<hana::experimental::stuple_tag> {
    template <std::size_t ...i, typename ...T, typename F>
    static constexpr decltype(auto)
    apply(hana::experimental::stuple_impl<std::index_sequence<i...>, T...> const& xs, F&& f) {
        return stuple_detail::get_impl<i>(xs)
    }

    template <std::size_t ...i, typename ...T, typename F>
    static constexpr decltype(auto)
    apply(hana::experimental::stuple_impl<std::index_sequence<i...>, T...>& xs, F&& f) {
        return stuple_detail::get_impl<i>(xs)
    }

    template <std::size_t ...i, typename ...T, typename F>
    static constexpr decltype(auto)
    apply(hana::experimental::stuple_impl<std::index_sequence<i...>, T...>&& xs, F&& f) {
        return stuple_detail::get_impl<i>(xs)
    }
};

// Iterable
template <>
struct at_impl<hana::experimental::stuple_tag> {
    template <typename Stuple, typename I>
    static constexpr decltype(auto) apply(Stuple const& xs, I const&) {
        return stuple_detail::get_impl<I::value>(xs);
    }
};

template <>
struct is_empty_impl<hana::experimental::stuple_tag> {
    template <typename ...T>
    static constexpr hana::bool_<sizeof...(T) == 0>
    apply(hana::experimental::stuple<T...> const&)
    { return {}; }
};

template <>
struct drop_front_impl<hana::experimental::stuple_tag> {
    template <typename ...Xs, typename N>
    static constexpr auto
    apply(hana::experimental::stuple<T...>&&, N const&) {
        constexpr std::size_t n = N::value > sizeof...(T) ? sizeof...(T) : N::value;
        using Indices = std::make_index_sequence<sizeof...(T) - n>;
        using Indexer = types_detail::indexer<std::make_index_sequence<sizeof...(T)>, T...>;
        return decltype(helper<n, Indexer>(Indices{})){};
    }
};
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXPERIMENTAL_STUPLE_HPP
