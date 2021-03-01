#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "player.h"
#include "graph.h"
#include "my-graph.h"
#include "move.h"

struct player {
  char const* name;
  enum color_t couleur;
  struct graph_t* graph;
  size_t M; 
  size_t N;                         // Nombre de cases libres
  };

void test__initialize_graph()
{
  struct graph_t* graph = initialize_carre(16);
  struct player player1;
  initialize_graph(graph);
  assert(player1.graph==graph);
  assert(player1.M==3);
  assert(player1.N==9);
}

void test__initialize_color()
{
  struct player player1;
  struct move_t move;
  move.m = 2;
  move.c = 1;
  initialize_color(move.c);
  assert(player1.couleur == 1);
}


int main()
{
  test__initialize_graph();
  test__initialize_color();
  return 0;
}
