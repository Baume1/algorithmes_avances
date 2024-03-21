#include "main.h"
#include "arbre.h"

void initialiser_arbre(){
    curr_node = malloc(sizeof(t_noeud));

    strcpy(curr_node->nom_balise, "texte_enrichi");
    strcpy(curr_node->valeur_balise, "");

    curr_node->fils = NULL;
    curr_node->pt_frere = NULL;
    curr_node->gd_frere = NULL;

    racine = curr_node;

    racine->fils = curr_node;
    curr_node->pere = racine;
}

void liberer_arbre(t_noeud racine){
    // À voir
}

void remonter_noeuds(char* nom_balise){
    while(!strcmp(curr_node->pere->nom_balise, nom_balise)){
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
    // On fait la manipulation avec le noeud actuel
    if(curr_node->fils == NULL){
        // On lui ajoute le nouveau noeud comme fils si il n'a pas de fils
        new_node->pere = curr_node;
        curr_node->fils = curr_node;
    }
    else{
        // Sinon on lui ajoute comme frère
        new_node->gd_frere = curr_node;
        curr_node->pt_frere = new_node;
    }
    curr_node = new_node;
}

void ajouter_noeud(){
    t_noeud* nv_noeud = malloc(sizeof(t_noeud));

    strcpy((nv_noeud->nom_balise), curr_tag);
    strcpy((nv_noeud->valeur_balise), tag_value);

    nv_noeud->fils = NULL;
    nv_noeud->pere = NULL;
    nv_noeud->gd_frere = NULL;
    nv_noeud->pt_frere = NULL;

    maj_curr_node(nv_noeud);
}

void maj_arbre(){
    if(!strcmp(curr_tag, "mot")){
        ajouter_noeud();
    }else if(!strcmp(curr_tag, "br/")){
        ajouter_noeud();
        remonter_noeuds("mot");
    }else{
        if(!strcmp(curr_node->nom_balise, "mot")){
            remonter_noeuds("mot");
        }

        if(curr_tag[0] == '/'){
            remonter_pere();
        }else{
            ajouter_noeud();
        }
    }

    // afficher_noeud_actuel();
}

void afficher_noeud_actuel(){
    printf("\n\nAdresse du noeud : %X\nBalise du noeud : %s\nValeur de la balise : %s\nSon pere : %X\nSon fils : %X\nSon gd frere : %X\nSon pt frere : %X\n\n", curr_node, curr_node->nom_balise, curr_node->valeur_balise, curr_node->pere, curr_node->fils, curr_node->gd_frere, curr_node->pt_frere);
}

void parcourir_arbre(t_noeud* node){
    afficher_noeud_actuel();
    if(node->fils != NULL){
        node = node->fils;
        parcourir_arbre(node);
    }else if(node->pt_frere != NULL){
        node->pt_frere;
        parcourir_arbre(node);
    }
}

void afficher_arbre(){
    t_noeud* local_node = racine;
    parcourir_arbre(local_node);
}