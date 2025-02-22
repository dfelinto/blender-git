# SPDX-License-Identifier: GPL-2.0-or-later
# Copyright 2006 Blender Foundation. All rights reserved.

set(INC
  .
  ../blenkernel
  ../blenlib
  ../blentranslation
  ../functions
  ../makesdna
  ../makesrna
  ../../../intern/guardedalloc
  ${CMAKE_BINARY_DIR}/source/blender/makesdna/intern
)

set(SRC
  intern/mesh_merge_by_distance.cc
  intern/mesh_to_curve_convert.cc
  intern/point_merge_by_distance.cc
  intern/realize_instances.cc

  GEO_mesh_merge_by_distance.hh
  GEO_mesh_to_curve.hh
  GEO_point_merge_by_distance.hh
  GEO_realize_instances.hh
)

set(LIB
  bf_blenkernel
  bf_blenlib
)

if(WITH_TBB)
  add_definitions(-DWITH_TBB)

  list(APPEND INC_SYS
    ${TBB_INCLUDE_DIRS}
  )

  list(APPEND LIB
    ${TBB_LIBRARIES}
  )
endif()

blender_add_lib(bf_geometry "${SRC}" "${INC}" "${INC_SYS}" "${LIB}")
