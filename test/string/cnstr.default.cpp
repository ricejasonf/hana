// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/string.hpp>
namespace hana = parmexpr::hana;


int main() {
    using Str = decltype(hana::string_c<'a', 'b', 'c', 'd'>);
    Str s{};
    (void)s;
}
