
// Copyright (C) 2008-2017 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Test all derived and base classes without exit invariants.

#define BOOST_CONTRACT_TEST_NO_A_INV
#define BOOST_CONTRACT_TEST_NO_B_INV
#define BOOST_CONTRACT_TEST_NO_C_INV
#include "decl.hpp"

#include <boost/preprocessor/control/iif.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok;
    ok.str(""); ok // Test nothing fails.
        #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
            // No invariants.
            << "c::static_inv" << std::endl
            << "b::static_inv" << std::endl
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            << "c::f::pre" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_OLDS
            << "c::f::old" << std::endl
            << "b::f::old" << std::endl
            << "a::f::old" << std::endl
        #endif
        << "a::f::body" << std::endl
        #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
            << "c::static_inv" << std::endl
            << "b::static_inv" << std::endl
            << "a::static_inv" << std::endl
        #endif
        #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
            << "c::f::old" << std::endl
            << "c::f::post" << std::endl
            << "b::f::old" << std::endl
            << "b::f::post" << std::endl
            << "a::f::post" << std::endl
        #endif
    ;
    
    struct err {};
    boost::contract::set_exit_invariant_failure(
            [] (boost::contract::from) { throw err(); });

    a aa;

    #ifdef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
        #define BOOST_CONTRACT_TEST_entry_inv 0
    #else
        #define BOOST_CONTRACT_TEST_entry_inv 1
    #endif
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_entry_inv, true, false);
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));

    a_exit_inv = false;
    b_exit_inv = true;
    c_exit_inv = true;
    a_entering_inv = b_entering_inv = c_entering_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_entry_inv, true, false);
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_exit_inv = true;
    b_exit_inv = false;
    a_entering_inv = b_entering_inv = c_entering_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_entry_inv, true, false);
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = false;
    a_entering_inv = b_entering_inv = c_entering_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_entry_inv, true, false);
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));
    
    a_exit_inv = false;
    b_exit_inv = false;
    c_exit_inv = false;
    a_entering_inv = b_entering_inv = c_entering_inv =
            BOOST_PP_IIF(BOOST_CONTRACT_TEST_entry_inv, true, false);
    out.str("");
    aa.f();
    BOOST_TEST(out.eq(ok.str()));

    #undef BOOST_CONTRACT_TEST_entry_inv
    return boost::report_errors();
}

