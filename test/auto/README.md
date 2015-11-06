The headers in this directory provide facilities for automatic unit testing.
Basically, each header defines unit tests for an algorithm or a set of related
algorithms. To get the tests for these algorithms, simply include the header
at global scope. However, before including the header, you must define the
following macros:

    `MAKE_TUPLE(...)`
        Must expand to a sequence holding `__VA_ARGS__`. A valid definition
        would be `hana::make_tuple(__VA_ARGS__)`.

    `TUPLE_TYPE(...)`
        Must expand to the type of a sequence holding objects of type `__VA_ARGS__`.
        A valid definition would be `hana::tuple<__VA_ARGS__>`.

    `TUPLE_TAG`
        Must expand to the tag of the sequence. A valid definition would
        be `hana::tuple_tag`.

If `MAKE_TUPLE` can't be used inside a constant expression, the
`MAKE_TUPLE_NO_CONSTEXPR` macro must also be defined.
