#ifndef NAVNODE_H
#define NAVNODE_H

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

#include "nodePath.h"
#include "lpoint3.h"

class EXPORT_CLASS NavNode {
PUBLISHED:
// These methods are publicly accessible to Python and C++

    NavNode( LVector3f pos, float max_size = 99999 );
    ~NavNode() {};

    LVector3f get_pos() { return this->pos; }

    float get_cost() const { return this->g + this->h; }
    void set_h( float h ) { this->h = h; }
    void set_g( float g ) { this->g = g; }

    /*LPoint3f get_pos() { return this->position; }
    void set_pos( LPoint3f position ) { this->position = position; }

    LVector3f get_normal() { return this->normal; }
    void set_normal( LVector3f normal ) { this->normal = normal; }*/

public:
// C++-only methods:

private:
    LVector3f pos;
    float size;
    float h;
    float g;
};

#endif
