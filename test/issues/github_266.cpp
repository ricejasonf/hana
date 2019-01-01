// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/bool.hpp>
#include <parmexpr/hana/experimental/types.hpp>
#include <parmexpr/hana/replace_if.hpp>
#include <parmexpr/hana/type.hpp>
namespace hana = parmexpr::hana;


struct predicate { hana::true_ operator()(...) const; };

int main() {
    auto types = hana::experimental::types<void, void>{};
    hana::replace_if(types, predicate{}, hana::type<struct anything>{});
}
