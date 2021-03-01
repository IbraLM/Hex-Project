#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "move.h"
#include "graph.h"
#include "my-graph.h"

struct player {
    char const* name;
    enum color_t couleur;
    struct graph_t* graph;
    size_t M;
    size_t N;
};

struct player player1;

char const* get_player_name(){
    player1.name="Hero";
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

struct move_t play(struct move_t previous_move){
    gsl_spmatrix_set(player1.graph->o, player1.couleur, previous_move.m, 1);
    struct move_t m;
    m.c=player1.couleur;
    player1.N--;
    size_t N = player1.N;//nombre_de_libre(player1, (M+1)*(M+1));
    //printf("nombre de cases libres %zu\n",N);
    if(N==0){
      m.m=0;
      return m;
    }
    int i = rand()%N+1;
    int j = empty_index(player1,i);
    m.m = j;
    gsl_spmatrix_set(player1.graph->o,player1.couleur,m.m,1);
    player1.N--;
    return m;
}

void finalize(){
  if(player1.graph!=NULL){
    graph_free(player1.graph);
    player1.graph=NULL;
  }
}
