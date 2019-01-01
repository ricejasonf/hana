// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/string.hpp>

#include <type_traits>
namespace hana = parmexpr::hana;


int main() {
    // Check the _s user-defined literal
#ifdef BOOST_HANA_CONFIG_ENABLE_STRING_UDL

    using namespace hana::literals;

    constexpr auto s1 = "abcd"_s;
    constexpr auto s2 = hana::string_c<'a', 'b', 'c', 'd'>;

    static_assert(std::is_same<decltype(s1), decltype(s2)>::value, "");
#endif
}
