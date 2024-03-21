#ifndef H_MAIN
#define H_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern FILE *mon_fichier;
extern char curr_char;

extern char curr_tag[81];
extern char tag_value[81];

extern t_noeud racine;
extern t_noeud* curr_node;

typedef struct s_noeud{
    char nom_balise[81]; // Potentiel problème (les VLA se free tous seuls), à vérifier si malloc n'est pas plus judicieux
    char valeur_balise[81]; // Potentiel problème (les VLA se free tous seuls), à vérifier si malloc n'est pas plus judicieux

    struct s_noeud* gd_frere; // = noeud précédent au même niveau
    struct s_noeud* pt_frere; // = noeud suivant au même niveau

    struct s_noeud* pere; // = le noeud un cran supérieur
    struct s_noeud* fils; // = le noeud un cran inférieur
}t_noeud;


#endif