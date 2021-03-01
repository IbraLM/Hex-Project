#include <dlfcn.h>
#include <assert.h>

#include "player-load.h"

struct player player_open(char * filename){
    struct player p;
    p.handle=dlopen(filename,RTLD_LAZY);//charger le jouer de la bibliotheque donnée par filename
    assert(p.handle != NULL);//vérifier si le chargement a été bien éffectué
    p.get_player_name=dlsym(p.handle,"get_player_name");
    p.propose_opening = dlsym(p.handle,"propose_opening");
    p.accept_opening  = dlsym(p.handle,"accept_opening");
    p.initialize_color = dlsym(p.handle,"initialize_color");
    p.initialize_graph = dlsym(p.handle,"initialize_graph");
    p.play = dlsym(p.handle,"play"); 
    p.finalize = dlsym(p.handle,"finalize");  
    return p;
}

//cette fonction initialise un joueur en chargeant ses fontions depuis sa bib dynamique

//décharger la bib dynamique 
int player_close(struct player p){
 
 
  return dlclose(p.handle);
  
  
 
}

