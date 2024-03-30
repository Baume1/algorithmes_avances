#ifndef H_ARBRE
#define H_ARBRE

/**
 * @brief Initialise l'arbre en créant un nœud racine avec la balise "texte_enrichi".
 */
void initialiser_arbre();

/**
 * @brief Remonte dans l'arbre jusqu'au nœud le plus proche ayant le même nom de balise que celui passé en paramètre.
 * @param nom_balise Nom de la balise à rechercher.
 */
void remonter_noeuds_eg(char *nom_balise);

/**
 * @brief Remonte dans l'arbre jusqu'au nœud le plus proche ayant un nom de balise différent de celui passé en paramètre.
 * @param nom_balise Nom de la balise à exclure.
 */
void remonter_noeuds_ineg(char *nom_balise);

/**
 * @brief Remonte jusqu'au nœud parent du nœud courant. Si le nœud courant n'a pas de parent, alors on remonte récursivement les grands frères jusqu'à arriver au père.
 */
void remonter_pere();

/**
 * @brief Met à jour le nœud courant en ajoutant le nouveau nœud passé en paramètre comme fils ou frère du nœud courant.
 * @param new_node Pointeur vers le nouveau nœud à ajouter.
 */
void maj_curr_node(t_noeud *new_node);

/**
 * @brief Ajoute un nouveau nœud à l'arbre avec les valeurs de curr_tag et tag_value.
 */
void ajouter_noeud();

/**
 * @brief Met à jour l'arbre en fonction des balises rencontrées.
 */
void maj_arbre();

/**
 * @brief Affiche les informations du nœud courant dans la console.
 */
void afficher_noeud_actuel();

/**
 * @brief Sauvegarde l'arbre dans un fichier "arbre_json.txt" au format JSON.
 */
void sauvegarder();

/**
 * @brief Sauvegarde un nœud donné dans le fichier de sauvegarde selon un format JSON.
 * @param noeud_a_sauvegarder Pointeur vers le nœud à sauvegarder.
 */
void sauvegarder_noeud(t_noeud *noeud_a_sauvegarder);

/**
 * @brief Sauvegarde récursivement tous les nœuds de l'arbre dans le fichier de sauvegarde.
 * @param noeud_a_parcourir Pointeur vers le nœud à partir duquel parcourir l'arbre.
 */
void sauvegarder_arbre(t_noeud *noeud_a_parcourir);

/**
 * @brief Affiche les informations d'un nœud donné dans la console.
 * @param noeud_a_afficher Pointeur vers le nœud à afficher.
 */
void afficher_noeud(t_noeud *noeud_a_afficher);

/**
 * @brief Affiche récursivement tous les nœuds de l'arbre dans la console.
 * @param noeud_a_parcourir Pointeur vers le nœud à partir duquel parcourir l'arbre.
 */
void afficher_arbre(t_noeud *noeud_a_parcourir);

/**
 * @brief Libère récursivement la mémoire allouée pour tous les nœuds de l'arbre.
 * @param noeud_a_parcourir Pointeur vers le nœud à partir duquel parcourir l'arbre.
 */
void liberer_arbre(t_noeud *noeud_a_parcourir);

#endif