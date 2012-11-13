/*
    This file is part of fall4c.

    fall4c is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    fall4c is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with fall4c.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "data/tree_avl.h"

int main (int argc, char *argv[])
{
    struct tree_t *avl_bst;

    avl_bst = NULL;

    printf ("avl_bst: %p\n", avl_bst);
    printf ("&avl_bst: %p\n", &avl_bst);

    avl_add (&avl_bst, "aaaa");
    avl_add (&avl_bst, "bbbb");
    avl_add (&avl_bst, "cccc");
    avl_add (&avl_bst, "dddd");
    avl_add (&avl_bst, "eeee");
    avl_add (&avl_bst, "ffff");
    avl_add (&avl_bst, "gggg");
    avl_add (&avl_bst, "hhhh");
    avl_add (&avl_bst, "iiii");
    avl_add (&avl_bst, "jjjj");

    printf ("avl_bst: %p\n", avl_bst);
    printf ("&avl_bst: %p\n", &avl_bst);

    avl_show (avl_bst);

    return 0;
}

