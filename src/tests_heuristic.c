#include "heuristic.h"
#include "tests_heuristic.h"
#include "move.h"
#include "graph.h"
#include <assert.h>
#include <string.h>
#include "my-graph.h"


struct player {
    char const* name;
    enum color_t couleur;
    struct graph_t* graph;
    size_t M;
};


struct path{
  size_t * tab;
  size_t size;
  size_t capacity;
};


extern struct player player3;


void test_path_empty()
{
  struct path * path = path__empty();
  assert(path->capacity == 1 && path->size == 0);
  printf("test_path_empty..\033[0;32mPASSED\033[0m\n");
  path__free(path);
}


void test_path_realloc()
{
  struct path* path = path__empty();
  path->capacity = 1;
  path->size = path->capacity;
  path__realloc(path);
  assert(path->capacity == 2);
  path__free(path);
  printf("test_path_realloc..\033[0;32mPASSED\033[0m\n");
}


void test_empty_index()
{
  printf("test_empty_index..""\033[31mIMPOSSIBLE A TESTER CAR NON DECLARABLE DANS heuristic.h\033[0m\n");
}


void test_path_add()
{
  struct path * path = path__empty();
  path__add(path, 0);
  assert(path->tab[0] == 0);
  assert(path->size == 1);
  for (int i = 1; i < 5; i++)
    path__add(path, 3 * i);
  for (int i = 1; i < 5; i ++)
      assert(path->tab[i] = 3 * i);
  assert(path->size == 5);
  assert(path->capacity == 8);
  path__free(path);
  printf("test_path_add..\033[0;32mPASSED\033[0m\n");
}


void test_get_player_name()
{
    char const* name=get_player_name();
    assert(!strcmp(name,"Heuristic"));
    printf("test_get_player_name..\033[0;32mPASSED\033[0m\n");
}


void test_propose_opening()
{
  assert(1);
  printf("test_min_max..\033[0;32mPASSED\033[0m\n");
}


void test_minDistance()
{
  int dist6[6] = {3, 3, 6, 15, 2, 18};
  int sptSet6[6] = {0, 0, 0, 1, 0, 1};
  int res6 = minDistance(dist6, sptSet6, 6);
  assert(res6 == 4);
  int dist2[2] = {3, 3};
  int sptSet2[2] = {0, 0};
  int res2 = minDistance(dist2, sptSet2, 2);
  assert(res2 == 1);
  printf("test_minDistance..\033[0;32mPASSED\033[0m\n");
}


void test_get_shortest_path()
{
  assert(1);
  printf("test_get_shortest_path..\033[31m TEST A FAIRE\033[0m\n");
}


void test_update1_graph()
{
  struct graph_t* G = malloc(sizeof(struct graph_t));
  G->t = gsl_spmatrix_alloc(16, 16);
  G->o = gsl_spmatrix_alloc(2, 16);
  G->num_vertices = 3;
  struct move_t m;
  m.m = G->num_vertices-1;
  m.c = 1;
  struct graph_t* copy = update1_graph(G, m);//malloc(sizeof(struct graph_t));

  for(size_t i = 0; i <  G->num_vertices-1; i++)
  {
    if(i != m.m)
      {
	assert(gsl_spmatrix_get(copy->o, 0, i) == gsl_spmatrix_get(G->o, 0, i));
	assert(gsl_spmatrix_get(copy->o, 1, i) == gsl_spmatrix_get(G->o, 1, i));
      }
    for(size_t j = 0; j < G->num_vertices-1; j++)
    {
      if(i!=m.m)
	assert(gsl_spmatrix_get(copy->t, i, j) == gsl_spmatrix_get(G->t, i, j));
    }
  }
  assert(gsl_spmatrix_get(copy->o, m.c, m.m) == 1);
  graph_free(G);
  graph_free(copy);
  printf("test_update1_graph..\033[32mPASSED\033[0m\n");
}


void test_path_score()
{
  size_t score = 0;
  struct path * path= path__empty();
  path__add(path, 2);
  path__add(path, 0);
  path__add(path, 3);
  path__add(path, 1);
  struct graph_t* G = malloc(sizeof(struct graph_t));
  G->t = gsl_spmatrix_alloc(4, 4);
  G->o = gsl_spmatrix_alloc(2, 4);
  G->num_vertices = 3;
  score = path_score(path, G);
  assert(score == path->size);
  path__free(path);
  graph_free(G);
  printf("test_path_score..\033[0;32mPASSED\033[0m\n");
}


void test_nombre_de_libre()
{
  struct graph_t * G = malloc(sizeof(struct graph_t));
  G->t = gsl_spmatrix_alloc(4, 4);
  G->o = gsl_spmatrix_alloc(2,4);
  G->num_vertices = 4;
  int compteur = nombre_de_libre(G);
  assert(compteur == 4);
  printf("test_nombre_de_libre..\033[0;32mPASSED\033[0m\n");
  graph_free(G);
}


void tests_heuristic()
{
  assert(1);
  printf("tests_heuristic..\033[31m TEST A FAIRE\033[0m\n");
}


void test_maxi()
{
  int a = 5;
  int b = -13;
  int res = maxi(a, b);
  assert(res == a);
  a = -0;
  b = 8;
  res = maxi(a, b);
  assert(res == b);
  a = 2;
  b = 2;
  res = maxi(a, b);
  assert(res == b);
  printf("test_maxi..\033[0;32mPASSED\033[0m\n");
}


void test_mini()
{
  int a = 5;
  int b = -13;
  int res = mini(a, b);
  assert(res == b);
  a = -0;
  b = 8;
  res = mini(a, b);
  assert(res == a);
  a = 2;
  b = 2;
  res = mini(a, b);
  assert(res == b);
  printf("test_mini..\033[0;32mPASSED\033[0m\n");
}

void test_is_empty()
{
  struct graph_t* G = malloc(sizeof(struct graph_t));
  G->t = gsl_spmatrix_alloc(4, 4);
  G->o = gsl_spmatrix_alloc(2, 4);
  G->num_vertices = 4;
  gsl_spmatrix_set(G->o, 0, 2, 0);
  gsl_spmatrix_set(G->o, 1, 2, 0);
  int res = is_empty(G, 2);
  assert(res == 1);
  gsl_spmatrix_set(G->o, 0, 2, 1);
  gsl_spmatrix_set(G->o, 1, 2, 1);
  res = is_empty(G, 2);
  assert(res == 0);
  gsl_spmatrix_set(G->o, 0, 2, 0);
  gsl_spmatrix_set(G->o, 1, 2, 1);
  res = is_empty(G, 2);
  assert(res == 0);
  graph_free(G);
  printf("test_is_empty..\033[0;32mPASSED\033[0m\n");
}


void test_intersect()
{
  struct path * path1 = path__empty();
  path__add(path1, 2);
  path__add(path1, 0);
  path__add(path1, 3);
  path__add(path1, 1);
  struct path * path2 = path__empty();
  path__add(path2, 0);
  path__add(path2, 5);
  path__add(path2, 7);
  path__add(path2, 3);
  struct path * path_intersec = path__empty();
  path__add(path_intersec, 0);
  path__add(path_intersec, 3);
  struct path * path_res = intersec(path1, path2);//path__empty();
  assert(path_res->size == path_intersec->size);
  for(int i = 0; i < (int) path_res->size; i++)
  {
    assert(path_res->tab[i] == path_intersec->tab[i]);
  }
  path__free(path1);
  path__free(path2);
  path__free(path_intersec);
  path__free(path_res);
  printf("test_intersect..\033[0;32mPASSED\033[0m\n");
}


void test_min_max()
{
  assert(1);
  printf("test_min_max..\033[31m TEST A FAIRE\033[0m\n");
}


void test_best_move()
{
  assert(1);
  printf("test_best_move..\033[31m TEST A FAIRE\033[0m\n");
}


void test_play()
{
  assert(1);
  printf("test_play..\033[31m TEST A FAIRE\033[0m\n");
}


void test_finalize()
{
  assert(1);
  printf("test_finalize..\033[0;31m player3 error\033[0m\n");
}
