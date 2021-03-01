GSL_PATH?=/opt/gsl-2.6/lib
CFLAGS=-Wall -Wextra -std=c99 -I $(GSL_PATH)/include

LDFLAGS=-L $(GSL_PATH)/lib -ldl -lgsl -lgslcblas -lm

all: build test

build: server hero.so hero2.so bridge.so heeuristic.so heeuristic1.so

test: build alltests_player.o alltests_graph.o alltests_heuristic.o tests_player.o tests_my-graph.o tests_heuristic.o
	$(CC) $(CFLAGS) -rdynamic --coverage -g -O0 -lgcov alltests_player.o tests_player.o  my-graph.o player.o -o alltests_player $(LDFLAGS)
	$(CC) $(CFLAGS) -rdynamic --coverage -g -O0 -lgcov alltests_graph.o  tests_my-graph.o  my-graph.o -o alltests_graph $(LDFLAGS)
	$(CC) $(CFLAGS) -rdynamic --coverage -g -O0 -lgcov alltests_heuristic.o tests_heuristic.o my-graph.o heuristic.o -o alltests_heuristic $(LDFLAGS)

install: build test
	cp server install && cp *.so install && cp alltests_player install && cp alltests_heuristic install && cp alltests_graph install

clean:
	rm -f *.o *.~ *.so *.gcno alltests_player alltests_graph alltests_heuristic server && cd install/ && rm -f *.o *.~ *.so *.gcno alltests_player alltests_graph alltests_heuristic server

my-graph.o: src/my-graph.h src/my-graph.c src/graph.h src/move.h
	$(CC) $(CFLAGS) -c -fPIC -g src/my-graph.c

player.o: src/player.c src/player.h src/move.h src/graph.h src/my-graph.h
	$(CC) $(CFLAGS) -c -fPIC src/player.c

heuristic.o: src/heuristic.c src/heuristic.h src/player.h src/move.h src/graph.h src/my-graph.h
	$(CC) $(CFLAGS) -c -fPIC src/heuristic.c

heuristic1.o: src/heuristic1.c src/player.h src/move.h src/graph.h src/my-graph.h
	$(CC) $(CFLAGS) -c -fPIC src/heuristic1.c	

player2.o: src/player2.c src/player.h src/move.h src/graph.h src/my-graph.h
	$(CC) $(CFLAGS) -c -fPIC src/player2.c

two-bridge.o: src/two-bridge.c src/player.h src/move.h src/graph.h src/my-graph.h
	$(CC) $(CFLAGS) -c -fPIC src/two-bridge.c

player-load.o: src/player-load.c src/player-load.h
	$(CC) $(CFLAGS) -c -g src/player-load.c

server.o: src/server.c src/move.h src/my-graph.h src/player-load.h
	$(CC) $(CFLAGS) -c src/server.c

hero.so: player.o my-graph.o
	$(CC) $(CFLAGS) -shared player.o my-graph.o -o hero.so $(LDFLAGS)


heeuristic1.so: heuristic1.o my-graph.o
	$(CC) $(CFLAGS) -shared heuristic1.o my-graph.o -o heeuristic1.so $(LDFLAGS)

heeuristic.so: heuristic.o my-graph.o
	$(CC) $(CFLAGS) -shared heuristic.o my-graph.o -o heeuristic.so $(LDFLAGS)

hero2.so: player2.o my-graph.o
	$(CC) $(CFLAGS) -shared player2.o my-graph.o -o hero2.so $(LDFLAGS)

bridge.so: two-bridge.o my-graph.o
	$(CC) $(CFLAGS) -shared two-bridge.o my-graph.o -o bridge.so $(LDFLAGS)

server: server.o my-graph.o player-load.o
	$(CC) $(CFLAGS) -rdynamic --coverage -g -O0 -o server my-graph.o player-load.o  server.o $(LDFLAGS)

tests_player.o: src/tests_player.c src/player.c src/player.h src/move.h src/my-graph.h
	$(CC) $(CFLAGS) -c src/tests_player.c

tests_heuristic.o: src/tests_heuristic.c src/heuristic.h src/move.h src/my-graph.h
	$(CC) $(CFLAGS) -c src/tests_heuristic.c

tests_my-graph.o: src/tests_my-graph.c src/my-graph.h src/player.h src/move.h src/graph.h src/tests_my-graph.h
	$(CC) $(CFLAGS) -c src/tests_my-graph.c

alltests_player.o: src/alltests_player.c src/tests_player.h
	$(CC) $(CFLAGS) -c -rdynamic --coverage -g -O0 -lgcov src/alltests_player.c

alltests_graph.o: src/alltests_graph.c  src/tests_my-graph.h
	$(CC) $(CFLAGS) -c -rdynamic --coverage -g -O0 -lgcov src/alltests_graph.c

alltests_heuristic.o: src/alltests_heuristic.c src/tests_heuristic.h
	$(CC) $(CFLAGS) -c -rdynamic --coverage -g -O0 -lgcov src/alltests_heuristic.c
