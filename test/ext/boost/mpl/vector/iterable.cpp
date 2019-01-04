// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/mpl/vector.hpp>

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/drop_front_exactly.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/front.hpp>
#include <parmexpr/hana/is_empty.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/tuple.hpp>
#include <parmexpr/hana/type.hpp>

#include <laws/iterable.hpp>

#include <parmexpr/mpl/vector.hpp>
namespace hana = parmexpr::hana;
namespace mpl = parmexpr::mpl;


struct t1; struct t2; struct t3; struct t4;

int main() {
    // front
    {
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::front(mpl::vector<t1>{}),
            hana::type_c<t1>
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::front(mpl::vector<t1, t2>{}),
            hana::type_c<t1>
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::front(mpl::vector<t1, t2, t3>{}),
            hana::type_c<t1>
        ));
    }

    // drop_front_exactly
    {
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(mpl::vector<t1>{}),
            mpl::vector<>{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(mpl::vector<t1, t2>{}),
            mpl::vector<t2>{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(mpl::vector<t1, t2, t3>{}),
            mpl::vector<t2, t3>{}
        ));


        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(mpl::vector<t1, t2, t3>{}, hana::size_c<2>),
            mpl::vector<t3>{}
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(mpl::vector<t1, t2, t3, t4>{}, hana::size_c<2>),
            mpl::vector<t3, t4>{}
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::drop_front_exactly(mpl::vector<t1, t2, t3, t4>{}, hana::size_c<3>),
            mpl::vector<t4>{}
        ));
    }

    // is_empty
    {
        BOOST_HANA_CONSTANT_CHECK(hana::is_empty(mpl::vector<>{}));
        BOOST_HANA_CONSTANT_CHECK(hana::is_empty(mpl::vector0<>{}));

        BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::is_empty(mpl::vector<t1>{})));
        BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::is_empty(mpl::vector1<t1>{})));

        BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::is_empty(mpl::vector<t1, t2>{})));
        BOOST_HANA_CONSTANT_CHECK(hana::not_(hana::is_empty(mpl::vector2<t1, t2>{})));
    }

    // laws
    auto vectors = hana::make_tuple(
          mpl::vector<>{}
        , mpl::vector<t1>{}
        , mpl::vector<t1, t2>{}
        , mpl::vector<t1, t2, t3>{}
        , mpl::vector<t1, t2, t3, t4>{}
    );
    hana::test::TestIterable<hana::ext::parmexpr::mpl::vector_tag>{vectors};
}
