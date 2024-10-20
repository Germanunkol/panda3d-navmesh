
#include <vector>
#include <queue>
#include <algorithm>
#include "src/a_star.h"

#define verbose

namespace a_star {

// This function should contruct a min-heap:
bool cmp(const NavNode& a, const NavNode& b)
{
    return a.get_cost() > b.get_cost();
}

class NodeCostComparator
{
public:
    bool operator() (const NavNode& a, const NavNode& b)
    {
        return a.get_cost() > b.get_cost();
    }
};

NavPath find_path( NavNode start_node, NavNode end_node )
{
    std::priority_queue<NavNode, std::vector<NavNode>, NodeCostComparator> open_set;
    open_set.push( start_node );

    // Probably a NOP, but for clarity:
    //std::make_heap( open_set.begin(), open_set.end() );
    
    std::vector<NavNode> closed;

    unsigned int i = 0;
    while( open_set.size() > 0 )
    {
        i += 1;
        #ifdef verbose
            std::cout << "Iteration: " << i << std::endl;
        #endif

        // Retrieve the minimum node. Note: pop_heap first moves the first node to the back
        // of the vector, then re-sorts the rest of the heap.
        //std::pop_heap( open_set.begin(), open_set.end() );
        //NavNode current_node = open_set.pop_back();
        NavNode current_node = open_set.top();
        open_set.pop();

        closed.push_back( current_node );
    }
    
    return NavPath();
}

};
