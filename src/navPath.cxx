
#include "src/navPath.h"

NavPath::NavPath()
{
}

void NavPath::add_node_back( NavNode node )
{
    this->nodes.push_back( node );

    // Calculate direction vectors which face along the path:
    if( this->nodes.size() > 0 )
    {
        size_t last_index = this->nodes.size() - 1;
        // Get the direction from the previous node to this new node:
        LVector3f forward = this->nodes[last_index].get_pos() - this->nodes[last_index-1].get_pos();
        // Set this as the "forward" direction for the previous node:
        this->nodes[last_index-1].set_forward_dir( forward );
        // Also set this direction for the newly added node, because it doesn't have another
        // node infront of it:
        this->nodes[last_index].set_forward_dir( forward );
    }
}

void NavPath::add_node_front( NavNode node )
{
    this->nodes.push_front( node );
    if( this->nodes.size() > 1 )
    {
        // Calculate the direction from the previous node to this node:
        LVector3f forward = this->nodes[1].get_pos() - this->nodes[0].get_pos();
        // Set this direction as the forward direction for the new node:
        this->nodes[0].set_forward_dir( forward );
    }
}

NavNode* NavPath::get_node( size_t i )
{
    if( i >= this->nodes.size() )
        throw std::invalid_argument( "Index error in NavPath::get_node(). Requested node past end of path!" );
    return &this->nodes[i];
}

NavNode* NavPath::operator[]( size_t i )
{
    if( i >= this->nodes.size() )
        throw std::invalid_argument( "Index error in NavPath::operator[]. Requested node past end of path!" );
    return &this->nodes[i];
}

void NavPath::raise_path( float height )
{
    for( auto it = this->nodes.begin(); it != this->nodes.end(); it++ )
    {
        LVector3f new_pos = it->get_pos() + it->get_normal() * height;
        it->set_pos( new_pos );
    }
}

std::string NavPath::__repr__() const
{
    std::stringstream sstr;
    sstr << "[Path: (length: " << this->nodes.size() << ")" << std::endl;
    for( auto it = this->nodes.begin(); it != this->nodes.end(); it++ )
        sstr << "\t" << *it << std::endl;

    return sstr.str();
}
