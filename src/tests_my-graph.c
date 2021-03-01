#include <stdio.h>
#include <assert.h>
#include "my-graph.h"
#include "player.h"
#include "move.h"
#include "graph.h"
#include "tests_my-graph.h"
/*
struct neighbours{
  size_t* nb;
  size_t size;
  size_t capacity;
};
*/
void test_nb__empty()
{
  struct neighbours* nb = nb__empty();
  assert(nb->capacity == 1);
  assert(nb->size == 0);
  assert(nb->nb != NULL);
  printf("test_nb__empty..\033[0;32mPASSED\033[0m\n");
  nb__free(nb);
}

void test_nb__realloc()
{
  struct neighbours* nb=nb__empty();
  nb->capacity = 1;
  nb->size = nb->capacity;
  nb__realloc(nb);
  assert(nb->capacity == 2);
  nb__free(nb);
  printf("test_nb__realloc..\033[0;32mPASSED\033[0m\n");
}

void test_nb__add()
{
  struct neighbours* nb = nb__empty();
  nb__add(nb, 1);
  assert(nb->nb[0] == 1);
  assert(nb->size == 1);
  
  nb__add(nb, 2);
  assert(nb->nb[1] == 2);
  assert(nb->size == 2);
  assert(nb->capacity == 2);

  for (int i = 3; i < 10; i++)
    nb__add(nb, i);
  for (int i = 1; i < 10; i ++)
      assert(nb->nb[i-1] = i);
  assert(nb->size == 9);
  assert(nb->capacity == 16);
  nb__free(nb);
  printf("test_nb__add..\033[0;32mPASSED\033[0m\n");
}

void test_nb__free()
{
  assert(0 == 0); //impossible de tester si un pointeur est free ou pas.
  printf("test_nb__free..\033[0;32mPASSED\033[0m\n");
}

void test_get_neighbours()
{
  struct neighbours* nb;
  struct graph_t* G = initialize_carre(25);
  nb = get_neighbours(G, 13);
  assert(nb->size == 4);
  assert(nb->nb[0] == 18);
  assert(nb->nb[1] == 14);
  assert(nb->nb[2] == 12);
  assert(nb->nb[3] == 8);
  nb__free(nb);
  nb = get_neighbours(G, 0);
  assert(nb->size == 2);
  assert(nb->nb[0] == 5);
  assert(nb->nb[1] == 1);
  nb__free(nb);
  nb = get_neighbours(G, 14);
  assert(nb->size == 3);
  assert(nb->nb[0] == 19);
  assert(nb->nb[1] == 13);
  assert(nb->nb[2] == 9);
  nb__free(nb);
  graph_free(G);
  printf("test_get_neighbours..\033[0;32mPASSED\033[0m\n");
}

void test_initialize_carre()
{
  size_t n = 6;
  struct graph_t* G = initialize_carre(n*n);
  size_t indice = rand() % n*n;
  struct neighbours* nb = get_neighbours(G, indice);
  if (nb->size == 4)
    {
      assert(nb->nb[0] == indice + n);
      assert(nb->nb[1] == indice + 1);
      assert(nb->nb[2] == indice - 1);
      assert(nb->nb[3] == indice - n);
    }
  if (nb->size == 3)
    {
      if (indice < n)
	{
	  assert(nb->nb[0] == indice + n);
	  assert(nb->nb[1] == indice + 1);
	  assert(nb->nb[2] == indice - 1);
	}
       if (indice % n == 0)
	{
	  assert(nb->nb[0] == indice + n);
	  assert(nb->nb[1] == indice + 1);
	  assert(nb->nb[2] == indice - n);
	}
       if (indice % n == n - 1)
	 {
	   assert(nb->nb[0] == indice + n);
	   assert(nb->nb[1] == indice - 1);
	   assert(nb->nb[2] == indice - n);
	 }
       if (indice >= n*(n-1))
	 {
	   assert(nb->nb[0] == indice + 1);
	   assert(nb->nb[1] == indice - 1);
	   assert(nb->nb[2] == indice - n);
	 }
    }
  if (nb->size == 2)
    {
      if (indice == 0)
	{
	  assert(nb->nb[0] == indice + n);
	  assert(nb->nb[1] == indice + 1);
	}
      if (indice == n-1)
	{
	  assert(nb->nb[0] == indice + n);
	  assert(nb->nb[1] == indice - 1);
	}
      if (indice == n*(n-1))
	{
	  assert(nb->nb[0] == indice + 1);
	  assert(nb->nb[1] == indice - n);
	}
      if (indice == n*n - 1)
	{
	  assert(nb->nb[1] == indice - 1);
	  assert(nb->nb[2] == indice - n);
	}
    }
  printf("test_initialize_carre..\033[0;32mPASSED\033[0m\n");
  graph_free(G);
  nb__free(nb);
}

void test_initialize_o()
{
  size_t n1 = 64;
  gsl_spmatrix* o_test1;
  o_test1 = gsl_spmatrix_alloc(2, n1);
  int gsl_spmatrix_set_zero(gsl_spmatrix * o_test1);
  for(int i = 0; i < 7; i++)
  {
    gsl_spmatrix_set(o_test1, 0, i, 1);
  }
  for(int i = n1 - 1; i > (int) n1 - 8; i--)
  {
    gsl_spmatrix_set(o_test1, 0, i, 1);
  }
  for(int j = 8; j < (int) n1 - 7; j = j + 8)
  {
    gsl_spmatrix_set(o_test1, 1, j, 1);
  }
  for(int j = 7; j < (int) n1 - 7; j = j + 8)
  {
    gsl_spmatrix_set(o_test1, 1, j, 1);
  }
  gsl_spmatrix* o1;
  o1 = gsl_spmatrix_alloc(2, n1);
  o1 = initialize_o(o1, n1);
  int compteur1 = 0;
  for(int k = 0; k < 2; k++)
  {
    for(int l = 0; l < (int) n1; l++)
    {
      if (gsl_spmatrix_get(o_test1, k, l) != gsl_spmatrix_get(o1, k, l))
        compteur1++;
    }
  }
  gsl_spmatrix_free(o_test1);
  gsl_spmatrix_free(o1);
  assert(compteur1 == 0);
  // 2e test
  size_t n2 = 16;
  gsl_spmatrix* o_test2;
  o_test2 = gsl_spmatrix_alloc(2, n2);
  int gsl_spmatrix_set_zero(gsl_spmatrix * o_test2);
  for(int i = 0; i < 3; i++)
  {
    gsl_spmatrix_set(o_test2, 0, i, 1);
  }
  for(int i = n2 - 1; i > (int) n2 - 4; i--)
  {
    gsl_spmatrix_set(o_test2, 0, i, 1);
  }
  for(int j = 4; j < (int) n2 - 3; j = j + 4)
  {
    gsl_spmatrix_set(o_test2, 1, j, 1);
  }
  for(int j = 3; j < (int) n2 - 3; j = j + 4)
  {
    gsl_spmatrix_set(o_test2, 1, j, 1);
  }
  gsl_spmatrix* o2;
  o2= gsl_spmatrix_alloc(2, n2);
  o2 = initialize_o(o2, n2);
  int compteur2 = 0;
  for(int k = 0; k < 2; k++)
  {
    for(int l = 0; l < (int) n2; l++)
    {
      if (gsl_spmatrix_get(o_test2, k, l) != gsl_spmatrix_get(o2, k, l))
      {
        compteur2++;
        printf("%d %d %d &&& %d %d %d\n", k, l, (int) gsl_spmatrix_get(o_test2, k, l), k, l, (int) gsl_spmatrix_get(o2, k, l));
      }
    }
  }
  gsl_spmatrix_free(o_test2);
  gsl_spmatrix_free(o2);
  assert(compteur2 == 0);
  // 3e test pour un impair
  /*
  size_t n3 = 81;
  gsl_spmatrix* o_test3;
  o_test3 = gsl_spmatrix_alloc(2, n3);
  int gsl_spmatrix_set_zero(gsl_spmatrix * o_test3);
  for(int i = 0; i < ; i++)
  {
    gsl_spmatrix_set(o_test2, 0, i, 1);
  }
  for(int i = n2 - 1; i > (int) n2 - 4; i--)
  {
    gsl_spmatrix_set(o_test2, 0, i, 1);
  }
  for(int j = 4; j < (int) n2 - 3; j = j + 4)
  {
    gsl_spmatrix_set(o_test2, 1, j, 1);
  }
  for(int j = 3; j < (int) n2 - 3; j = j + 4)
  {
    gsl_spmatrix_set(o_test2, 1, j, 1);
  }
  gsl_spmatrix* o2;
  o2= gsl_spmatrix_alloc(2, n2);
  o2 = initialize_o(o2, n2);
  int compteur2 = 0;
  for(int k = 0; k < 2; k++)
  {
    for(int l = 0; l < (int) n2; l++)
    {
      if (gsl_spmatrix_get(o_test2, k, l) != gsl_spmatrix_get(o2, k, l))
      {
        compteur2++;
        printf("%d %d %d &&& %d %d %d\n", k, l, (int) gsl_spmatrix_get(o_test2, k, l), k, l, (int) gsl_spmatrix_get(o2, k, l));
      }
    }
  }
  gsl_spmatrix_free(o_test2);
  gsl_spmatrix_free(o2);
  assert(compteur2 == 0);*/
  printf("test_initialize_o..\033[0;32mPASSED\033[0m\n");
}

/*
void test_initialize_hex()
{
  size_t n = 64;
  struct graph_t* G_test = malloc(sizeof(struct graph_t));
  G_test->t=gsl_spmatrix_alloc(n,n);
  G_test->o=gsl_spmatrix_alloc(2,n);
  G_test->num_vertices=n;
  int compteur = 0;
  assert(compteur == 0);
  printf("test_initialize_hex..\033[0;32mPASSED\033[0m\n");
}*/

void test_graph_initialize()
{
  size_t n = 6;
  struct graph_t* graph1 = NULL;
  graph1 = graph_initialize(n*n, 'c');
  struct graph_t* graph2 = NULL;
  graph2 = graph_initialize(n*n, 'h');
  printf("test_graph_initialize..\033[0;32mPASSED\033[0m\n");
  graph_free(graph1);
  graph_free(graph2);
}

void test_graph_add_move()
{
  size_t  n = 10;
  struct graph_t* graph1 = NULL;
  graph1 = graph_initialize(n*n, 'c');
  struct move_t move;
  move.m = 9;
  move.c = 1;
  graph_add_move(graph1, move);
  assert(gsl_spmatrix_get(graph1->o, move.c, move.m) == 1);

  struct graph_t* graph2 = NULL;
  graph2 = graph_initialize(n*n, 'h');
  graph_add_move(graph2, move);
  assert(gsl_spmatrix_get(graph2->o, move.c, move.m) == 1);
  
  printf("test_graph_add_move..\033[0;32mPASSED\033[0m\n");

  graph_free(graph1);
  graph_free(graph2);
}

void test_DFS()
{
  size_t n = 6;
  struct graph_t* graph1 = NULL;
  graph1 = graph_initialize(n*n, 'c');
  int b = DFS(graph1, BLACK);
  int w = DFS(graph1, WHITE);
  assert((b == 0) && (w == 0));
  
  for (size_t i = n; i <= 2*n-1; i++)
    gsl_spmatrix_set(graph1->o, WHITE, i, 1);
  //graph_display(graph1, 'c');
  b = DFS(graph1, BLACK);
  w = DFS(graph1, WHITE);
  assert((b == 0) && (w == 1));
  
  struct graph_t* graph2 = NULL;
  graph2 = graph_initialize(n*n, 'c');
  gsl_spmatrix_set(graph2->o, BLACK, n+2, 1);
  gsl_spmatrix_set(graph2->o, BLACK, n+2+n, 1);
  gsl_spmatrix_set(graph2->o, BLACK, n+2+n+1, 1);
  gsl_spmatrix_set(graph2->o, BLACK, n+2+n+1+n, 1);
  gsl_spmatrix_set(graph2->o, BLACK, n+2+n+1+n+n, 1);
  //graph_display(graph2, 'c');
  b = DFS(graph2, BLACK);
  w = DFS(graph2, WHITE);
  assert((b == 1) && (w == 0));

  printf("test_DFS..\033[0;32mPASSED\033[0m\n");

  graph_free(graph1);
  graph_free(graph2);
}
