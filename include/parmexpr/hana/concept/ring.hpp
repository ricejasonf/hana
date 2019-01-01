/*!
@file
Defines `parmexpr::hana::Ring`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_RING_HPP
#define BOOST_HANA_CONCEPT_RING_HPP

#include <parmexpr/hana/fwd/concept/ring.hpp>

#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/default.hpp>
#include <parmexpr/hana/core/tag_of.hpp>
#include <parmexpr/hana/detail/integral_constant.hpp>
#include <parmexpr/hana/mult.hpp>
#include <parmexpr/hana/one.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename R>
    struct Ring
        : hana::integral_constant<bool,
            !is_default<one_impl<typename tag_of<R>::type>>::value &&
            !is_default<mult_impl<typename tag_of<R>::type,
                                  typename tag_of<R>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_RING_HPP
