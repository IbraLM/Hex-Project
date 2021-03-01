#  Hex Project 

* **Qu'est-ce que c'est ?**
L'objectif de ce projet, est d'implémenter un ensemble de fonctions qui permettent de faire jouer deux joueurs à une partie du jeu Hex. Ainsi, ce code contient deux types de fonctions :

1. Fonctions qui définissent des joueurs automatiques (clients).

2. Fonctions qui implémente un serveur qui s'occupe de l'organisation du jeu.

* Le code est écrit en langage C.

# Architecture des fichiers :

*  **Makefile**
*  **src/** : Contient tous les fichiers sources.
*  **install/** : Répertoire d'installation (vide au début).
*  **rapport/** : Contient le rapport de notre projet.
 

# Makefile : 
Contient plusieurs règles :
1. **build** : Compile l'ensemble du code.
2. **test** : Compile les tests.
3. **install** : Copie les exécutables (server, alltests_graph, alltests_heuristic, alltests_player, bridge.so, heeuristic1.so, heeuristic.so, hero2.so et hero.so).
4. **clean** : Supprime les fichiers compilés et insatallés.

# Instructions :

Vous pouvez charger l'ensemble des clients de manière dynamique avec la commande :

**./install/server -m [M] -t [T] ./install/client1.so ./install/client2.so**

* L'option **-m** permet de spécifier la largeur du plateau.
* L'option **-t** permet de choisir la forme du plateau de jeu :
  * **-c** : grille carée.
  * **-h** : grille hexagonale.

Voici la liste des clients disponibles :
1. hero.so
2. hero2.so 
3. bridge.so
4. heeuristic.so
5. heeuristic1.so