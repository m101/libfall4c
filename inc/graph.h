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

#ifndef _GRAPH_H_
#define _GRAPH_H_

struct graph_node
{
        int weigth;
        struct graph_node *adjacent, *neighbourg;
};

struct graph_edge
{
        int weight;
        struct graph_node *next, *prev;
};

int graph_node_add (struct graph_node *node);

#endif

