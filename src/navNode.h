#ifndef NAVNODE_H
#define NAVNODE_H

#include <ostream>
#include <tuple>

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

#include "nodePath.h"
#include "lpoint3.h"

#include "src/navEdge.h"

class EXPORT_CLASS NavNode {
PUBLISHED:
// These methods are publicly accessible to Python and C++

    NavNode( LPoint3f pos, LVector3f normal = LVector3f::up(), float max_size = 99999 );
    ~NavNode() {};

    void set_pos( LPoint3f pos ) { this->pos = pos; }
    LPoint3f get_pos() { return this->pos; }

    float get_cost() const { return this->g + this->h; }
    float get_g() const { return this->g; }
    void set_h( float h ) { this->h = h; }
    void set_g( float g ) { this->g = g; }

    NavNode* get_parent() { return this->parent; }
    void set_parent( NavNode* parent ) { this->parent = parent; }

    LVector3f get_forward_dir() { return this->forward_dir; }
    void set_forward_dir( LVector3f f ) { this->forward_dir = f; }

    /* Denote that neighbor can be reached from this node
     *
     * Edge cost will be set to edge_cost_factor * edge_length.
     *
     * Note: This will also automatically add 'this' instance to 'neighbor' as an upstream neighbor */
    void add_downstream_neighbor( NavNode* neighbor, float edge_cost_factor = 1 );

    size_t num_downstream_neighbors() { return this->neighbor_edges_downstream.size(); }

    size_t num_upstream_neighbors() { return this->neighbor_edges_upstream.size(); }
    // Return neighbor node and the cost it takes to reach it
    //std::tuple<NavNode*, float> get_neighbor( size_t i );
    NavEdge* get_downstream_edge( size_t i );
    NavEdge* get_upstream_edge( size_t i );

    NavNode* get_downstream_neighbor( size_t i );
    NavNode* get_upstream_neighbor( size_t i );

    bool is_my_downstream_neighbor( NavNode* other );
    bool is_my_upstream_neighbor( NavNode* other );

    void set_open( bool open ) { this->open = open; }
    bool is_open() { return this->open; }

    std::string __repr__() const;

    /* Resets all values that were set during a search */
    void reset();

    friend std::ostream& operator<<(std::ostream& os, const NavNode& n);

    LVector3f get_normal() { return this->normal; }
    void set_normal( LVector3f normal ) { this->normal = normal; }

public:
// C++-only methods:
    void add_upstream_neighbor( NavNode* neighbor );

private:

    LPoint3f pos;
    LVector3f normal;
    LVector3f forward_dir;
    float size;
    float h;
    float g;

    bool open;

    NavNode* parent;
    //std::map<NavNode*, float> neighbors;
    std::vector<NavEdge> neighbor_edges_downstream;
    std::vector<NavEdge> neighbor_edges_upstream;
};

#endif
