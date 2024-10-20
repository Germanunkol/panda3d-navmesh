
#include "src/navPath.h"

NavPath::NavPath()
{
}

void NavPath::add_node( NavNode node )
{
    this->nodes.push_back( node );
}

NavNode NavPath::get_node( unsigned int i )
{
    return this->nodes[i];
}

