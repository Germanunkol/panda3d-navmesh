
#include "navMesh.h"

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
