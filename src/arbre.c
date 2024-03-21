#include "main.h"

void initialiser_arbre(){
    strcpy(racine.nom_balise, curr_tag);
    racine.valeur_balise = NULL;

    racine.pere = NULL;

    racine.gd_frere = NULL;
    racine.pt_frere = NULL;

    racine.fils = NULL;
}

void liberer_arbre(t_noeud racine){
    // À voir
}

void remonter_noeuds(char* nom_balise){
    while(!strcmp(curr_node->nom_balise, nom_balise)){
        curr_node = curr_node->pere;
    }
}

void remonter_pere(){
    if(curr_node->pere == NULL && curr_node->gd_frere != NULL){
        curr_node = curr_node->gd_frere;
        remonter_pere();
    }else if(curr_node->pere != NULL){
        curr_node = curr_node->pere;
    }else{
        printf("Le pere et grand frere n'existent pas");
    }
}

void liberer_noeud(t_noeud* noeud){
    free(racine);
}

void maj_curr_node(t_noeud* new_node){
    // Pour éventuellement faire un traitement plus complexe
    if(curr_node->fils != NULL){
        // On fait la manipulation avec le noeud actuel
        new_node->pere = curr_node;
        curr_node->fils = curr_node;
    }
    else{
        new_node->gd_frere = curr_node;
        curr_node->pt_frere = new_node;
    }
    curr_node = new_node;
}

void ajouter_noeud(){
    t_noeud* nv_noeud = (t_noeud*)malloc(sizeof(t_noeud));
    strcpy(*(nv_noeud->nom_balise), curr_tag);
    strcpy(*(nv_noeud->valeur_balise), tag_value);

    nv_noeud->fils = NULL;
    nv_noeud->gd_frere = NULL;
    nv_noeud->pt_frere = NULL;

    maj_curr_node(nv_noeud);
}