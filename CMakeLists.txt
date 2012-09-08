cmake_minimum_required (VERSION 2.6)
project (libfall4c)

set (CMAKE_BUILD_TYPE Debug)

# The version number.
set (fall4c_VERSION_MAJOR 1)
set (fall4c_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
    "${PROJECT_SOURCE_DIR}/fall4c_config.h.in"
    "${PROJECT_BINARY_DIR}/fall4c_config.h"
    )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/inc")

# add the executable
add_library(
    fall4c
    src/file.c
    src/string_ext.c
    src/file_browse.c
    src/data/dictionnary.c
    src/data/list.c
    src/data/queue.c
    src/data/stack.c
    # src/data/dictionnary_example.c
    # src/data/tree_avl.c
    # src/data/tree_common.c
    # src/data/tree_binary_mod.c
    # src/data/tree_redblack.c
    # src/data/tree_binary.c
    # src/data/tree_sparse.c
    # src/reed_solomon.c
    # src/collision.c
    # src/pathfinding.c
    src/data/array_manipulation.c
    src/data/array_associative.c
    src/graph.c
    src/math/bases.c
    src/math/math_probability.c
    src/math/interpolation.c
    src/math/vector_space.c
    src/math/math_ext.c
    src/math/dl.c
    src/math/math_sequence.c
    src/math/math_matrix.c
    src/math/math_trigonometry.c
    src/math/math_basic.c
    src/math/math_complex_numbers.c
    src/math/geometry_space.c
    src/util/errors.c
    src/util/debug.c
    src/ctype_extended.c
    )

install (TARGETS fall4c DESTINATION lib)
file (
    COPY ${PROJECT_SOURCE_DIR}/inc/ DESTINATION inc/fall4c
    PATTERN inc/*
    )
install (DIRECTORY ${PROJECT_BINARY_DIR}/inc/fall4c DESTINATION include)

