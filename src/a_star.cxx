
#include <vector>
//#include <queue>
#include <algorithm>
#include <unordered_set>

#include "src/a_star.h"
#include "src/navEdge.h"
#include "src/openSet.h"

//#define verbose

namespace a_star {

// This function should contruct a min-heap:
bool cmp(const NavNode& a, const NavNode& b)
{
    return a.get_cost() > b.get_cost();
}

class NodeCostComparator
{
public:
    bool operator() (const NavNode* a, const NavNode* b)
    {
        return a->get_cost() > b->get_cost();
    }
};

NavPath backtrack( NavNode* current_node )
{
    NavPath path;
    while( current_node != NULL )
    {
        path.add_node_front( *current_node );
        current_node = current_node->get_parent();
    }
    return path;
}

NavPath find_path( NavNode* start_node, NavNode* end_node )
{
    OpenSet<NavNode*, std::vector<NavNode*>, NodeCostComparator> open_set;
    open_set.push( start_node );
    start_node->set_open( true );
    start_node->set_g( 0 );

    #ifdef verbose
        std::cout << "Finding path" << std::endl;
        std::cout << "\tfrom: " << *start_node << std::endl;
        std::cout << "\tto: " << *end_node << std::endl;
    #endif

    // Probably a NOP, but for clarity:
    //std::make_heap( open_set.begin(), open_set.end() );
    
    std::unordered_set<NavNode*> closed;

    unsigned int i = 0;
    while( open_set.size() > 0 )
    {
        i += 1;
        #ifdef verbose
            std::cout << "Iteration: " << i << std::endl;
        #endif

        // Get the node with the minimum cost and remove it from the open set:
        NavNode* current_node = open_set.top();
        open_set.pop();

        #ifdef verbose
            std::cout << "Current node: " << *current_node << std::endl;
        #endif

        current_node->set_open( false );
        closed.insert( current_node );

        if( current_node == end_node )
        {
            #ifdef verbose
                std::cout << "Found end node!" << std::endl;
            #endif
            return backtrack( current_node );
        }

        for( size_t i = 0; i < current_node->num_downstream_neighbors(); i ++ )
        {
            NavEdge* new_edge = current_node->get_downstream_edge( i );
            NavNode* new_node = new_edge->get_end_node();
            #ifdef verbose
                std::cout << "\tChecking node: " << *new_node << std::endl;
            #endif
            // Check if we already worked through this node:
            if( closed.find( new_node ) == closed.end() )
            {
                // If not, conider adding it to the open set!
                if( !new_node->is_open() )
                {
                    float h = (end_node->get_pos() - new_node->get_pos()).length();
                    new_node->set_h( h );
                    new_node->set_parent( current_node );
                    float new_g = current_node->get_g() + new_edge->get_cost();
                    new_node->set_g( new_g );
                   
                    // Add to open list: 
                    open_set.push( new_node );
                    new_node->set_open( true );
                    #ifdef verbose
                        std::cout << "\tNode is not open. Adding to open set" << std::endl;
                    #endif
                } else {
                    float new_g = current_node->get_g() + new_edge->get_cost();
                    #ifdef verbose
                        std::cout << "\tNew g: " << new_g << std::endl;
                    #endif
                    if( new_node->get_g() > new_g )
                    {
                        new_node->set_g( new_g );
                        new_node->set_parent( current_node );
                        // Because we changed the g (and thus the cost), we must re-sort:
                        open_set.resort();
                    }
                }
            } 
        }
    }

    // TODO: clean up is_open for all nodes still in open set. Otherwise, let OpenSet handle it upon
    // destruction
    //
    // TODO: clear all g values and all h values of visited nodes!
    
    return NavPath();
}

};
