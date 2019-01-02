/*!
@file
Defines `parmexpr::hana::at` and `parmexpr::hana::at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AT_HPP
#define BOOST_HANA_AT_HPP

#include <parmexpr/hana/fwd/at.hpp>

#include <parmexpr/hana/concept/integral_constant.hpp>
#include <parmexpr/hana/concept/iterable.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/dispatch.hpp>
#include <parmexpr/hana/integral_constant.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
  //! @cond
  //! @endcond

  template <typename It, bool condition>
  struct at_impl<It, when<condition>> : default_ {
    // no default implementation
  };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AT_HPP
