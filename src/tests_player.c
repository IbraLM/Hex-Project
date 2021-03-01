#include "player.h"
#include "move.h"
#include <assert.h>
#include <string.h>
#include "my-graph.h"

struct player {
    char const* name;
    enum color_t couleur;
    struct graph_t* graph;
    size_t M;
};
extern struct player player1;


void test_get_player_name(){
    char const* name=get_player_name();
    assert(!strcmp(name,"Hero"));
    printf("test_get_player_name..\033[0;32mPASSED\033[0m\n");
}

void test_propose_opening(){
    size_t x=rand()%8+2;
    x=x*x;
    struct graph_t*G1=graph_initialize(x,'c');
    struct graph_t*G2=graph_initialize(x,'h');
    initialize_graph(G1);
    struct move_t m=propose_opening();
    assert(m.c==BLACK && m.m%x!=0 && m.m%x!=x-1);
    initialize_graph(G2);
    m=propose_opening();
    assert(m.c==BLACK && m.m%x!=0 && m.m%x!=x-1);
    graph_free(G1);
    graph_free(G2);
    printf("test_propose_opening..\033[0;32mPASSED\033[0m\n");
}

void test_initialize_graph(){
    size_t x=rand()%8+2;
    x=x*x;
    struct graph_t*G1=graph_initialize(x,'c');
    struct graph_t*G2=graph_initialize(x,'h');
    initialize_graph(G1);
    assert(player1.graph==G1 && player1.M==(size_t)sqrt(x)-1);
    initialize_graph(G2);
    assert(player1.graph==G2 && player1.M==(size_t)sqrt(x)-1);
    graph_free(G1);
    graph_free(G2);
    printf("test_initialize_graph..\033[0;32mPASSED\033[0m\n");
}

void test_initialize_color(){
    initialize_color(BLACK);
    assert(player1.couleur==BLACK);
    initialize_color(WHITE);
    assert(player1.couleur==WHITE);
    printf("test_initialize_color..\033[0;32mPASSED\033[0m\n");
}

void test_play(){
    size_t x=rand()%8+2;
    x=x*x;
    size_t i=rand()%2;
    char t='c';
    switch(i){
        case 0:
            t='c';
            break;
        case 1:
            t='h';
            break;
        default:
            break;
    }
    struct graph_t*G1=graph_initialize(x,t);
    initialize_graph(G1);
    int y=rand()%(G1->num_vertices)+1;
    struct move_t m1={BLACK,y};
    struct move_t m2=play(m1);
    struct move_t m3=play(m2);
    assert(gsl_spmatrix_get(player1.graph->o,player1.couleur,m1.m)==1 && gsl_spmatrix_get(player1.graph->o,player1.couleur,m2.m)==1 );
    assert(gsl_spmatrix_get(player1.graph->o,player1.couleur,m2.m)==1 && gsl_spmatrix_get(player1.graph->o,player1.couleur,m3.m)==1 );
    struct graph_t*G2=graph_initialize(9,'c');
    initialize_graph(G2);
    struct move_t move=propose_opening();
    assert(move.c==BLACK && move.m==4);
    struct move_t new=play(move);
    assert(gsl_spmatrix_get(player1.graph->o,player1.couleur,4)==1 && new.m==0);
    graph_free(G1);
    graph_free(G2);
    printf("test_play..\033[0;32mPASSED\033[0m\n");
}

void test_finalize(){
    size_t x=rand()%8+2;
    x=x*x;
    struct graph_t*G=graph_initialize(x,'c');
    initialize_graph(G);
    finalize();
    assert(player1.graph==NULL);
    printf("test_finalize..\033[0;32mPASSED\033[0m\n");
}
