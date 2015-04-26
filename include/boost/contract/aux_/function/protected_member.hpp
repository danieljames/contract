
#ifndef BOOST_CONTRACT_AUX_FUNCTION_PROTECTED_MEMBER_HPP_
#define BOOST_CONTRACT_AUX_FUNCTION_PROTECTED_MEMBER_HPP_

#include <boost/contract/aux_/function/free_function.hpp>

namespace boost { namespace contract { namespace aux { namespace function {

// Not public members (i.e., protected members) are allowed to fail class
// invariants (so no inv) and they do not participate in virtual function
// polymorphism according to substitution principle (so no subcontracting).
// Therefore, their contracts behave like contracts of free functions.
typedef boost::contract::aux::function::free_function protected_member;

} } } } // namespace

#endif // #include guard
