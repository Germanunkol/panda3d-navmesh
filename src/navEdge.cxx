
#include "src/navEdge.h"

NavEdge::NavEdge( NavNode* start_node, NavNode* end_node, float cost_factor )
    : start_node( start_node )
    , end_node( end_node )
{
    this->cost = (end_node->get_pos() - start_node->get_pos()).length() * cost_factor;
}
