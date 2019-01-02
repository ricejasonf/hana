/*!
@file
Forward declares `parmexpr::hana::at` and `parmexpr::hana::at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AT_HPP
#define BOOST_HANA_FWD_AT_HPP

#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/dispatch.hpp>
#include <parmexpr/hana/core/tag_of.hpp>
#include <parmexpr/hana/core/when.hpp>
#include <parmexpr/hana/fwd/concept/iterable.hpp>
#include <parmexpr/hana/fwd/integral_constant.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the `n`th element of an iterable.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` and an `IntegralConstant` index, `at` returns the
    //! element located at the index in the linearization of the iterable.
    //! Specifically, given an iterable `xs` with a linearization of
    //! `[x1, ..., xN]`, `at(xs, k)` is equivalent to `xk`.
    //!
    //! If the `Iterable` actually stores the elements it contains, `at` is
    //! required to return a lvalue reference, a lvalue reference to const
    //! or a rvalue reference to the matching element, where the type of
    //! reference must match that of the iterable passed to `at`. If the
    //! `Iterable` does not store the elements it contains (i.e. it generates
    //! them on demand), this requirement is dropped.
    //!
    //!
    //! @param xs
    //! The iterable in which an element is retrieved. The iterable must
    //! contain at least `n + 1` elements.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the 0-based index of
    //! the element to return. It is an error to call `at` with an index that
    //! out of bounds of the iterable.
    //!
    //!
    //! Example
    //! -------
    //! @include example/at.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto at = [](auto&& xs, auto const& n) -> decltype(auto) {
        return tag-dispatched;
    };
#else
  template <typename It, typename = void>
  struct at_impl : at_impl<It, when<true>> { };

  struct at_t {
    template <typename Xs>
    using Tag = typename hana::tag_of<Xs>::type;

    template <typename It>
    using Impl = BOOST_HANA_DISPATCH_IF(at_impl<It>,
      hana::Iterable<It>::value);

    static using operator()(using auto xs, using auto n) {
      return Impl<Tag<decltype(xs)>>::apply(xs, n);
    }
  } inline constexpr at{};
#endif

    //! Equivalent to `at`; provided for convenience.
    //! @ingroup group-Iterable
    //!
    //!
    //! @note
    //! `hana::at_c<n>` is an overloaded function, not a function object.
    //! Hence, it can't be passed to higher-order algorithms. This is done
    //! for compile-time performance reasons.
    //!
    //!
    //! Example
    //! -------
    //! @include example/at_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto at_c = [](auto&& xs) {
        return hana::at(forwarded(xs), hana::size_c<n>);
    };
#else
  template <std::size_t n>
  struct at_c_fn {
    static using operator()(using auto xs) {
      return hana::at(xs, hana::size_t<n>{});
    }
  };

  template <std::size_t n>
  inline constexpr at_c_fn<n> at_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AT_HPP
