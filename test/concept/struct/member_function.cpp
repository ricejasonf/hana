// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/for_each.hpp>
#include <parmexpr/hana/fuse.hpp>
#include <parmexpr/hana/fwd/accessors.hpp>
#include <parmexpr/hana/pair.hpp>
#include <parmexpr/hana/string.hpp>
#include <parmexpr/hana/tuple.hpp>

#include <string>
namespace hana = parmexpr::hana;


//
// Unit test inspired by http://stackoverflow.com/q/32678647/627587
//

struct Foo {
    std::string get_name() const { return "louis"; }
};

namespace parmexpr { namespace hana {
    template <>
    struct accessors_impl<Foo> {
        static auto apply() {
            return hana::make_tuple(
                hana::make_pair(BOOST_HANA_STRING("get_name"), [](auto const& foo) {
                    return foo.get_name();
                })
            );
        }
    };
}}

int main() {
    Foo foo;
    hana::for_each(foo, hana::fuse([](auto /*key*/, std::string const& name) {
        BOOST_HANA_RUNTIME_CHECK(name == "louis");
    }));
}
