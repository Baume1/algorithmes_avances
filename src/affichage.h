#ifndef H_AFFICHAGE
#define H_AFFICHAGE
#include "main.h"

/**
 * @brief Retourne à la ligne et réinitialise la position à 0.
 */
void retour_ligne();

/**
 * @brief Dessine la bordure supérieure ou inférieure de la fenêtre de rendu.
 */
void limite_fenetre();

/**
 * @brief Dessine la bordure supérieure de la fenêtre de rendu et décrémente la taille de la fenêtre actuelle.
 */
void ouvrir_fenetre();

/**
 * @brief Dessine la bordure inférieure de la fenêtre de rendu et incrémente la taille de la fenêtre actuelle.
 */
void fermer_fenetre();

/**
 * @brief Complète la ligne actuelle avec des espaces et dessine la bordure latérale droite de la fenêtre.
 */
void finaliser_ligne();

/**
 * @brief Dessine les bordures latérales gauches de la fenêtre et les tabulations avant le début de la ligne.
 */
void debuter_ligne();

/**
 * @brief Insère un mot dans la fenêtre de rendu, en majuscules si nécessaire.
 * @param mot La chaîne de caractères représentant le mot à insérer.
 */
void inserer_mot(char *mot);

/**
 * @brief Traite un nœud de l'arbre en fonction de son type et de sa valeur.
 * @param noeud Pointeur vers le nœud à traiter.
 */
void traiter_noeud(t_noeud *noeud);

/**
 * @brief Rend le texte représenté par l'arbre en parcourant récursivement tous les nœuds.
 * @param noeud_a_parcourir Pointeur vers le nœud racine à partir duquel parcourir l'arbre.
 */
void rendre_texte(t_noeud *noeud_a_parcourir);

#endif