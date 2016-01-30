
// Test only derived and grandparent classes (ends) with exit invariants.

#undef BOOST_CONTRACT_TEST_NO_A_INV
#define BOOST_CONTRACT_TEST_NO_B_INV
#undef BOOST_CONTRACT_TEST_NO_C_INV
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>
#include <string>
            
std::string ok_c() {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_PRECONDITIONS
            << "a::ctor::pre" << std::endl
            << "b::ctor::pre" << std::endl
            << "c::ctor::pre" << std::endl
        #endif
        
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::ctor::old" << std::endl
        #endif
        << "c::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl // This can fail.
        #endif
    ;
    return ok.str();
}

std::string ok_b() {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::ctor::post" << std::endl
        #endif
        
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::ctor::old" << std::endl
        #endif
        << "b::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
            // No failure here.
        #endif
    ;
    return ok.str();
}

std::string ok_a() {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::ctor::post" << std::endl
        #endif
            
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::ctor::old" << std::endl
        #endif
        << "a::ctor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl // This can fail.
        #endif
    ;
    return ok.str();
}

std::string ok_end() {
    std::ostringstream ok; ok
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::ctor::post" << std::endl
        #endif
    ;
    return ok.str();
}

int main() {
    std::ostringstream ok;
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = true;
    {
        out.str("");
        a aa;
        ok.str(""); ok // Test no failure.
            << ok_c()
            << ok_b()
            << ok_a()
            << ok_end()
        ;
        BOOST_TEST(out.eq(ok.str()));
    }
    
    struct err {};
    boost::contract::set_exit_invariant_failure(
            [] (boost::contract::from) { throw err(); });

    a_exit_inv = false;
    b_exit_inv = true;
    c_exit_inv = true;
    try {
        out.str("");
        a aa;
        #if BOOST_CONTRACT_EXIT_INVARIANTS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok.str(""); ok
            << ok_c()
            << ok_b()
            << ok_a() // Test a::inv failed.
            #if !BOOST_CONTRACT_EXIT_INVARIANTS
                << ok_end()
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    a_exit_inv = true;
    b_exit_inv = false;
    c_exit_inv = true;
    try {
        out.str("");
        a aa;
        ok.str(""); ok
            << ok_c()
            << ok_b() // Test no b::inv so no failure.
            << ok_a()
            << ok_end()
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_inv = true;
    b_exit_inv = true;
    c_exit_inv = false;
    try {
        out.str("");
        a aa;
        #if BOOST_CONTRACT_EXIT_INVARIANTS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok.str(""); ok
            << ok_c() // Test c::inv failed.
            #if !BOOST_CONTRACT_EXIT_INVARIANTS
                << ok_b()
                << ok_a()
                << ok_end()
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }
    
    a_exit_inv = false;
    b_exit_inv = false;
    c_exit_inv = false;
    try {
        out.str("");
        a aa;
        #if BOOST_CONTRACT_EXIT_INVARIANTS
                BOOST_TEST(false);
            } catch(err const&) {
        #endif
        ok.str(""); ok
            << ok_c() // Test c::inv failed.
            #if !BOOST_CONTRACT_EXIT_INVARIANTS
                << ok_b()
                << ok_a()
                << ok_end()
            #endif
        ;
        BOOST_TEST(out.eq(ok.str()));
    } catch(...) { BOOST_TEST(false); }

    return boost::report_errors();
}
