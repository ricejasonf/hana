/*!
@file
Defines `parmexpr::hana::members`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MEMBERS_HPP
#define BOOST_HANA_MEMBERS_HPP

#include <parmexpr/hana/fwd/members.hpp>

#include <parmexpr/hana/accessors.hpp>
#include <parmexpr/hana/concept/struct.hpp>
#include <parmexpr/hana/config.hpp>
#include <parmexpr/hana/core/dispatch.hpp>
#include <parmexpr/hana/second.hpp>
#include <parmexpr/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Object>
    constexpr auto members_t::operator()(Object&& object) const {
        using S = typename hana::tag_of<Object>::type;
        using Members = BOOST_HANA_DISPATCH_IF(members_impl<S>,
            hana::Struct<S>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::Struct<S>::value,
            "hana::members(object) requires 'object' to be a Struct");
        #endif

        return Members::apply(static_cast<Object&&>(object));
    }
    //! @endcond

    namespace struct_detail {
        template <typename Holder, typename Forward>
        struct members_helper {
            Holder object;
            template <typename Accessor>
            constexpr decltype(auto) operator()(Accessor&& accessor) const {
                return hana::second(static_cast<Accessor&&>(accessor))(
                    static_cast<Forward>(object)
                );
            }
        };
    }

    template <typename S, bool condition>
    struct members_impl<S, when<condition>> : default_ {
        template <typename Object>
        static constexpr auto apply(Object&& object) {
            return hana::transform(hana::accessors<S>(),
                struct_detail::members_helper<Object&, Object&&>{object}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MEMBERS_HPP
