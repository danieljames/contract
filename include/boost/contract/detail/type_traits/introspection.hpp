
#ifndef BOOST_CONTRACT_DETAIL_INTROSPECTION_HPP_
#define BOOST_CONTRACT_DETAIL_INTROSPECTION_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/name.hpp>
#include <boost/function_types/member_function_pointer.hpp>
#include <boost/function_types/function_pointer.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/rem.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// NOTE: Unfortunately, it is not possible to use Boost.TTI because it not
// always works on MSVC (e.g., when the introspecting meta-function is invoked
// multiple times, MSVC 2010 gives an internal compiler error). This is a
// simpler introspecting implementation that seems to work better on MSVC.

/* PRIVATE */

#define BOOST_CONTRACT_DETAIL_INTROSPECTION_END_(tparam) \
        template<typename> \
        static boost::contract::detail::introspection::no& check(...); \
    public: \
        static bool const value = sizeof(check<tparam>(0)) == \
                sizeof(boost::contract::detail::introspection::yes); \
        typedef boost::mpl::bool_<value> type;

#define BOOST_CONTRACT_DETAIL_INTROSPECTION_HAS_MEMBER_FUNCTION_(is_static, \
        trait, func_name) \
    template< \
        typename BOOST_CONTRACT_DETAIL_NAME1(T), \
        typename BOOST_CONTRACT_DETAIL_NAME1(R), \
        class BOOST_CONTRACT_DETAIL_NAME1(P), \
        class BOOST_CONTRACT_DETAIL_NAME1(G) = boost::function_types::null_tag \
    > \
    class trait { \
        template<class BOOST_CONTRACT_DETAIL_NAME1(C)> \
        static boost::contract::detail::introspection::yes& check( \
            boost::contract::detail::introspection::check_function< \
                typename \
                    BOOST_PP_IIF(is_static, \
                        boost::function_types::function_pointer \
                    , \
                        boost::function_types::member_function_pointer \
                    ) \
                < \
                    typename boost::mpl::push_front< \
                        BOOST_PP_IIF(is_static, \
                            BOOST_CONTRACT_DETAIL_NAME1(P) \
                            BOOST_PP_TUPLE_EAT(2) \
                        , \
                            BOOST_PP_TUPLE_REM(2) \
                        )( \
                            typename boost::mpl::push_front< \
                                BOOST_CONTRACT_DETAIL_NAME1(P), \
                                BOOST_CONTRACT_DETAIL_NAME1(C) \
                            >::type \
                        ) \
                        , BOOST_CONTRACT_DETAIL_NAME1(R) \
                    >::type, \
                    BOOST_CONTRACT_DETAIL_NAME1(G) \
                >::type, \
                &BOOST_CONTRACT_DETAIL_NAME1(C)::func_name \
            >* \
        ); \
        BOOST_CONTRACT_DETAIL_INTROSPECTION_END_( \
                BOOST_CONTRACT_DETAIL_NAME1(T)) \
    };

/* PUBLIC */

#define BOOST_CONTRACT_DETAIL_INTROSPECTION_HAS_TYPE(trait, type_name)\
    template<typename BOOST_CONTRACT_DETAIL_NAME1(T)> \
    class trait { \
        template<class BOOST_CONTRACT_DETAIL_NAME1(C)> \
        static boost::contract::detail::introspection::yes& check( \
                typename BOOST_CONTRACT_DETAIL_NAME1(C)::type_name*); \
        BOOST_CONTRACT_DETAIL_INTROSPECTION_END_( \
                BOOST_CONTRACT_DETAIL_NAME1(T)) \
    };

#define BOOST_CONTRACT_DETAIL_INTROSPECTION_HAS_MEMBER_FUNCTION( \
        trait, func_name) \
    BOOST_CONTRACT_DETAIL_INTROSPECTION_HAS_MEMBER_FUNCTION_( \
            /* is_static = */ 0, trait, func_name)

#define BOOST_CONTRACT_DETAIL_INTROSPECTION_HAS_STATIC_MEMBER_FUNCTION(trait, \
        func_name) \
    BOOST_CONTRACT_DETAIL_INTROSPECTION_HAS_MEMBER_FUNCTION_( \
            /* is_static = */ 1, trait, func_name)
        
/* CODE */

namespace boost { namespace contract { namespace detail {
        namespace introspection {

typedef class {} yes;
typedef yes no[2];

template<typename F, F> class check_function;

} } } } // namespace

#endif // #include guard
