#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "move.h"
#include "graph.h"

int identite(int i);
struct path* path__empty();
void path__realloc(struct path * path);
int path__add(struct path * path, size_t n);
void path__free(struct path* path);
//char const* get_player_name();
//struct move_t propose_opening();
//int accept_opening(const struct move_t opening);
//void initialize_graph(struct graph_t* graph);
// int empty_index(struct player player, size_t i);
//void initialize_color(enum color_t id);
int minDistance(int dist[], int sptSet[],int n);
void printSolution(int dist[],int parent[],int n);
struct path* get_shortest_path(struct graph_t* G,size_t M, int src,enum color_t id);
struct graph_t* update1_graph(struct graph_t* G,struct move_t m);
int path_score(struct path* path,struct graph_t* G);
int nombre_de_libre(struct graph_t* G);
int heuristic(struct graph_t* G,int M);
int maxi(int a,int b);
int mini(int a,int b);
int is_empty(struct graph_t* G, int i);
struct path* intersec(struct path* p1,struct path* p2);
int min_max(struct graph_t* G, int maxminplayer, int depth, int alpha, int beta,enum color_t id,int M);
struct move_t best_move(struct graph_t* G,enum color_t id, int M,struct path* inter);
//struct move_t play(struct move_t previous_move);
//void finalize();
