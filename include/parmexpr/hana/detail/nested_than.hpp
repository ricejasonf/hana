/*!
@file
Defines `parmexpr::hana::detail::nested_than`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_NESTED_THAN_HPP
#define BOOST_HANA_DETAIL_NESTED_THAN_HPP

#include <parmexpr/hana/detail/nested_than_fwd.hpp>

#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/functional/flip.hpp>
#include <parmexpr/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    template <typename Algorithm>
    template <typename X>
    constexpr decltype(auto) nested_than_t<Algorithm>::operator()(X&& x) const
    { return hana::partial(hana::flip(Algorithm{}), static_cast<X&&>(x)); }
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_NESTED_THAN_HPP
