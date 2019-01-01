/*!
@file
Includes all the library components except the adapters for external
libraries.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_HPP
#define BOOST_HANA_HPP

//! @defgroup group-concepts Concepts
//! Concepts provided by the library.

//! @defgroup group-datatypes Data types
//! General purpose data types provided by the library.

//! @defgroup group-functional Functional
//! General purpose function objects.

//! @defgroup group-core Core
//! Core utilities of the library.

//! @defgroup group-experimental Experimental features
//! Experimental features that may or may not make it into the library.
//! These features should not expected to be stable.

//! @defgroup group-ext External adapters
//! Adapters for external libraries.

//! @defgroup group-config Configuration options
//! Configurable options to tweak the global behavior of the library.

//! @defgroup group-assertions Assertions
//! Macros to perform different kinds of assertions.

//! @defgroup group-details Details
//! Implementation details. Do not rely on anything here, even if it is
//! documented.

// Include config.hpp first, so that warning messages about compiler support
// appear as soon as possible.
#include <parmexpr/hana/config.hpp>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace parmexpr {
    //! Namespace containing everything in the library.
    namespace hana {
        //! Namespace containing C++14 user-defined literals provided by Hana.
        namespace literals {}
    }
}
#endif

#include <parmexpr/hana/accessors.hpp>
#include <parmexpr/hana/adapt_adt.hpp>
#include <parmexpr/hana/adapt_struct.hpp>
#include <parmexpr/hana/adjust.hpp>
#include <parmexpr/hana/adjust_if.hpp>
#include <parmexpr/hana/all.hpp>
#include <parmexpr/hana/all_of.hpp>
#include <parmexpr/hana/and.hpp>
#include <parmexpr/hana/any.hpp>
#include <parmexpr/hana/any_of.hpp>
#include <parmexpr/hana/ap.hpp>
#include <parmexpr/hana/append.hpp>
#include <parmexpr/hana/assert.hpp>
#include <parmexpr/hana/at.hpp>
#include <parmexpr/hana/at_key.hpp>
#include <parmexpr/hana/back.hpp>
#include <parmexpr/hana/basic_tuple.hpp>
#include <parmexpr/hana/bool.hpp>
#include <parmexpr/hana/cartesian_product.hpp>
#include <parmexpr/hana/chain.hpp>
#include <parmexpr/hana/comparing.hpp>
#include <parmexpr/hana/concat.hpp>
#include <parmexpr/hana/concept.hpp>
#include <parmexpr/hana/contains.hpp>
#include <parmexpr/hana/core.hpp>
#include <parmexpr/hana/count.hpp>
#include <parmexpr/hana/count_if.hpp>
#include <parmexpr/hana/cycle.hpp>
#include <parmexpr/hana/define_struct.hpp>
#include <parmexpr/hana/difference.hpp>
#include <parmexpr/hana/div.hpp>
#include <parmexpr/hana/drop_back.hpp>
#include <parmexpr/hana/drop_front.hpp>
#include <parmexpr/hana/drop_front_exactly.hpp>
#include <parmexpr/hana/drop_while.hpp>
#include <parmexpr/hana/duplicate.hpp>
#include <parmexpr/hana/empty.hpp>
#include <parmexpr/hana/equal.hpp>
#include <parmexpr/hana/erase_key.hpp>
#include <parmexpr/hana/eval.hpp>
#include <parmexpr/hana/eval_if.hpp>
#include <parmexpr/hana/extend.hpp>
#include <parmexpr/hana/extract.hpp>
#include <parmexpr/hana/fill.hpp>
#include <parmexpr/hana/filter.hpp>
#include <parmexpr/hana/find.hpp>
#include <parmexpr/hana/find_if.hpp>
#include <parmexpr/hana/first.hpp>
#include <parmexpr/hana/flatten.hpp>
#include <parmexpr/hana/fold.hpp>
#include <parmexpr/hana/fold_left.hpp>
#include <parmexpr/hana/fold_right.hpp>
#include <parmexpr/hana/for_each.hpp>
#include <parmexpr/hana/front.hpp>
#include <parmexpr/hana/functional.hpp>
#include <parmexpr/hana/fuse.hpp>
#include <parmexpr/hana/greater.hpp>
#include <parmexpr/hana/greater_equal.hpp>
#include <parmexpr/hana/group.hpp>
#include <parmexpr/hana/index_if.hpp>
#include <parmexpr/hana/if.hpp>
#include <parmexpr/hana/insert.hpp>
#include <parmexpr/hana/insert_range.hpp>
#include <parmexpr/hana/integral_constant.hpp>
#include <parmexpr/hana/intersection.hpp>
#include <parmexpr/hana/intersperse.hpp>
#include <parmexpr/hana/is_disjoint.hpp>
#include <parmexpr/hana/is_empty.hpp>
#include <parmexpr/hana/is_subset.hpp>
#include <parmexpr/hana/keys.hpp>
#include <parmexpr/hana/lazy.hpp>
#include <parmexpr/hana/length.hpp>
#include <parmexpr/hana/less.hpp>
#include <parmexpr/hana/less_equal.hpp>
#include <parmexpr/hana/lexicographical_compare.hpp>
#include <parmexpr/hana/lift.hpp>
#include <parmexpr/hana/map.hpp>
#include <parmexpr/hana/max.hpp>
#include <parmexpr/hana/maximum.hpp>
#include <parmexpr/hana/members.hpp>
#include <parmexpr/hana/min.hpp>
#include <parmexpr/hana/minimum.hpp>
#include <parmexpr/hana/minus.hpp>
#include <parmexpr/hana/mod.hpp>
#include <parmexpr/hana/monadic_compose.hpp>
#include <parmexpr/hana/monadic_fold_left.hpp>
#include <parmexpr/hana/monadic_fold_right.hpp>
#include <parmexpr/hana/mult.hpp>
#include <parmexpr/hana/negate.hpp>
#include <parmexpr/hana/none.hpp>
#include <parmexpr/hana/none_of.hpp>
#include <parmexpr/hana/not.hpp>
#include <parmexpr/hana/not_equal.hpp>
#include <parmexpr/hana/one.hpp>
#include <parmexpr/hana/optional.hpp>
#include <parmexpr/hana/or.hpp>
#include <parmexpr/hana/ordering.hpp>
#include <parmexpr/hana/pair.hpp>
#include <parmexpr/hana/partition.hpp>
#include <parmexpr/hana/permutations.hpp>
#include <parmexpr/hana/plus.hpp>
#include <parmexpr/hana/power.hpp>
#include <parmexpr/hana/prefix.hpp>
#include <parmexpr/hana/prepend.hpp>
#include <parmexpr/hana/product.hpp>
#include <parmexpr/hana/range.hpp>
#include <parmexpr/hana/remove.hpp>
#include <parmexpr/hana/remove_at.hpp>
#include <parmexpr/hana/remove_if.hpp>
#include <parmexpr/hana/remove_range.hpp>
#include <parmexpr/hana/repeat.hpp>
#include <parmexpr/hana/replace.hpp>
#include <parmexpr/hana/replace_if.hpp>
#include <parmexpr/hana/replicate.hpp>
#include <parmexpr/hana/reverse.hpp>
#include <parmexpr/hana/reverse_fold.hpp>
#include <parmexpr/hana/scan_left.hpp>
#include <parmexpr/hana/scan_right.hpp>
#include <parmexpr/hana/second.hpp>
#include <parmexpr/hana/set.hpp>
#include <parmexpr/hana/size.hpp>
#include <parmexpr/hana/slice.hpp>
#include <parmexpr/hana/sort.hpp>
#include <parmexpr/hana/span.hpp>
#include <parmexpr/hana/string.hpp>
#include <parmexpr/hana/suffix.hpp>
#include <parmexpr/hana/sum.hpp>
#include <parmexpr/hana/symmetric_difference.hpp>
#include <parmexpr/hana/take_back.hpp>
#include <parmexpr/hana/take_front.hpp>
#include <parmexpr/hana/take_while.hpp>
#include <parmexpr/hana/tap.hpp>
#include <parmexpr/hana/then.hpp>
#include <parmexpr/hana/traits.hpp>
#include <parmexpr/hana/transform.hpp>
#include <parmexpr/hana/tuple.hpp>
#include <parmexpr/hana/type.hpp>
#include <parmexpr/hana/unfold_left.hpp>
#include <parmexpr/hana/unfold_right.hpp>
#include <parmexpr/hana/union.hpp>
#include <parmexpr/hana/unique.hpp>
#include <parmexpr/hana/unpack.hpp>
#include <parmexpr/hana/value.hpp>
#include <parmexpr/hana/version.hpp>
#include <parmexpr/hana/while.hpp>
#include <parmexpr/hana/zero.hpp>
#include <parmexpr/hana/zip.hpp>
#include <parmexpr/hana/zip_shortest.hpp>
#include <parmexpr/hana/zip_shortest_with.hpp>
#include <parmexpr/hana/zip_with.hpp>

#endif // !BOOST_HANA_HPP
