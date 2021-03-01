#include "tests_my-graph.h"

int main()
{
  test_nb__empty();
  test_nb__realloc();
  test_nb__add();
  test_get_neighbours();
  test_initialize_carre();
  test_graph_initialize();
  test_graph_add_move();
  test_DFS();
  test_initialize_o();
  return 0;
}
