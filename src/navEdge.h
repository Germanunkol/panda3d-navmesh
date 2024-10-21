#ifndef NAVEDGE_H
#define NAVEDGE_H

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

#include "nodePath.h"
#include "lpoint3.h"

//#include "src/navNode.h"
class NavNode;

class EXPORT_CLASS NavEdge {
    /* Directed edge towards some target end node
     */
PUBLISHED:
// These methods are publicly accessible to Python and C++

    NavEdge( NavNode* end_node, float cost );
    ~NavEdge() {};

    float get_cost() { return this->cost; }
    NavNode* get_end_node() { return this->end_node; }

    /*LPoint3f get_pos() { return this->position; }
    void set_pos( LPoint3f position ) { this->position = position; }

    LVector3f get_normal() { return this->normal; }
    void set_normal( LVector3f normal ) { this->normal = normal; }*/

public:
// C++-only methods:

private:
    NavNode* end_node;
    float cost;
};

#endif
