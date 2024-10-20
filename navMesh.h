#ifndef NAVMESH_H
#define NAVMESH_H

// dtoolbase.h defines the PUBLISHED macro if the CPPPARSER macro is defined
#include "dtoolbase.h"

#include "nodePath.h"
#include "lpoint3.h"

class EXPORT_CLASS NavMesh {
PUBLISHED:
  // These methods are publicly accessible to Python and C++

  NavMesh();
  ~NavMesh() {};

  /*LPoint3f get_pos() { return this->position; }
  void set_pos( LPoint3f position ) { this->position = position; }

  LVector3f get_normal() { return this->normal; }
  void set_normal( LVector3f normal ) { this->normal = normal; }*/

public:
  // C++-only methods:
  
private:
  LPoint3f position;
  LVector3f normal;
};

#endif
