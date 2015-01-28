
#ifndef BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_HPP_

#include <boost/contract/ext_/preprocessor/traits/assertion/namespace/name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/namespace/new_name.hpp>
#include <boost/contract/ext_/preprocessor/traits/assertion/kind.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_DONE_(decl_traits) \
    ( \
        BOOST_PP_TUPLE_ELEM(2, 0, decl_traits), \
        BOOST_CONTRACT_EXT_PP_TRAITS_DONE( \
                BOOST_PP_TUPLE_ELEM(2, 1, decl_traits)) \
    )

/* PUBLIC */

// Precondition: decl = `namespace (new-name) as name`.
#define BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_PARSE(decl) \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_DONE_( \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_NAMESPACE_ASSERTION_TRAITS_NEW_NAME_PARSE( \
    BOOST_CONTRACT_EXT_PP_ASSERTION_TRAITS_SET_KIND_PARSE(namespace, \
        (decl BOOST_PP_NIL, BOOST_CONTRACT_EXT_PP_TRAITS_INIT) \
    ))))

// ASSERTION_TRAITS_KIND(traits) expands to `namespace` for this assertion.

#endif // #include guard
