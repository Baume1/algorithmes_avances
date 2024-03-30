#ifndef NON_TERMINAUX_H
#define NON_TERMINAUX_H

#include "main.h"
#include "terminaux.h"

/**
 * @brief Traite les annexes du document en lisant et validant les balises "annexe" et "/annexe".
 */
void annexes();

/**
 * @brief Traite le document principal en lisant et validant les balises "document" et "/document", puis appelle la fonction contenu().
 */
void document();

/**
 * @brief Traite le texte enrichi en appelant les fonctions document() et annexes().
 */
void texte_enrichi();

/**
 * @brief Traite le contenu du document ou d'une section en lisant et traitant les différentes balises rencontrées.
 */
void contenu();

/**
 * @brief Traite une section du document en lisant et validant les balises "section" et "/section", puis appelle la fonction contenu().
 */
void section();

/**
 * @brief Traite un titre en lisant et validant les balises "titre" et "/titre", puis appelle la fonction texte().
 */
void titre();

/**
 * @brief Traite une liste en lisant et validant les balises "liste" et "/liste", puis appelle la fonction item() pour chaque élément de la liste.
 */
void liste();

/**
 * @brief Traite un élément de liste en lisant et validant les balises "item" et "/item", puis appelle soit liste_texte() soit texte_liste() selon le contenu de l'élément.
 */
void item();

/**
 * @brief Traite le contenu d'un élément de liste qui contient une sous-liste en appelant récursivement les fonctions liste() et texte_liste().
 */
void liste_texte();

/**
 * @brief Traite le contenu textuel d'un élément de liste en appelant récursivement les fonctions texte() et liste_texte().
 */
void texte_liste();

/**
 * @brief Traite un bloc de texte en appelant la fonction mot_enrichi() pour chaque mot rencontré.
 */
void texte();

/**
 * @brief Traite un mot en appelant soit mot_important() soit mot_simple() selon le contenu.
 */
void mot_enrichi();

/**
 * @brief Traite un mot important en lisant et validant les balises "important" et "/important", puis appelle la fonction mot_simple() pour chaque mot.
 */
void mot_important();

/**
 * @brief Traite un mot simple en lisant les caractères jusqu'à rencontrer un espace ou la fin du fichier, puis écrase la balise "mot" avec la valeur lue.
 */
void mot_simple();

#endif