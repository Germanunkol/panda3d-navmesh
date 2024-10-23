#ifndef NAVPATH_H
#define NAVPATH_H

#include <queue>

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

    void add_node_front( NavNode node );
    void add_node_back( NavNode node );
    NavNode* get_node( size_t i );
    //NavNode* get_node_cleaned( size_t i );

    unsigned int get_length() { return this->nodes.size(); }

    NavNode* operator[](size_t);

    void raise_path( float height );

    std::string __repr__() const;

    //void smooth_path();

public:
// C++-only methods:


private:
    std::deque<NavNode> nodes;
};

#endif
