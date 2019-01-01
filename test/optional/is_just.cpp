// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/optional.hpp>
namespace hana = parmexpr::hana;


struct undefined { };

int main() {
    BOOST_HANA_CONSTANT_CHECK(hana::is_just(hana::just(undefined{})));
    BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::is_just(hana::nothing)));
}
