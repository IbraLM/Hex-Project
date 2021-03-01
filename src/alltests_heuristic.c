#include "tests_heuristic.h"

int main()
{
  test_path_empty();
  test_path_realloc();
  test_empty_index();
  test_path_add();
  test_get_player_name();
  test_propose_opening();
  test_minDistance();
  test_get_shortest_path();
  test_update1_graph();
  test_path_score();
  test_nombre_de_libre();
  tests_heuristic();
  test_maxi();
  test_mini();
  test_is_empty();
  test_intersect();
  test_min_max();
  test_best_move();
  test_play();
  test_finalize();
  return 0;
}
