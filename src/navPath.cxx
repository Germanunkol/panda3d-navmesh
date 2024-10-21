
#include "src/navPath.h"

NavPath::NavPath()
{
}

void NavPath::add_node_back( NavNode node )
{
    this->nodes.push_back( node );
}

void NavPath::add_node_front( NavNode node )
{
    this->nodes.push_front( node );
}

NavNode NavPath::get_node( unsigned int i )
{
    return this->nodes[i];
}

