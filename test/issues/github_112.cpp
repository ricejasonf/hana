// Copyright Louis Dionne 2013-2017
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

#include <parmexpr/hana/accessors.hpp>
#include <parmexpr/hana/adapt_struct.hpp>
#include <parmexpr/hana/define_struct.hpp>
namespace hana = parmexpr::hana;


struct Person {
    BOOST_HANA_DEFINE_STRUCT(Person,
        (int, age)
    );
};

struct Employee {
    int age;
};

BOOST_HANA_ADAPT_STRUCT(Employee, age);

constexpr auto person_members = hana::accessors<Person>();
constexpr auto employee_members = hana::accessors<Employee>();

int main() {
    (void)person_members;
    (void)employee_members;
}
