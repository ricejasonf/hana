// Copyright Sergey Nizovtsev 2016
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/core/is_a.hpp>
#include <parmexpr/hana/functional/partial.hpp>
#include <parmexpr/hana/product.hpp>
#include <parmexpr/hana/range.hpp>
#include <parmexpr/hana/traits.hpp>
#include <parmexpr/hana/transform.hpp>
#include <parmexpr/hana/tuple.hpp>
#include <parmexpr/hana/type.hpp>

namespace hana = parmexpr::hana;

int main() {
    constexpr auto type = hana::type_c<int[2][3][4]>;

    BOOST_HANA_CONSTANT_CHECK(
        hana::is_an<hana::integral_constant_tag<size_t>>(
            hana::traits::extent(type, hana::uint_c<1>)
        )
    );

    // Check that we can multiple extents in size_t's ring
    hana::product<hana::integral_constant_tag<size_t>>(
        hana::transform(
            hana::to_tuple(
                hana::make_range(
                    hana::size_c<0>,
                    hana::traits::rank(type)
                )
            ),
            hana::partial(hana::traits::extent, type)
        )
    );
}
