#ifndef _MY_GRAPH_H_
#define _MY_GRAPH_H_

#include "graph.h"
#include "move.h"

/* initialization of a graph that has n vertices
 * and has the form given by c 
 * c can be either 'c'-->carre
 *                 'h'-->hex
 */
struct neighbours{
  size_t* nb;
  size_t size;
  size_t capacity;
};

struct graph_t* graph_initialize(size_t n,char c);

/* initialization of an allocated spmatrix o (2*n)
*/
gsl_spmatrix* initialize_o(gsl_spmatrix* o,size_t n);//, char c);c

/* allocate and return a square graph of n vertices 
 * after intializing its spmatrixes t and o
 */  
struct graph_t* initialize_carre(size_t n);

/* allocate and return  a hex graph of n vertices 
 * after intializing its spmatrixes t and o
 */
struct graph_t* initialize_hex(size_t n);

/*
À tester
 */
struct graph_t* initialize_triangular(size_t m);

/* free the allocated spmatrixes of the graph G
 * free the graph G
*/
void graph_free(struct graph_t* G); 

/* Display the given graph G 
 * according to his form
 */
void graph_display(struct graph_t* G,char c);

/* Add the given move 'move' to the graph G*/ 
void graph_add_move(struct graph_t* G,struct move_t move);

/* Depth-first search algorithm
 * used to find if two opposite sides are connected
 * it uses a recursive auxilary function DFSutil
 */
int DFS(struct graph_t* G,enum color_t id);

/*auxilary recursive function that starts the DFS from a specified vertex*/
int DFSutil(struct graph_t* G,size_t n,size_t* visited,enum color_t id);

struct neighbours* nb__empty();
void nb__realloc(struct neighbours * nb);
int nb__add(struct neighbours*nb, size_t n);
void nb__free(struct neighbours* nb);
struct neighbours* get_neighbours(struct graph_t* G,size_t n);
#endif //_MY_GRAPH_H_


