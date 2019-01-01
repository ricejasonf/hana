// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#ifndef BOOST_HANA_TEST_TUPLE_AUTO_SPECS_HPP
#define BOOST_HANA_TEST_TUPLE_AUTO_SPECS_HPP

#include <parmexpr/hana/tuple.hpp>


#define MAKE_TUPLE(...) ::parmexpr::hana::make_tuple(__VA_ARGS__)
#define TUPLE_TYPE(...) ::parmexpr::hana::tuple<__VA_ARGS__>
#define TUPLE_TAG ::parmexpr::hana::tuple_tag

#endif // !BOOST_HANA_TEST_TUPLE_AUTO_SPECS_HPP
