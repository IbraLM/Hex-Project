#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "move.h"
#include "graph.h"
#include "my-graph.h"


#define INT_MA 1000


struct player {
    char const* name;
    enum color_t couleur;
    struct graph_t* graph;
    size_t M;
    size_t N;
};

struct player player1;

struct path{
  size_t * tab;
  size_t size;
  size_t capacity;
};


/*returns an empty data-struct path*/
struct path* path__empty(){
  struct path*path=malloc(sizeof(struct path));
  path->capacity=1;
  path->size=0;
  path->tab=malloc(sizeof(path->capacity*sizeof(size_t)));
  return path;
}

/* whenever the capacity of nb is insufficient
 * this fonction allocate more memory*/
void path__realloc(struct path * path){
  if(path->capacity == 0){
    path->capacity = 1;
    path->tab = malloc(sizeof(size_t) * 1);
  }
  else if(path->size == path->capacity){
    size_t* tab = realloc(path->tab,(2 * path->capacity) * sizeof(size_t));
    path->tab = tab;
    path->capacity =path->capacity*2;
  }
}

/* adds the vertex n to struct of path path
 * return EXIT_SUCCESS if n was added correctly
 * and EXIT_FAILURE if not
 */
int path__add(struct path * path, int n){
  if((path->capacity == 0) || (path->size == 0)){
    path__realloc(path);
    path->tab[0] = n;
    path->size++;
    return EXIT_SUCCESS;
  }
  else{
  path__realloc(path);
  path->tab[path->size] =n;
  path->size++;
  return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}

/* free all the allocated memory of path*/
void path__free(struct path* path){
  free(path->tab);
  free(path);
}


char const* get_player_name(){
    player1.name="Heuristic";
    return player1.name;
}

struct move_t propose_opening(){
    size_t M=(int)sqrt(player1.graph->num_vertices)-1;
    struct move_t m;
    //m.c=player1.couleur;
    do{
      m.m=rand()%((M+1)*(M-1))+M+1;
    }while(m.m%(M+1)==0 || m.m%(M+1)==M);
    m.c=BLACK;
    graph_add_move(player1.graph,m);
    return m;
}


int accept_opening(const struct move_t opening){
    size_t M=(int)sqrt(player1.graph->num_vertices)-1;
    if(opening.m < (size_t)(M+1)*(M+1)){
        int a=rand()%2;
        if(a==1)
          return 1;
        else{
          struct move_t m=opening;
          m.c=BLACK;
          graph_add_move(player1.graph,m);
          return 0;
        }
      }

    else
        return 0;
}



void initialize_graph(struct graph_t* graph){
    player1.graph=graph;
    player1.M=(size_t)sqrt(player1.graph->num_vertices)-1;
    player1.N=(player1.M-1)*(player1.M-1);
}


int empty_index(struct player player, size_t i)
{
  size_t compteur = 0;
  for(size_t j = 0; j < player.graph->num_vertices ; j++)
  {
    if(gsl_spmatrix_get(player.graph->o, player.couleur, j) == 0 && gsl_spmatrix_get(player1.graph->o, (player.couleur+1)%2, j)==0)
      compteur++;
    if(compteur==i)
      return j;
  }
  return -1;
}

void initialize_color(enum color_t id){
    player1.couleur= id;
    if(id==BLACK)
      player1.N--;
}


int minDistance(int dist[], int sptSet[],int n){
	// Initialize min value
	int min = INT_MA, min_index;

	for (int v = 0; v < n; v++)
		if (sptSet[v] == 0 && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[],int parent[],int n)
{
	printf("Vertex \t\t Distance from Source \t\t parent\n");
	for (int i = 0; i < n; i++)
		printf("%d \t\t %d \t\t %d\n", i, dist[i],parent[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
struct path* get_shortest_path(struct graph_t* G,size_t M, int src, enum color_t id){
	int dist[G->num_vertices]; // The output array. dist[i] will hold the shortest
	// distance from src to i


  int parent[G->num_vertices];
   for(size_t i=0;i<G->num_vertices;i++){
    parent[i]=INT_MA;
  }

	int sptSet[G->num_vertices]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (size_t i = 0; i < G->num_vertices; i++)
		dist[i] = INT_MA, sptSet[i] = 0;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;
  parent[src]=-1;

	// Find shortest path for all vertices
	for (int count = 0; count < (int)(G->num_vertices - 1); count++) {
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.
		int u = minDistance(dist, sptSet,G->num_vertices);

		// Mark the picked vertex as processed
		sptSet[u] = 1;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (size_t v = 0; v < G->num_vertices; v++){


			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, v is not checked by the opennent, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && gsl_spmatrix_get(G->t,u,v)  && dist[u] != INT_MA
				&& !gsl_spmatrix_get(G->o,(id+1)%2,v) && dist[u] + (int)(gsl_spmatrix_get(G->t,u,v)-gsl_spmatrix_get(G->o,id,v)*gsl_spmatrix_get(G->o,id,u)) <= dist[v]){
				dist[v] = dist[u] + (int)(gsl_spmatrix_get(G->t,u,v)-gsl_spmatrix_get(G->o,id,v)*gsl_spmatrix_get(G->o,id,u));
        parent[v]=u;
        }
    }
  }
  struct path* p= path__empty();
  if(id==BLACK){
    int i=G->num_vertices-1;
    while(i!=-1){
      if(dist[i]==INT_MA)
        break;
      path__add(p,i);

      i=parent[i];
    }
  }
  else if(id==WHITE){
    int i=2*M+1;
    while(i!=-1){
      if(dist[i]==INT_MA)
        break;
      path__add(p,i);

      i=parent[i];
    }
  }
  return p;
}



struct graph_t* update1_graph(struct graph_t* G,struct move_t m){
  struct graph_t* copy=malloc(sizeof(struct graph_t));
  copy->num_vertices=G->num_vertices;
  copy->t=gsl_spmatrix_alloc(G->num_vertices,G->num_vertices);
  copy->o=gsl_spmatrix_alloc(2,G->num_vertices);
  size_t i=0,j=0;
  for(i=0;i<G->num_vertices;i++){
    gsl_spmatrix_set(copy->o,0,i,gsl_spmatrix_get(G->o,0,i));
    gsl_spmatrix_set(copy->o,1,i,gsl_spmatrix_get(G->o,1,i));
    for(j=0;j<G->num_vertices;j++){
      gsl_spmatrix_set(copy->t,i,j,gsl_spmatrix_get(G->t,i,j));

    }
  }
  graph_add_move(copy,m);
  return copy;
}


int path_score(struct path* path,struct graph_t* G)
{
  size_t score = 0,i=0;
  for(i=0; i<path->size; i++)
    {
      if((gsl_spmatrix_get(G->o, 0, path->tab[i]) == 0) && ((gsl_spmatrix_get(G->o, 1, path->tab[i]) == 0)))
	      score++;
    }
    return score;
}


int nombre_de_libre(struct graph_t* G)
{
  int compteur = 0;
  for(size_t i = 0; i < G->num_vertices; i++)
  {
    if(gsl_spmatrix_get(G->o,0, i) == 0 && gsl_spmatrix_get(G->o,1, i)==0)
      compteur++;
  }
  return compteur;
}


int heuristic(struct graph_t* G,int M){
  if(DFS(G,player1.couleur))
    return -INT_MA;
  if(DFS(G,(player1.couleur+1)%2))
    return INT_MA;
  struct path* p_path=get_shortest_path(G,M,player1.couleur*(M+1),player1.couleur);
  struct path* op_path=get_shortest_path(G,M,(player1.couleur+1)%2*(M+1),(player1.couleur+1)%2);
  int p_score=path_score(p_path,G);
  int op_score=path_score(op_path,G);
  path__free(p_path);
  path__free(op_path);
  return p_score-op_score;
}

int maxi(int a,int b){
  if(a>=b)
    return a;
  else
    return b;
}

int mini(int a,int b){
  if(a<=b)
    return a;
  else
    return b;
}


int is_empty(struct graph_t* G, int i){
    if(gsl_spmatrix_get(G->o,0, i) == 0 && gsl_spmatrix_get(G->o,1, i)==0)
      return 1;
    else
      return 0;
}

struct path* intersec(struct path* p1,struct path* p2){
  struct path* inter=path__empty();
  size_t i=0;
  if(p1->size<p2->size){
    for(i=0;i<p1->size;i++){
      for(size_t j=0;j<p2->size;j++){
        if(p1->tab[i]==p2->tab[j]){
          path__add(inter,p1->tab[i]);
          continue;
        }
      }
    }
  }
  else{
    for(i=0;i<p2->size;i++){
      for(size_t j=0;j<p1->size;j++){
        if(p2->tab[i]==p1->tab[j]){
          path__add(inter,p2->tab[i]);
          continue;
        }
      }
    }
  }
  return inter;
}
struct path* unio(struct path* p1,struct path* p2){
  for(size_t i=0;i<p2->size;i++){
    path__add(p1,p2->tab[i]);
  }
  return p1;
}

int min_max(struct graph_t* G, int maxminplayer, int depth, int alpha, int beta,enum color_t id,int M){
  struct path* p_path=get_shortest_path(player1.graph,player1.M,player1.couleur*(player1.M+1),player1.couleur);
  struct path* op_path=get_shortest_path(player1.graph,player1.M,(player1.couleur+1)%2*(player1.M+1),(player1.couleur+1)%2);
  struct path* un=intersec(p_path,op_path);
  if(depth==0 || DFS(G,id) || DFS(G,(id+1)%2) || un->size==0){
    int h=heuristic(G,M); //or game is over)
    path__free(p_path);
    path__free(op_path);
    path__free(un);
    return h;
  }

  else if(maxminplayer){
    int max=-INT_MA,count=0;
    for(size_t i=0;i<un->size;i++){
      if(is_empty(G,un->tab[i]) ){
          count++;
          struct move_t move;
          move.m=un->tab[i];
          move.c=id;
          struct graph_t*copy=update1_graph(G,move);
          max=maxi(max,min_max(copy,0,depth-1,alpha,beta,(id+1)%2,M));
          graph_free(copy);
          alpha=maxi(alpha,max);
          if(beta <= alpha)
            break;
      }
    }
    path__free(p_path);
    path__free(op_path);
    path__free(un);
    return max;
  }
  else{
    int min=INT_MA,count2=0;
    for(size_t i=0;i<un->size;i++){
      if(is_empty(G,un->tab[i])){
        count2++;
        struct move_t move;
        move.m=un->tab[i];
        move.c=id;
        struct graph_t*copy=update1_graph(G,move);
        min=mini(min,min_max(copy,1,depth-1,alpha,beta,(id+1)%2,M));
        graph_free(copy);
        beta=mini(beta,min);
        if(beta <= alpha)
          break;
      }
    }
    path__free(p_path);
    path__free(op_path);
    path__free(un);
    return min;
  }
}


struct move_t best_move(struct graph_t* G,enum color_t id, int M,struct path* inter){
  int bestval=10000;
  struct move_t m;
  m.m=0;
  m.c=id;

  for(size_t i=0;i<inter->size;i++){
      if(is_empty(G,inter->tab[i])){
          struct move_t move;
          move.m=inter->tab[i];
          move.c=id;
          struct graph_t*copy=update1_graph(G,move);
          int val=min_max(copy,1,10,-1000,1000,(id+1)%2,M);
          graph_free(copy);
          if(val<bestval){
            bestval=val;
            m.m=inter->tab[i];
          }

      }
    }
  return m;
}



struct move_t play(struct move_t previous_move){
    graph_add_move(player1.graph,previous_move);
    player1.N--;
    struct move_t m;
    m.c=player1.couleur;
    m.m=0;
    size_t N = player1.N;
    if(N==0){
      m.m=0;
      return m;
    }
    else if(N!=0){
      struct path* p_path=get_shortest_path(player1.graph,player1.M,player1.couleur*(player1.M+1),player1.couleur);
      struct path* op_path=get_shortest_path(player1.graph,player1.M,(player1.couleur+1)%2*(player1.M+1),(player1.couleur+1)%2);
      struct path* un=unio(p_path,op_path);
      struct neighbours* nb=get_neighbours(player1.graph,previous_move.m);
      struct path* p=path__empty();
      for(size_t i=0; i<nb->size;i++){
        path__add(p,nb->nb[i]);
      }
      nb__free(nb);
      struct path* uni=unio(un,p);
      path__free(p);
      m=best_move(player1.graph,player1.couleur,player1.M,uni);
      if(m.m==0){
        int i = rand()%N+1;
        int j = empty_index(player1,i);
        m.m = j;

      }
      path__free(p_path);
      path__free(op_path);
    }
 
    gsl_spmatrix_set(player1.graph->o,m.c,m.m,1);
    player1.N--;
    return m;
}

void finalize(){
  if(player1.graph!=NULL){
    graph_free(player1.graph);
    player1.graph=NULL;
  }
}



