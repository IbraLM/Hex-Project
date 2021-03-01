#ifndef PLAYER_LOAD_H
#define PLAYER_LOAD_H

#include "move.h"
#include "graph.h"

struct player {
    char const* (*get_player_name)();
    struct move_t (*propose_opening)();
    int (*accept_opening)(const struct move_t);
    void (*initialize_graph)(struct graph_t*);
    void (*initialize_color)(enum color_t);
    struct move_t (*play)(struct move_t);
    void (*finalize)();
    void * handle;
};

struct player player_open(char * filename);
void initialize_player(struct player* p);
int player_close(struct player p);

#endif // PLAYER_LOAD_H
