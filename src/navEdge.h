#ifndef NAVEDGE_H
#define NAVEDGE_H

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

#include "nodePath.h"
#include "lpoint3.h"

#include "src/navNode.h"

class EXPORT_CLASS NavEdge {
PUBLISHED:
// These methods are publicly accessible to Python and C++

    NavEdge( NavNode* start_node, NavNode* end_node, float cost_factor = 1 );
    ~NavEdge() {};

    float get_cost() { return this->cost; }

    /*LPoint3f get_pos() { return this->position; }
    void set_pos( LPoint3f position ) { this->position = position; }

    LVector3f get_normal() { return this->normal; }
    void set_normal( LVector3f normal ) { this->normal = normal; }*/

public:
// C++-only methods:

private:
    NavNode* start_node;
    NavNode* end_node;
    float cost;
};

#endif
