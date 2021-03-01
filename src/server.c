#include <stdio.h>
#include <getopt.h>
#include <dlfcn.h>
#include <time.h>
#include <assert.h>
#include "move.h"
#include "my-graph.h"
#include "player-load.h"



size_t M=8;
char T= 'h';
int next=0;

int is_winning(struct graph_t* G,enum color_t id){
  int win=DFS(G,id);
  return win;
}

void parse_opts(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "m:t:")) != -1) {
    switch (opt) {
    case 'm' :
      M = atoi(optarg);
      break;
    case 't' :
      T = *optarg;
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-m M] [-t T]\n",argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  if (optind >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }
}
struct graph_t* server_plateau=NULL;
struct graph_t* player1_plateau=NULL;
struct graph_t* player2_plateau=NULL;


int main(int argc,char*argv[]){
    parse_opts(argc,argv);
    srand(time(NULL));
    struct player players[2];
    struct player p;
    for(int i=0; i<2;i++){
      printf("%s\n",argv[argc-2+i]);
      players[i]=player_open(argv[argc-2+i]);
    }
    assert(dlerror()== NULL);
    server_plateau=graph_initialize((M+1)*(M+1),T);
    player1_plateau=graph_initialize((M+1)*(M+1),T);
    player2_plateau=graph_initialize((M+1)*(M+1),T);
    printf("|-|-|-|___THE GAME BEGINS____|-|-|-|\n");
    //graph_display(server_plateau,T);
    printf("====================================\n");
    players[0].initialize_graph(player1_plateau);
    players[1].initialize_graph(player2_plateau);
    struct move_t move=players[0].propose_opening();
    move.c=BLACK;
    graph_add_move(server_plateau,move);
    if(players[1].accept_opening(move)){
      //graph_add_move(player1_plateau,move);
      printf("%s begins\n", players[0].get_player_name());   
      printf("he puts the %d piece on the %ld vertex\n",move.c,move.m);
      players[0].initialize_color(BLACK);
      players[1].initialize_color(WHITE);
      next=1;
    }
    else{
      printf("%s begins\n", players[1].get_player_name());
      //move=players[1].propose_opening();
      //move.c=BLACK;
      //graph_add_move(server_plateau,move);
      //graph_add_move(player2_plateau,move);
      printf("he puts the %d piece on the %ld vertex\n",move.c,move.m);
      players[0].initialize_color(WHITE);
      players[1].initialize_color(BLACK);
      next=2;
    }
    
    int k=0;
    while(1){
      p=players[next%2];//compute_next_player
      printf("%s gonna play\n",p.get_player_name());
      move=p.play(move);
      if(!move.m){
        //there's no empty places
        printf("%s can not play, there's no empty place\n",p.get_player_name()); 
        k=1;
        break;
      }
      printf("he puts the %d piece on the %ld vertex\n",move.c,move.m);
      graph_add_move(server_plateau,move);
      //graph_display(server_plateau,T);
      next++;
      if(is_winning(server_plateau,move.c)){
        printf("the player %s wins\n",p.get_player_name());
        break;      
      }

    }
    graph_display(server_plateau,T);
    graph_free(server_plateau);
    for(int i=0; i<2;i++){
      players[i].finalize();
    }
    for(int i=0; i<2;i++){

      //int close = player_close(players[i]);
      player_close(players[i]);
      //if(close != 0){
        //printf("Error : The player isn't unloaded!");  
	//return 1;
    //  }
    
    }
    if(k)
      printf("It's a DRAWW!\n");
    else
      printf("CONGRATS!!\n");
    return 0;
}

