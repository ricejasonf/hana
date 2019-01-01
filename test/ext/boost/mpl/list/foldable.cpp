// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/mpl/list.hpp>

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/unpack.hpp>
#include <parmexpr/hana/type.hpp>

#include <laws/base.hpp>
#include <laws/foldable.hpp>

#include <parmexpr/mpl/list.hpp>
namespace hana = parmexpr::hana;
namespace mpl = parmexpr::mpl;


struct t1; struct t2; struct t3; struct t4;

int main() {
    // unpack
    {
        hana::test::_injection<0> f{};
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::unpack(mpl::list<>{}, f),
            f()
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::unpack(mpl::list<t1>{}, f),
            f(hana::type_c<t1>)
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::unpack(mpl::list<t1, t2>{}, f),
            f(hana::type_c<t1>, hana::type_c<t2>)
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::unpack(mpl::list<t1, t2, t3>{}, f),
            f(hana::type_c<t1>, hana::type_c<t2>, hana::type_c<t3>)
        ));
    }

    // laws
    auto lists = hana::make_tuple(
          mpl::list<>{}
        , mpl::list<t1>{}
        , mpl::list<t1, t2>{}
        , mpl::list<t1, t2, t3>{}
        , mpl::list<t1, t2, t3, t4>{}
    );

    hana::test::TestFoldable<hana::ext::parmexpr::mpl::list_tag>{lists};
}
