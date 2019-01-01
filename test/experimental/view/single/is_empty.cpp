// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/experimental/view.hpp>
#include <parmexpr/hana/is_empty.hpp>
#include <parmexpr/hana/not.hpp>
namespace hana = parmexpr::hana;


template <int> struct undefined { };

int main() {
    {
        auto single = hana::experimental::single_view(undefined<0>{});
        BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::is_empty(single)));
    }
}
