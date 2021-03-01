#include <stdio.h>
#include "my-graph.h"



////PRIVATE FUNCTIONS ans structures

/*dynamic data struct built in ordre to
* save the neighbours of a vertex
* nb       : is a dynamic array of vertices
* size     : is the size of nb
* capacity : is the capacity of nb
*/

/*
struct neighbours{
  size_t* nb;
  size_t size;
  size_t capacity;
};
*/
/*returns an empty data-struct neighbours*/
struct neighbours* nb__empty(){
  struct neighbours*nb=malloc(sizeof(struct neighbours));
  nb->capacity=1;
  nb->size=0;
  nb->nb=malloc(sizeof(nb->capacity*sizeof(size_t)));
  return nb;
}

/* whenever the capacity of nb is insufficient
 * this fonction allocate more memory*/
void nb__realloc(struct neighbours *nb){
  if(nb->capacity == 0){
    nb->capacity = 1;
    nb->nb = malloc(sizeof(size_t) * 1);
  }
  else if(nb->size == nb->capacity){
    size_t* tab = realloc(nb->nb,(2 * nb->capacity) * sizeof(size_t));
    nb->nb = tab;
    nb->capacity =nb->capacity*2;
  }
}

/* adds the vertex n to struct of neighbours nb
 * return EXIT_SUCCESS if n was added correctly
 * and EXIT_FAILURE if not
 */
int nb__add(struct neighbours*nb, size_t n){
  if((nb->capacity == 0) || (nb->size == 0)){
    nb__realloc(nb);
    nb->nb[0] = n;
    nb->size++;
    return EXIT_SUCCESS;
  }
  else{
  nb__realloc(nb);
  nb->nb[nb->size] =n;
  nb->size++;
  return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

/* free all the allocated memory of nb*/
void nb__free(struct neighbours* nb){
  free(nb->nb);
  free(nb);
}

/* return the neighbours of a given vertex n
 * in the graph G
 */
struct neighbours* get_neighbours(struct graph_t* G,size_t n){
  struct neighbours*nb=nb__empty();
  for(size_t j=0;j<G->num_vertices;j++){
    if(gsl_spmatrix_get(G->t,n,G->num_vertices-1-j)==1){
      nb__add(nb,G->num_vertices-1-j);
    }
  }
  return nb;
}

/////

gsl_spmatrix* initialize_o(gsl_spmatrix* o,size_t n){
    size_t i=0;
    size_t m=(int)sqrt(n)-1;
    for(i=0;i<m;i++){
        gsl_spmatrix_set(o,0,i,1);
        gsl_spmatrix_set(o,0,n-i-1,1);
    }
    for(i=m;i+1<n;i=i+m+1){
        gsl_spmatrix_set(o,1,i,1);
        gsl_spmatrix_set(o,1,i+1,1);
    }
    return o;
}


struct graph_t* initialize_carre(size_t n){
    struct graph_t* G=malloc(sizeof(struct graph_t));
    G->num_vertices=n;
    G->t=gsl_spmatrix_alloc(n,n);
    G->o=gsl_spmatrix_alloc(2,n);
    initialize_o(G->o,n);
    //initialize G->t
    size_t i=0;
    for(i=0;i<n;i++){
        size_t m=(size_t)sqrt(n);
        if((i+1)%m!=0){
            gsl_spmatrix_set(G->t,i,i+1,1);
            gsl_spmatrix_set(G->t,i+1,i,1);
        }
        if(i+m<n){
            gsl_spmatrix_set(G->t,i,i+m,1);
            gsl_spmatrix_set(G->t,i+m,i,1);
        }
    }
    return G;
}



struct graph_t* initialize_hex(size_t n){
    struct graph_t* G=malloc(sizeof(struct graph_t));
    G->t=gsl_spmatrix_alloc(n,n);
    G->o=gsl_spmatrix_alloc(2,n);
    G->num_vertices=n;
    initialize_o(G->o,n);//, 'h');
    //initialize G->t
    size_t i=0;
    for(i=0;i<n;i++){
        size_t m=(size_t)sqrt(n);
        if((i+1)%m!=0){
            gsl_spmatrix_set(G->t,i,i+1,1);
            gsl_spmatrix_set(G->t,i+1,i,1);
        }
        if(i+m<n){
            gsl_spmatrix_set(G->t,i,i+m,1);
            gsl_spmatrix_set(G->t,i+m,i,1);
            if(i%m!=0){
              gsl_spmatrix_set(G->t,i,i+m-1,1);
              gsl_spmatrix_set(G->t,i+m-1,i,1);
            }
        }
    }
    return G;
}


struct graph_t* graph_initialize(size_t n,char c){
  struct graph_t* graph=NULL;
  switch(c){
  case 'c':
    graph=initialize_carre(n);
    break;
  case 'h':
    graph=initialize_hex(n);
    break;
 /* case 't':
    graph=initialize_triangular(n);
    break;*/
  default:
    break;
  }
  return graph;
}

void graph_free(struct graph_t* G){
    gsl_spmatrix_free(G->o);
    gsl_spmatrix_free(G->t);
    free(G);
}

void graph_add_move(struct graph_t* G,struct move_t move){
    gsl_spmatrix_set(G->o,move.c,move.m,1);
}



void graph_display(struct graph_t*G,char t){
  size_t M=(int)sqrt(G->num_vertices)-1;
  //if G is a square graph
  if(t=='c'){
    for (size_t i = 0; i < M+1; i++){
        printf("[\t");
        for (size_t j = 0; j < M+1; j++){
          if(gsl_spmatrix_get(G->o, 0, i*(M+1)+j))
            printf("\x1b[30m%c \x1b[37m\t",'B');
          else if(gsl_spmatrix_get(G->o, 1, i*(M+1)+j)){
            printf("\x1b[37m%c \x1b[37m\t",'W');
          }
	        else
            printf("%c\t",'.');
	      }
        printf("]\n");
    }
  }
  //if G is a Hex graph
  else if(t=='h'){
    for (size_t i = 0; i < M+1; i++){
        for(size_t k=0;k<i;k++)
          printf("\t");
        printf("[\t");
        for (size_t j = 0; j < M+1; j++){
          if(gsl_spmatrix_get(G->o, 0, i*(M+1)+j))
            printf("\x1b[30m%c \x1b[37m\t",'B');
          else if(gsl_spmatrix_get(G->o, 1, i*(M+1)+j)){
            printf("%c\t",'W');
          }
	        else
            printf("%c\t",'.');
	      }
        printf("]\n");
    }
  }
}


int DFS(struct graph_t* G,enum color_t id){
  size_t M=(int)sqrt(G->num_vertices)-1;
  size_t* visited=malloc(G->num_vertices*sizeof(size_t));
  // Mark all the vertices as not visited
  for(size_t i=0;i<G->num_vertices;i++){
    visited[i]=0;
  }
  //Determine the start vertex of the DFS
  int a=0,b=0;
  if(id==BLACK){
    a=DFSutil(G,0,visited,id);
  }else if(id==WHITE){
    b=DFSutil(G,M+1,visited,id);
  }
  free(visited);
  if(a==1 || b==1)
    return 1;
  else
    return 0;
}

int DFSutil(struct graph_t* G,size_t n,size_t* visited,enum color_t id){
  size_t M=(int)sqrt(G->num_vertices)-1;
  //mark the current vertex as visited
  visited[n]=1;
  struct neighbours* nb=get_neighbours(G,n);
  //recur for all the adjacent vertices of n
  for(size_t i=0;i<nb->size;i++){
    if(gsl_spmatrix_get(G->o,id,nb->nb[i])==1 && !visited[nb->nb[i]]){
      if((id==BLACK && nb->nb[i]>=G->num_vertices-M) || (id==WHITE && nb->nb[i]%(M+1)==M)){
        //there's a winner
        nb__free(nb);
        return 1;
      }
      else{
        if(DFSutil(G,nb->nb[i],visited,id)){
          //there's a winner
          nb__free(nb);
          return 1;
        }
      }
    }
  }
  //it's a draw
  nb__free(nb);
  return 0;
}
