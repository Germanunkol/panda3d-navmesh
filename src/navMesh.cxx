#include <limits>
#include <unordered_set>

#include "src/navMesh.h"
#include "src/a_star.h"

NavMesh::NavMesh()
{
}

NavMesh::~NavMesh()
{
    for( auto it = this->nodes.begin(); it < this->nodes.end(); it ++ )
    {
        delete *it;
    }
}

NavNode* NavMesh::add_node( LVector3f pos )
{
    NavNode* node = new NavNode( pos );
    this->nodes.push_back( node );

    // Warning! If we ever add a node-remove function, we also need to remove the node from
    // the tree!
    this->node_searchtree.insert( pos, node );

    // Return the added node:
    return node;
}

void NavMesh::reset()
{
    std::cout << "Resetting all nodes. NOTE: Do this only for debugging purposes, it's unneccesarily slow!" << std::endl;
    for( auto it = this->nodes.begin(); it < this->nodes.end(); it ++ )
    {
        (*it)->reset();
    }
}

bool NavMesh::connectivity_check()
{
    /* Check if the graph is "strongly connected". This is the case if we can pick a node s and 
     * - all nodes are reachable from node s and
     * - s is reachable from all nodes. */
    std::cout << "Checking that all " << this->nodes.size() << " nodes are connected..." << std::endl;

    if( this->nodes.size() == 0 )
        return true;

    NavNode* start_node = this->nodes[0];
  
    // --------------------------- 
    // Start by checking if all nodes can be reached from the start node:
    std::unordered_set<NavNode*> open;
    std::unordered_set<NavNode*> visited;
    open.insert( start_node );

    while( open.size() > 0 )
    {
        auto first = open.begin();
        NavNode* current_node = *first;

        for( size_t i = 0; i < current_node->num_downstream_neighbors(); i ++ )
        {
            NavNode* neighbor = current_node->get_downstream_neighbor( i );
            // If the neighbor is neither in the visited set nor in the open set, add it to the open set:
            if( visited.find( neighbor) == visited.end() && open.find( neighbor ) == open.end() )
                open.insert( neighbor );
        }

        open.erase( current_node );
        visited.insert( current_node );
    }

    if( this->nodes.size() > visited.size() )
    {
        std::cout << "\tCheck failed! The following nodes could not be reached from node 0:" << std::endl;
        for( auto it = this->nodes.begin(); it != this->nodes.end(); it++ )
        {
            if( visited.find( *it ) == visited.end() )
                std::cout << "\t\t" << **it << std::endl;
        }
        return false;
    } else if ( this->nodes.size() < visited.size() ) {
        std::cout << "\tCheck failed! Something wrong, looks like some nodes were reached multiple times?"
                  << std::endl;
        return false;
    }

    // Check again in the other direction, i.e. iterating the reversed graph, to see if the start node can
    // be reached from all other nodes:
    open.clear();
    visited.clear();
    open.insert( start_node );

    while( open.size() > 0 )
    {
        auto first = open.begin();
        NavNode* current_node = *first;

        // This time, look at the _upstream_ neighbors!
        for( size_t i = 0; i < current_node->num_upstream_neighbors(); i ++ )
        {
            NavNode* neighbor = current_node->get_upstream_neighbor( i );
            // If the neighbor is neither in the visited set nor in the open set, add it to the open set:
            if( visited.find( neighbor) == visited.end() && open.find( neighbor ) == open.end() )
                open.insert( neighbor );
        }

        open.erase( current_node );
        visited.insert( current_node );
    }

    if( this->nodes.size() > visited.size() )
    {
        std::cout << "\tCheck failed! From the following nodes we cannot reach node 0:" << std::endl;
        for( auto it = this->nodes.begin(); it != this->nodes.end(); it++ )
        {
            if( visited.find( *it ) == visited.end() )
                std::cout << "\t\t" << **it << std::endl;
        }
        return false;
    } else if ( this->nodes.size() < visited.size() ) {
        std::cout << "\tCheck failed! Something wrong, looks like some nodes were reached multiple times?"
                  << std::endl;
        return false;
    }

    std::cout << "\tCheck successful, NavMesh is valid!" << std::endl;

    return true;
}

NavPath NavMesh::find_path( LVector3f start_pos, LVector3f end_pos, size_t max_search_length )
{
    //this->reset();
    NavNode* start_node = find_nearest_node_at( start_pos );
    NavNode* end_node = find_nearest_node_at( end_pos );
    return a_star::find_path( start_node, end_node, max_search_length );
}

NavNode* NavMesh::find_nearest_node_at( LVector3f search_pos )
{
    if( this->nodes.size() == 0 )
        return NULL;
    else
        return this->node_searchtree.search( search_pos );
}


