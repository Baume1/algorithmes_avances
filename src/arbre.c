#include "main.h"

void initialiser_arbre(){
    strcpy(racine.nom_balise, curr_tag);

    racine.gd_frere = NULL;
    racine.pt_frere = NULL;

    racine.fils = NULL;
}

void liberer_racine(t_noeud* racine){
    free(racine);
}

void ajouter_noeud(){
    
}