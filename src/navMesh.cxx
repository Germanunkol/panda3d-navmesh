
#include "src/navMesh.h"
#include "src/a_star.h"

NavMesh::NavMesh()
{
}

NavNode* NavMesh::add_node( LVector3f pos )
{
    NavNode node( pos );
    this->nodes.push_back( node );
    // Return the added node:
    return &this->nodes.back();
}

void NavMesh::fill_from_geom()
{
}

NavPath NavMesh::find_path( LVector3f start_pos, LVector3f end_pos )
{
    NavNode start_node = find_nearest_node_at( start_pos );
    NavNode end_node = find_nearest_node_at( end_pos );
    return a_star::find_path( start_node, end_node );
}

NavNode NavMesh::find_nearest_node_at( LVector3f search_pos )
{
    // TODO! Replace this with KD-Tree search or similar
    float min_dist = 999999;
    NavNode closest = this->nodes[0];
    for( auto itr = this->nodes.begin(); itr != this->nodes.end(); itr++ )
    {
        float dist = (search_pos - itr->get_pos()).length();
        if( dist < min_dist )
        {
            closest = *itr;
        }
    }
    return closest;
}
