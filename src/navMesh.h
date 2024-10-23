#ifndef NAVMESH_H
#define NAVMESH_H

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

#include "nodePath.h"
#include "lpoint3.h"

#include "src/navNode.h"
#include "src/navEdge.h"
#include "src/navPath.h"
#include "src/kdTree.h"

class EXPORT_CLASS NavMesh {
PUBLISHED:
// These methods are publicly accessible to Python and C++

    NavMesh();
    ~NavMesh();

    NavNode* add_node( LPoint3f pos, LVector3f normal = LVector3f::up() );

    void reset();

    //void fill_from_geom();    // Maybe TODO?
    
    /* Check that all nodes are connected to each other */
    bool connectivity_check();

    NavPath find_path(
            LPoint3f start_pos,
            LPoint3f end_pos,
            size_t max_search_length = std::numeric_limits<size_t>::max() );

    NavNode* find_closest_node( LPoint3f search_pos );

public:
// C++-only methods:

private:
    std::vector<NavNode*> nodes;

    KDTree<NavNode*> node_searchtree;
};

#endif
