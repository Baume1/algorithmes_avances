#ifndef TERMINAUX_H
#define TERMINAUX_H

#include "main.h"

/*
   Initialise le processus de lecture du fichier.
*/
void amorcer();

/*
   Lit le prochain caractère du fichier ouvert.
*/
void lire_caractere();

/**
 *  Vérifie si le caractère courant correspond au terminal donné et avance le curseur.
 * @param terminal Le caractère terminal attendu.
 */
void consommer_terminal(char terminal);

/*
   Avance le curseur jusqu'au prochain caractère non-espace.
*/
void passer_espaces();

void lire_balise();
void valider_balise(char *nom);
void lire_et_valider_balise(char *nom);
void ecraser_balise(char *nom);
void ecraser_tag_value(char *valeur);

#endif