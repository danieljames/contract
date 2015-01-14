
#ifndef BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VIRT_SPECIFIERS_HPP_
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VIRT_SPECIFIERS_HPP_

#include <boost/contract/ext_/preprocessor/traits/func/aux_/index.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/keyword_comb.hpp>
#include <boost/contract/ext_/preprocessor/traits/adt.hpp>
#include <boost/contract/ext_/preprocessor/keyword/final.hpp>
#include <boost/contract/ext_/preprocessor/keyword/override.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VIRT_SPECIFIERS_( \
        sign_virt, traits) \
    ( \
        BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST(sign_virt) \
    , \
        BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
            BOOST_CONTRACT_EXT_PP_TRAITS_PUSH_BACK( \
                traits, \
                BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(2, 0, \
                        BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_virt)), \
                    final \
                ) \
                BOOST_PP_EMPTY \
            ), \
            BOOST_PP_EXPR_IIF(BOOST_PP_TUPLE_ELEM(2, 1, \
                    BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_virt)), \
                override \
            ) \
            BOOST_PP_EMPTY \
        ) \
    )

/* PUBLIC */

#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VIRT_SPECIFIERS_PARSE(sign_traits) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VIRT_SPECIFIERS_( \
        BOOST_CONTRACT_EXT_PP_TRAITS_AUX_KEYWORD2_COMB_PARSE( \
            BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_FIRST(sign_traits), \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_FINAL_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_FINAL_REMOVE_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_IS_OVERRIDE_FRONT, \
            BOOST_CONTRACT_EXT_PP_KEYWORD_OVERRIDE_REMOVE_FRONT \
        ), \
        BOOST_CONTRACT_EXT_PP_SIGN_TRAITS_SECOND(sign_traits) \
    )

// Expand to `final | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_FINAL(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_FINAL_INDEX, traits)()

// Expand to `override | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_OVERRIDE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_AUX_OVERRIDE_INDEX, traits)()

#endif // #include guard
