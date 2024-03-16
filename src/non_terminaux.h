#ifndef NON_TERMINAUX_H
#define NON_TERMINAUX_H

#include "main.h"
#include "terminaux.h"

/**
 * @brief Traite les annexes du document.
 * Valide un pattern de la forme <annexe> {<contenu>} </annexe> en boucle jusqu'à la fin du fichier.
 * Le détail du contenu est géré par la fonction contenu().
 */
void annexes();

/**
 * @brief Analyse le corps principal du document NanoML.
 * Valide la structure <document> {contenu} </document>, où le contenu est défini par la fonction contenu().
 */
void document();

/**
 * @brief Point d'entrée pour l'analyse d'un texte enrichi.
 * Enchaîne l'analyse d'un document et de ses annexes potentielles en utilisant les fonctions document() et annexes().
 */
void texte_enrichi();

/**
 * @brief Gère le contenu interne d'un élément de document ou d'annexe.
 * Itère sur les éléments internes possibles tels que les sections, titres, mots enrichis, et listes.
 */
void contenu();

/**
 * @brief Analyse une section du document.
 * Valide la structure <section> {<contenu>} </section> et gère le contenu interne avec la fonction contenu().
 */
void section();

/**
 * @brief Convertit le texte du titre en majuscules pour l'affichage.
 */
void titre();

/**
 * @brief Analyse les listes dans le document.
 * Valide un pattern de la forme <liste> {<item>} </liste> et itère sur chaque élément avec la fonction item().
 */
void liste();

/**
 * @brief Traite un élément de liste NanoML.
 * Gère les éléments formatés en <item> {contenu} </item>, incluant le texte, les listes et les listes imbriquées.
 */
void item();

/**
 * @brief Gère la combinaison liste suivie de texte dans un élément de liste.
 * Cette structure permet la récursivité des listes et du texte.
 */
void liste_texte();

/**
 * @brief Gère la combinaison texte suivi d'une liste dans un élément de liste.
 * Permet une structure récursive de texte et listes.
 */
void texte_liste();

/**
 * @brief Analyse une suite de mots ou éléments enrichis dans le document.
 * Itère sur des mots enrichis, pouvant être simples ou importants, jusqu'à rencontrer une nouvelle balise.
 */
void texte();

/**
 * @brief Traite un mot dans le texte, qui peut être simple ou marqué comme important.
 * Dirige vers mot_important() si le mot est dans une balise d'importance, sinon traite comme mot_simple().
 */
void mot_enrichi();

/**
 * @brief Traite une séquence de mots simples marqués comme importants.
 * Valide et traite une structure répétitive de la forme <important> {<mot_simple>} </important>, en bouclant sur chaque <mot_simple>.
 */
void mot_important();

/**
 * @brief Lit et traite un mot simple du texte.
 * Capture la chaîne de caractères jusqu'à un espace ou une nouvelle balise.
 */
void mot_simple();

#endif