/*!
@file
Defines `parmexpr::hana::Logical`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_LOGICAL_HPP
#define BOOST_HANA_CONCEPT_LOGICAL_HPP

#include <parmexpr/hana/fwd/concept/logical.hpp>

#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/default.hpp>
#include <parmexpr/hana/core/tag_of.hpp>
#include <parmexpr/hana/detail/integral_constant.hpp>
#include <parmexpr/hana/eval_if.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/while.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename L>
    struct Logical
        : hana::integral_constant<bool,
            !is_default<eval_if_impl<typename tag_of<L>::type>>::value &&
            !is_default<not_impl<typename tag_of<L>::type>>::value &&
            !is_default<while_impl<typename tag_of<L>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_LOGICAL_HPP
