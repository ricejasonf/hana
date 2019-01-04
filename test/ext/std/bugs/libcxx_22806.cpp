// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/chain.hpp>
#include <parmexpr/hana/ext/std/tuple.hpp>
#include <parmexpr/hana/functional/compose.hpp>
#include <parmexpr/hana/lift.hpp>

#include <laws/base.hpp>

#include <tuple>
namespace hana = parmexpr::hana;


int main() {
    using M = hana::ext::std::tuple_tag;
    auto m = std::make_tuple(hana::test::ct_eq<0>{});
    auto f = hana::compose(hana::lift<M>, hana::test::_injection<0>{});
    hana::chain(m, hana::compose(hana::lift<M>, f));
}
