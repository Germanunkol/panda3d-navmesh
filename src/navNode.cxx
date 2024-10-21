
#include <limits>
#include <sstream>

#include "src/navNode.h"

NavNode::NavNode( LVector3f pos, float size )
    : pos( pos )
    , size( size )
    , h( std::numeric_limits<float>::infinity() )
    , g( std::numeric_limits<float>::infinity() )
    , parent( NULL )
    , open( false )
{
}


std::string NavNode::__repr__() const
{
    std::stringstream sstr;
    sstr << "[NavNode: " <<
              "pos: (" << this->pos << ")" <<
              ", size: " << this->size <<
              ", h: " << this->h <<
              ", g: " << this->g <<
              ", neighbors ds: " << this->neighbor_edges_upstream.size() <<
              ", neighbors us: " << this->neighbor_edges_upstream.size() <<
              "]";
    return sstr.str();
}

std::ostream& operator<<(std::ostream& os, const NavNode& n)
{
    return os << "[NavNode: " <<
              "pos: (" << n.pos << ")" <<
              ", size: " << n.size <<
              ", h: " << n.h <<
              ", g: " << n.g <<
              ", neighbors: " << n.neighbor_edges_upstream.size() <<
              ", neighbors us: " << n.neighbor_edges_upstream.size() <<
              "]";
}

void NavNode::add_downstream_neighbor( NavNode* neighbor, float edge_cost_factor )
{
    // First, check if this is already our neighbor:
    if( !this->is_my_downstream_neighbor( neighbor ) )
    {
        // If not, add as neighbor:
        float cost = (neighbor->get_pos() - this->pos).length() * edge_cost_factor;
        this->neighbor_edges_downstream.push_back( NavEdge( neighbor, cost ) );
    }

    // Also let the other node know that we have a connection to it:
    neighbor->add_upstream_neighbor( this );
}

void NavNode::add_upstream_neighbor( NavNode* neighbor )
{
    // First, check if this is already our (upstream) neighbor:
    if( !this->is_my_upstream_neighbor( neighbor ) )
        this->neighbor_edges_upstream.push_back( NavEdge( neighbor, std::numeric_limits<float>::infinity() ) );
}

NavEdge* NavNode::get_downstream_edge( size_t i )
{
    return &this->neighbor_edges_downstream[i];
}
NavEdge* NavNode::get_upstream_edge( size_t i )
{
    return &this->neighbor_edges_upstream[i];
}

NavNode* NavNode::get_downstream_neighbor( size_t i )
{
    return this->neighbor_edges_downstream[i].get_end_node();
}
NavNode* NavNode::get_upstream_neighbor( size_t i )
{
    return this->neighbor_edges_upstream[i].get_end_node();
}

bool NavNode::is_my_downstream_neighbor( NavNode* other )
{
    for( auto it = neighbor_edges_downstream.begin(); it != neighbor_edges_downstream.end(); it ++ )
        if( it->get_end_node() == other )
            return true;
    return false;
}

bool NavNode::is_my_upstream_neighbor( NavNode* other )
{
    for( auto it = neighbor_edges_upstream.begin(); it != neighbor_edges_upstream.end(); it ++ )
        if( it->get_end_node() == other )
            return true;
    return false;
}



