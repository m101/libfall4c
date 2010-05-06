#ifndef _TREE_BINARY_H_
#define _TREE_BINARY_H_

#include <stddef.h>             /* pour size_t */

#include "tree_common.h"

// Add data to tree
struct tree_t* binary_search_tree_add (struct tree_t *root, void *data);
// Display whole tree
void binary_tree_display (struct tree_t *root);
void binary_tree_display_right (struct tree_t *root);
void binary_tree_display_left (struct tree_t *root);

#endif /* _TREE_BINARY_H_ */

