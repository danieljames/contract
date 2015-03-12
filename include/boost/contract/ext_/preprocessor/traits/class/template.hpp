
#ifndef BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_HPP_
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_HPP_

#include <boost/contract/ext_/preprocessor/traits/param.hpp>
#include <boost/contract/ext_/preprocessor/traits/aux_/class_index.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/keyword_list.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/list.hpp>
#include <boost/contract/ext_/preprocessor/traits/utility/traits.hpp>
#include <boost/contract/ext_/preprocessor/keyword/template.hpp>
#include <boost/contract/ext_/preprocessor/keyword/default.hpp>

/* PUBLIC */

// Expand to `template | EMPTY()`.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
            BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_TEMPLATE_INDEX, traits)()

// Expand to EMPTY() if no class template parameters, otherwise expand to
// pp-seq of param. traits (each pp-seq elem. to be inspected via PARAM_TRAITS).
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_PARAMS(traits) \
    BOOST_CONTRACT_EXT_PP_TRAITS_ELEM( \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_AUX_TEMPLATE_PARAMS_INDEX, \
        traits \
    )()

#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_PARSE_D(d, decl_traits) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_LIST_TRAITS_PARSE_D(d, \
        decl_traits, \
        template, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_IS_TEMPLATE_FRONT, \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TEMPLATE_REMOVE_FRONT, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_ \
    )

/* PRIVATE */

// Precondition: decl = `(,,,) ...` from `template(,,,) ...` originally in decl.
// This macro will also parse `(,,,)` into a pp-seq of template param traits.
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_(d, decl) \
    BOOST_CONTRACT_EXT_PP_LIST_TRAITS_PARSE_D_1(d, \
        decl, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_PARAM_PARSE_, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_IS_DEFAULT_, \
        BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_REPLACE_DEFAULT_PARSE_ \
    )
    
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_PARAM_PARSE_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_TEMPLATE_PARAM_TRAITS_PARSE_D(d, decl)
                    
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_IS_DEFAULT_(d, l, decl) \
    BOOST_CONTRACT_EXT_PP_KEYWORD_IS_DEFAULT_FRONT(decl)
                    
#define BOOST_CONTRACT_EXT_PP_CLASS_TRAITS_TEMPLATE_REPLACE_DEFAULT_PARSE_( \
        d, l, decl) \
    BOOST_CONTRACT_EXT_PP_PARAM_TRAITS_REPLACE_DEFAULT_PARSE_D(d, decl)

#endif // #include guard
