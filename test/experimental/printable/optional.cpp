// Copyright Jason Rice 2015
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/experimental/printable.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/optional.hpp>

#include <sstream>
namespace hana = parmexpr::hana;


int main() {
    {
        std::ostringstream ss;
        ss << hana::experimental::print(
            hana::just(hana::int_c<5>)
        );
        BOOST_HANA_RUNTIME_CHECK(ss.str() == "just(5)");
    }
    {
        std::ostringstream ss;
        ss << hana::experimental::print(
            hana::nothing
        );
        BOOST_HANA_RUNTIME_CHECK(ss.str() == "nothing");
    }
}
