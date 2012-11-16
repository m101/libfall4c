cmake_minimum_required (VERSION 2.8.9)
project (libfall4c)

set (CMAKE_BUILD_TYPE Debug)

ENABLE_TESTING()
SET (CMAKE_CXX_FLAGS        "-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
SET (CMAKE_C_FLAGS          "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")

# The version number.
set (FALL4C_VERSION_MAJOR 1)
set (FALL4C_VERSION_MINOR 0)

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
    SHARED
    src/escape.c
    src/file.c
    src/filemap.c
    src/string_ext.c
    src/file_browse.c
    src/data/wordlist.c
    src/data/list.c
    src/data/queue.c
    src/data/stack.c
    src/data/tree_avl.c
    src/data/tree_redblack.c
    src/data/tree_common.c
    src/data/tree_binary.c
    src/data/tree_sparse.c
    # src/reed_solomon.c
    src/collision.c
    # src/pathfinding.c
    src/data/array_manipulation.c
    src/data/hashtable.c
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
target_link_libraries (fall4c
    unac
    m
    gcov
    )

# executable testing wordlist
add_executable (wordlist_example
    src/data/wordlist_example.c
    )
target_link_libraries (wordlist_example
    fall4c
    gcov
    )
# test: coverage
add_test(NAME wordlist_example COMMAND wordlist_example)

# executable testing wordlist
add_executable (binstr_to_bin
    tests/binstr_to_bin.c
    )
target_link_libraries (binstr_to_bin
    fall4c
    gcov
    )
# test: coverage
add_test(NAME binstr_to_bin COMMAND binstr_to_bin)

# executable testing wordlist
add_executable (avl_tree_test
    tests/avl_tree.c
    )
target_link_libraries (avl_tree_test
    fall4c
    gcov
    )
# test: coverage
add_test(NAME avl_tree_test COMMAND avl_tree_test)

install (TARGETS fall4c DESTINATION lib)
file (
    COPY ${PROJECT_SOURCE_DIR}/inc/ DESTINATION inc/fall4c
    PATTERN inc/*
    )
install (DIRECTORY ${PROJECT_BINARY_DIR}/inc/fall4c DESTINATION include)

