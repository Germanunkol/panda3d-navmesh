#ifndef A_STAR_H
#define A_STAR_H

#include "src/navNode.h"
#include "src/navPath.h"

namespace a_star {

NavPath find_path( NavNode* start_node, NavNode* end_node );

};

#endif
