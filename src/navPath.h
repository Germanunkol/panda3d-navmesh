#ifndef NAVPATH_H
#define NAVPATH_H

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

#include "nodePath.h"
#include "lpoint3.h"

#include "src/navNode.h"
#include "src/navEdge.h"

class EXPORT_CLASS NavPath {
PUBLISHED:
// These methods are publicly accessible to Python and C++

    NavPath();
    ~NavPath() {};

    void add_node( NavNode node );
    NavNode get_node( unsigned int i );

    unsigned int get_length() { return this->nodes.size(); }

public:
// C++-only methods:

private:
    std::vector<NavNode> nodes;
};

#endif
