#ifndef TERMINAUX_H
#define TERMINAUX_H

#include "main.h"

/**
 * @brief Ouvre un fichier en mode lecture et initialise le processus de lecture de caractères.
 * @param nom_fichier Le nom du fichier à ouvrir.
 */
void amorcer(char *nom_fichier);

/**
 * @brief Lit le prochain caractère du fichier ouvert.
 */
void lire_caractere();

/**
 * @brief Consomme un caractère terminal si celui-ci correspond au caractère actuel.
 * @param terminal Le caractère terminal attendu.
 */
void consommer_terminal(char terminal);

/**
 * @brief Passe les espaces blancs dans le fichier.
 */
void passer_espaces();

/**
 * @brief Lit une balise XML/HTML et stocke son nom dans la variable curr_tag.
 */
void lire_balise();

/**
 * @brief Écrase le contenu de la variable curr_tag avec le nom de balise donné.
 * @param nom Le nom de la balise à écraser.
 */
void ecraser_balise(char *nom);

/**
 * @brief Valide si le nom de la balise actuelle correspond au nom donné.
 * @param nom Le nom de la balise attendue.
 */
void valider_balise(char *nom);

/**
 * @brief Lit et valide une balise avec le nom donné.
 * @param nom Le nom de la balise attendue.
 */
void lire_et_valider_balise(char *nom);

/**
 * @brief Écrase la valeur de la balise actuelle avec la valeur donnée.
 * @param valeur La nouvelle valeur de la balise.
 */
void ecraser_tag_value(char *valeur);

/**
 * @brief Affiche le nom et la valeur de la balise actuelle.
 */
void afficher_token();

#endif