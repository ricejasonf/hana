/*!
@file
Defines `parmexpr::hana::Searchable`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_SEARCHABLE_HPP
#define BOOST_HANA_CONCEPT_SEARCHABLE_HPP

#include <parmexpr/hana/fwd/concept/searchable.hpp>

#include <parmexpr/hana/any_of.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/default.hpp>
#include <parmexpr/hana/core/tag_of.hpp>
#include <parmexpr/hana/detail/integral_constant.hpp>
#include <parmexpr/hana/find_if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Searchable
        : hana::integral_constant<bool,
            !is_default<any_of_impl<typename tag_of<S>::type>>::value &&
            !is_default<find_if_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_SEARCHABLE_HPP
