/*!
@file
Defines `parmexpr::hana::MonadPlus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_PLUS_HPP
#define BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

#include <parmexpr/hana/fwd/concept/monad_plus.hpp>

#include <parmexpr/hana/concat.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/default.hpp>
#include <parmexpr/hana/core/tag_of.hpp>
#include <parmexpr/hana/detail/integral_constant.hpp>
#include <parmexpr/hana/empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct MonadPlus
        : hana::integral_constant<bool,
            !is_default<concat_impl<typename tag_of<M>::type>>::value &&
            !is_default<empty_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_PLUS_HPP
