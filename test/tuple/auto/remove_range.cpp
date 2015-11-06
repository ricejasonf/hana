/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/tuple.hpp>


#define MAKE_TUPLE(...) ::boost::hana::make_tuple(__VA_ARGS__)
#define TUPLE_TYPE(...) ::boost::hana::tuple<__VA_ARGS__>
#define TUPLE_TAG ::boost::hana::tuple_tag

#include "../../auto/remove_range.hpp"

int main() { }
