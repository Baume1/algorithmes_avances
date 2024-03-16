#ifndef TERMINAUX_H
#define TERMINAUX_H

#include "main.h"

/**
 * @brief Initialise la lecture du fichier.
 */
void amorcer();

/**
 * @brief Lit le prochain caractère du fichier ouvert.
 */
void lire_caractere();

/**
 * @brief Vérifie si le caractère courant correspond au terminal donné et avance le curseur.
 * @param terminal : char Le caractère terminal attendu.
 */
void consommer_terminal(char terminal);

/**
 * @brief Avance le curseur jusqu'au prochain caractère non-espace.
 */
void passer_espaces();

/**
 * @brief Lit la balise courante dans le fichier.
 */
void lire_balise();

/**
 * @brief Vérifie si la balise courante correspond à celle attendue.
 * @param nom Le nom de la balise attendue.
 */
void valider_balise(char *nom);

/**
 * @brief Lit et valide la balise courante.
 * @param nom : char* Le nom de la balise attendue.
 */
void lire_et_valider_balise(char *nom);

/**
 * @brief Remplace le nom de la balise courante par celui fourni.
 * @param nom : char* Le nouveau nom pour la balise courante.
 */
void ecraser_balise(char *nom);

/**
 * Attribue une nouvelle valeur à la balise courante.
 * @param valeur : char* La nouvelle valeur pour la balise.
 */
void ecraser_tag_value(char *valeur);

#endif