#ifndef NAVMESH_H
#define NAVMESH_H

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

#include "nodePath.h"
#include "lpoint3.h"

#include "src/navNode.h"
#include "src/navEdge.h"
#include "src/navPath.h"

class EXPORT_CLASS NavMesh {
PUBLISHED:
// These methods are publicly accessible to Python and C++

    NavMesh();
    ~NavMesh();

    NavNode* add_node( LVector3f pos );

    void reset();

    //void fill_from_geom();    // Maybe TODO?
    
    /* Check that all nodes are connected to each other */
    bool connectivity_check();

    NavPath find_path(
            LVector3f start_pos,
            LVector3f end_pos,
            size_t max_search_length = std::numeric_limits<size_t>::infinity() );

    NavNode* find_nearest_node_at( LVector3f search_pos );


    /*LPoint3f get_pos() { return this->position; }
    void set_pos( LPoint3f position ) { this->position = position; }

    LVector3f get_normal() { return this->normal; }
    void set_normal( LVector3f normal ) { this->normal = normal; }*/

public:
// C++-only methods:

private:
    std::vector<NavNode*> nodes;
};

#endif
