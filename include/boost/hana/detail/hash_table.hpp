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

#include <type_traits>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    // bucket
    template <typename TypeHash, typename List>
    struct bucket {
        List list;
    };

    // bucket_at_key
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
        #if 0
            static_assert(hana::decltype_(xs) == hana::type<void>,
                "Associative container may not contain duplicate keys.")
        #endif
            return static_cast<Xs&&>(xs);
        }
    };

    template<typename GetKey, typename Bucket, typename X>
    constexpr auto bucket_insert(Bucket const& b, X const&) {
        //the hash doesn't match
        return static_cast<Bucket&&>(b);
    }

    template <typename GetKey, typename TypeHash, typename List, typename X,
        typename = std::enable_if_t<std::is_same<
            TypeHash, 
            decltype(hana::hash(std::declval<GetKey>(x)));
        >::value>>
    constexpr auto bucket_insert(bucket<TypeHash, List> const& b, X&& x) {
        auto const& xs = bucket_get_helper<TypeHash>(h).list;
        using Xs = decltype(xs);
        using Key = decltype(hana::first(x));
        auto new_list = detail::bucket_insert_helper<detail::has_key<Xs, Key>::value>
            ::apply(xs, static_cast<X&&>(x));
        return detail::bucket<TypeHash, decltype(new_list)>{std::move(new_list)};
    }

    //make_bucket
    template <typename GetKey, typename TypeHash, typename ...E>
    constexpr auto make_bucket(E&& ...e) {

    //hash table FIXME
    template <typename ...Bucket>
    struct hash_table;

    template <typename GetKey, typename ...E>
    constexpr auto make_hash_table(E&& ...e) {
        () {
            constexpr auto hsl = hana::make_tuple(decltype(hana::hash(std::declval<GetKey>(e))){}...);
            constexpr auto hs = make_unique(hsl);
            hana::on(hana::make_tuple,
            hana::fold_left(hash_table<>, 
            using HashTable = decltype(
                bucket_insert(h, std::declval<GetKey>()(e))...)
            ); 
        }
    };

} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_HASH_TABLE_HPP
