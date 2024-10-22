
set(P3NAVMESH_HEADERS
  src/navMesh.h
  src/navNode.h
  src/navEdge.h
  src/navPath.h
  src/a_star.h
  src/openSet.h
  src/kdTree.h
)

set(P3NAVMESH_SOURCES
  src/navMesh.cxx
  src/navNode.cxx
  src/navEdge.cxx
  src/navPath.cxx
  src/a_star.cxx
)

composite_sources(p3navmesh P3NAVMESH_SOURCES)
add_library(p3navmesh ${P3NAVMESH_HEADERS} ${P3NAVMESH_SOURCES})
set_target_properties(p3navmesh PROPERTIES DEFINE_SYMBOL BUILDING_NAVMESH)
target_link_libraries(p3navmesh panda)
  #target_link_libraries(p3navmesh panda
  #  PKG::OPENCV PKG::ARTOOLKIT)
set_target_properties(p3navmesh PROPERTIES CXX_EXCEPTIONS ON)
target_interrogate(p3navmesh ALL)

install(TARGETS p3navmesh
    EXPORT Navmesh COMPONENT Navmesh
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/panda3d
  ARCHIVE COMPONENT NavmeshDevel)
install(FILES ${P3NAVMESH_HEADERS} COMPONENT NavmeshDevel DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/panda3d)

export_targets(Navmesh COMPONENT NavmeshDevel)

