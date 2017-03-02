
#include <boost/contract.hpp>
#include <vector>
#include <algorithm>
#include <limits>

int main() {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    //[loop
    int total = 0;
    for(std::vector<int>::const_iterator i = v.begin(); i != v.end(); ++i) {
        // Contract for a for-loop (same for while- and all other loops).
        boost::contract::old_ptr<int> old_total = BOOST_CONTRACT_OLD(total);
        boost::contract::check c = boost::contract::function()
            .precondition([&] {
                BOOST_CONTRACT_ASSERT(
                        total + *i <= std::numeric_limits<int>::max());
            })
            .postcondition([&] {
                BOOST_CONTRACT_ASSERT(total == *old_total + *i);
            })
        ;

        total += *i; // For-loop body.
    }
    //]

    assert(total == 6);
    return 0;
}
