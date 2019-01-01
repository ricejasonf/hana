// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/ext/parmexpr/mpl/vector.hpp>

#include <parmexpr/hana/tuple.hpp>

#include <laws/searchable.hpp>

#include <parmexpr/mpl/vector.hpp>
namespace hana = parmexpr::hana;
namespace mpl = parmexpr::mpl;


struct t1; struct t2; struct t3; struct t4;

int main() {
    auto vectors = hana::make_tuple(
          mpl::vector<>{}
        , mpl::vector<t1>{}
        , mpl::vector<t1, t2>{}
        , mpl::vector<t1, t2, t3>{}
        , mpl::vector<t1, t2, t3, t4>{}
    );

    auto keys = hana::tuple_t<t1, t2, void>;

    hana::test::TestSearchable<hana::ext::parmexpr::mpl::vector_tag>{vectors, keys};
}
