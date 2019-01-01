// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/mpl/list.hpp>

#include <parmexpr/hana/tuple.hpp>

#include <laws/comparable.hpp>

#include <parmexpr/mpl/list.hpp>
namespace hana = parmexpr::hana;
namespace mpl = parmexpr::mpl;


struct t1; struct t2; struct t3; struct t4;

int main() {
    auto lists = hana::make_tuple(
          mpl::list<>{}
        , mpl::list<t1>{}
        , mpl::list<t1, t2>{}
        , mpl::list<t1, t2, t3>{}
        , mpl::list<t1, t2, t3, t4>{}
    );

    hana::test::TestComparable<hana::ext::parmexpr::mpl::list_tag>{lists};
}
