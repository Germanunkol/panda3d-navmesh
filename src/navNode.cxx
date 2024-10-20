
#include "src/navNode.h"

NavNode::NavNode( LVector3f pos, float size )
    : pos( pos )
    , size( size )
    , h( 0 )
    , g( 0 )
{
}
