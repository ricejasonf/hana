// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/mpl/integral_c.hpp>

#include <parmexpr/hana/tuple.hpp>
#include <parmexpr/hana/value.hpp>

#include <laws/constant.hpp>

#include <parmexpr/mpl/int.hpp>
#include <parmexpr/mpl/integral_c.hpp>
namespace hana = parmexpr::hana;
namespace mpl = parmexpr::mpl;


int main() {
    // value
    static_assert(hana::value(mpl::integral_c<int, 0>{}) == 0, "");
    static_assert(hana::value(mpl::integral_c<int, 1>{}) == 1, "");
    static_assert(hana::value(mpl::integral_c<int, 3>{}) == 3, "");

    // laws
    hana::test::TestConstant<hana::ext::parmexpr::mpl::integral_c_tag<int>>{
        hana::make_tuple(
            mpl::int_<-10>{}, mpl::int_<-2>{}, mpl::integral_c<int, 0>{},
            mpl::integral_c<int, 1>{}, mpl::integral_c<int, 3>{}
        ),
        hana::tuple_t<int, long, long long>
    };
}
