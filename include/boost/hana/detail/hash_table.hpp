/*!
@file
Defines `boost::hana::detail::hash_table`.

@copyright Jason Rice 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_HASH_TABLE_HPP
#define BOOST_HANA_DETAIL_HASH_TABLE_HPP

#include <boost/hana/append.hpp>
#include <boost/hana/detail/index_if.hpp>
#include <boost/hana/hash.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    // bucket
    template <typename TypeHash, typename List>
    struct bucket {
        List list;
    };

    // bucket_get
    template <typename TypeHash, typename List>
    static constexpr detail::bucket<TypeHash, List>&& 
    bucket_get_helper(detail::bucket<TypeHash, List>&& b) {
        return static_cast<detail::bucket<TypeHash, List>&&>(b);
    }

    template <typename TypeHash, typename List>
    static constexpr detail::bucket<TypeHash, List>&
    bucket_get_helper(detail::bucket<TypeHash, List>& b) {
        return b;
    }

    template <typename TypeHash, typename List>
    static constexpr detail::bucket<TypeHash, List> const&
    bucket_get_helper(detail::bucket<TypeHash, List> const& b) {
        return b;
    }

    template <typename M, typename Key>
    static constexpr decltype(auto) bucket_at_key(M const& m, Key const&) {
        using TypeHash = decltype(hana::hash(std::declval<Key>()));
        auto const& list = bucket_get_helper<TypeHash>(m).list;
        using Pack = typename detail::make_pack<decltype(list)>::type;
        using Pred = decltype(
            hana::compose(
                hana::partial(
                    hana::equal.to(std::declval<Key>())
                )
                , hana::first
            )
        );
        return hana::at_c<detail::index_if<Pred, Pack>::value>(list);
    }

    // has_key (requires Key is compile-time Comparable)
    template <typename Xs, typename Key>
    struct has_key {
        using Pack = typename detail::make_pack<Xs>::type;
        using Pred = decltype(
            hana::compose(
                hana::partial(
                    hana::equal.to(std::declval<Key>())
                )
                , hana::first
            )
        );
        static constexpr bool value = detail::index_if<Pred, Pack>::value > -1;
    };

    // bucket_insert
    template <bool cond>
    struct bucket_insert_helper;

    template <>
    struct bucket_insert_helper<false> {
        template <typename Xs, typename X>
        constexpr auto apply(Xs&& xs, X&& x) {
            return hana::append(static_cast<Xs&&>(xs), static_cast<X&&>(x));
        }
    };

    template <>
    struct bucket_insert_helper<true> {
        template <typename Xs, typename X>
        constexpr auto apply(Xs&& xs, X const&) {
            return static_cast<Xs&&>(xs);
        }
    };

    template <typename HashTable, typename X, typename TypeHash>
    constexpr auto bucket_insert(HashTable const& h, X&& x, TypeHash const&) {
        auto const& xs = bucket_get_helper<TypeHash>(h).list;
        using Xs = decltype(xs);
        using Key = decltype(hana::first(x));
        auto new_list = detail::bucket_insert_helper<detail::has_key<Xs, Key>::value>
            ::apply(xs, static_cast<X&&>(x));
        return detail::bucket<TypeHash, decltype(new_list)>{std::move(new_list)};
    }

    //hash table FIXME
    template <typename GetKey, typename ...E>
    struct hash_table
        : detail::bucket<E, decltype(hana::hash(std::declval<GetKey>()(std::declval<E>())))>...
    {
        template <typename ...Xn>
        explicit constexpr auto hash_table(Xn&& ...xn)
            : detail::bucket<E,
                decltype(hana::hash(std::declval<GetKey>()(std::declval<E>())))>{static_cast<Xn&&>(xn)}...
        { }
    };

    template <typename GetKey, typename ...E>
    constexpr auto make_hash_table(E&& ...e) {

    };

} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_HASH_TABLE_HPP
