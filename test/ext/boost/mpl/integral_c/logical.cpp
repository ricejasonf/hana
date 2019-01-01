// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/mpl/integral_c.hpp>

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/eval_if.hpp>
#include <parmexpr/hana/functional/always.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/tuple.hpp>

#include <laws/base.hpp>
#include <laws/logical.hpp>

#include <parmexpr/mpl/bool.hpp>
#include <parmexpr/mpl/int.hpp>
#include <parmexpr/mpl/integral_c.hpp>
namespace hana = parmexpr::hana;
namespace mpl = parmexpr::mpl;


int main() {
    // eval_if
    {
        auto t = hana::test::ct_eq<3>{};
        auto e = hana::test::ct_eq<4>{};

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::eval_if(mpl::true_{}, hana::always(t), hana::always(e)),
            t
        ));

        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::eval_if(mpl::false_{}, hana::always(t), hana::always(e)),
            e
        ));
    }

    // not_
    {
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::not_(mpl::true_{}),
            mpl::false_{}
        ));
        BOOST_HANA_CONSTANT_CHECK(hana::equal(
            hana::not_(mpl::false_{}),
            mpl::true_{}
        ));
    }

    // laws
    hana::test::TestLogical<hana::ext::parmexpr::mpl::integral_c_tag<int>>{
        hana::make_tuple(
            mpl::int_<-2>{}, mpl::integral_c<int, 0>{}, mpl::integral_c<int, 3>{}
        )
    };

    hana::test::TestLogical<hana::ext::parmexpr::mpl::integral_c_tag<bool>>{
        hana::make_tuple(
            mpl::true_{}, mpl::false_{},
            mpl::integral_c<bool, true>{}, mpl::integral_c<bool, false>{}
        )
    };
}
