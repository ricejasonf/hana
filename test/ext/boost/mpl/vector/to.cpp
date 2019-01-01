// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/mpl/vector.hpp>

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/core/to.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/type.hpp>

#include <support/seq.hpp>

#include <parmexpr/mpl/vector.hpp>
namespace hana = parmexpr::hana;
namespace mpl = parmexpr::mpl;


struct t1; struct t2; struct t3; struct t4;

int main() {
    // Conversion from any `Foldable` containing `type`s
    auto foldable = ::seq;
    auto to_vector = hana::to<hana::ext::parmexpr::mpl::vector_tag>;
    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        to_vector(foldable()),
        mpl::vector<>{}
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        to_vector(foldable(hana::type_c<t1>)),
        mpl::vector<t1>{}
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        to_vector(foldable(hana::type_c<t1>, hana::type_c<t2>)),
        mpl::vector<t1, t2>{}
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        to_vector(foldable(hana::type_c<t1>, hana::type_c<t2>, hana::type_c<t3>)),
        mpl::vector<t1, t2, t3>{}
    ));

    BOOST_HANA_CONSTANT_CHECK(hana::equal(
        to_vector(foldable(hana::type_c<t1>, hana::type_c<t2>, hana::type_c<t3>, hana::type_c<t4>)),
        mpl::vector<t1, t2, t3, t4>{}
    ));
}
