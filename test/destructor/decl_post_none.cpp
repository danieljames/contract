
// Test all derived and base classes without postconditions.

#define BOOST_CONTRACT_AUX_TEST_NO_A_POST
#define BOOST_CONTRACT_AUX_TEST_NO_B_POST
#define BOOST_CONTRACT_AUX_TEST_NO_C_POST
#include "decl.hpp"

#include <boost/detail/lightweight_test.hpp>
#include <sstream>

int main() {
    std::ostringstream ok; ok // Test nothing fails.
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "a::static_inv" << std::endl
            << "a::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "a::dtor::old" << std::endl
        #endif
        << "a::dtor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "a::static_inv" << std::endl
        #endif

        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "b::static_inv" << std::endl
            << "b::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "b::dtor::old" << std::endl
        #endif
        << "b::dtor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "b::static_inv" << std::endl
        #endif
            
        #if BOOST_CONTRACT_ENTRY_INVARIANTS
            << "c::static_inv" << std::endl
            << "c::inv" << std::endl
        #endif
        #if BOOST_CONTRACT_POSTCONDITIONS
            << "c::dtor::old" << std::endl
        #endif
        << "c::dtor::body" << std::endl
        #if BOOST_CONTRACT_EXIT_INVARIANTS
            << "c::static_inv" << std::endl
        #endif
    ;
    
    a_post = true;
    b_post = true;
    c_post = true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = false;
    b_post = true;
    c_post = true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = true;
    b_post = false;
    c_post = true;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = true;
    b_post = true;
    c_post = false;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));
    
    a_post = false;
    b_post = false;
    c_post = false;
    {
        a aa;
        out.str("");
    }
    BOOST_TEST(out.eq(ok.str()));

    return boost::report_errors();
}

