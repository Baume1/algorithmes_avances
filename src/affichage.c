#include "affichage.h"

#define taille_fenetre 50 // Taille maximale de la fenêtre
int fenetre_actu = taille_fenetre; // Taille de la fenêtre actuelle

int position = 0; // On démarre à 0
int tabulations = 0; // Aucune tabulation au début du document

int est_important = 0; // Par défaut, toutes les lettres sont en minuscules

void retour_ligne()
{
    printf("\n"); // On retourne à la ligne
    position = 0; // On réinitialise la position à 0
}

void limite_fenetre()
{
    for (position; position < taille_fenetre - fenetre_actu; position++) // On met autant de "|" que le décalage l'ordonne
    {
        printf("|");
    }
    printf("+");                                        // On dessine le coin gauche
    for (position; position < fenetre_actu; position++) // On met autant de tirets que la taille de la fenêtre actuelle qu'on dessine
    {
        printf("-");
    }
    printf("+");                                          // On dessine le coin droit
    for (position; position < taille_fenetre; position++) // On finalise avec le même qu'au début
    {
        printf("|");
    }
    retour_ligne(); // On retourne à la ligne et réinitialise la position
}

void ouvrir_fenetre()
{
    limite_fenetre();  // On dessine la bordure haute de la fenêtre
    fenetre_actu -= 1; // +1 pour le décalage
}

void fermer_fenetre()
{
    fenetre_actu += 1; // +1 pour le décalage
    limite_fenetre();  // On dessine la bordure basse de la fenêtre
}

void finaliser_ligne()
{
    // Combler avec des espaces, il faut taille_fenetre_max - 2 * nb__sous-fenêtres espaces
    for (position; position <= fenetre_actu + 1; position++) // = fenêtre_actu + 1 nous donne le résultat du "calcul" précédent
    {
        printf(" ");
    }
    // Finir la bordure de la fenêtre
    for (position + 1; position <= taille_fenetre + 1; position++) // Pareil ici sauf qu'ici on va jusqu'à la taille maximale
    {
        printf("|");
    }
    retour_ligne(); // Puis on retourne à la ligne (et réinitialise la position également)
}

void debuter_ligne()
{
    // Chaque début de ligne est constitué d'un certain nombre de "|" selon le nombre de décalages/fenêtres
    for (position; position < taille_fenetre - fenetre_actu; position++)
    {
        printf("|");
    }
    // On décale selon le nombre de décalage
    for (position; position < taille_fenetre - fenetre_actu + tabulations; position++)
    {
        printf(" ");
    }
}

void inserer_mot(char *mot)
{
    size_t cpt_mot = 0;
    while (mot[cpt_mot] != '\0')
    {
        if (est_important) // Si le mot est important, on le met en majuscules
        {
            if (mot[cpt_mot] >= 'a' && mot[cpt_mot] <= 'z') // On vérifie si c'est une lettre et qu'elle est bien minuscule
            {
                printf("%c", mot[cpt_mot] - 32); // Pour convertir en majuscule
            }
            else // On l'ajoute sinon
            {
                printf("%c", mot[cpt_mot]);
            }
        }
        else // On ajoute juste le caractère dans le cas contraire
        {
            printf("%c", mot[cpt_mot]);
        }
        cpt_mot++; // Le compteur du mot
        position++; // Et la position est changée aussi
    }
    printf(" "); // On laisse un espace pour un nouveau mot
    position++; // On vient de mettre un espace donc on incrémente de 1 la position
}

void traiter_noeud(t_noeud *noeud)
{
    // J'aurais dû utiliser un enum...
    if (!strcmp(noeud->nom_balise, "mot") && strcmp(noeud->valeur_balise, "")) // Cas : mot non vide
    {
        if (noeud->pere != NULL)
        {
            if (strcmp(noeud->pere->nom_balise, "mot"))
            {
                debuter_ligne();
            }
        }
        else if (noeud->gd_frere != NULL)
        {
            debuter_ligne();
        }

        if (position + strlen(noeud->valeur_balise) + 1 < fenetre_actu)
        {
            inserer_mot(noeud->valeur_balise);
        }
        else
        {
            finaliser_ligne();
            debuter_ligne();
            inserer_mot(noeud->valeur_balise);
        }
        if (noeud->fils == NULL || strcmp(noeud->fils->nom_balise, "mot") && strcmp(noeud->fils->nom_balise, "br/"))
        {
            finaliser_ligne();
        }
    }
    else if (!strcmp(noeud->nom_balise, "document") || !strcmp(noeud->nom_balise, "annexe") || !strcmp(noeud->nom_balise, "section")) // Cas : début document, début annexe ou début section
    {
        ouvrir_fenetre();
        debuter_ligne();
    }
    else if (!strcmp(noeud->nom_balise, "/document") || !strcmp(noeud->nom_balise, "/annexe") || !strcmp(noeud->nom_balise, "/section")) // Cas : fin document, fin annexe ou fin section
    {
        fermer_fenetre();
    }
    else if (!strcmp(noeud->nom_balise, "titre") || !strcmp(noeud->nom_balise, "important")) // Cas : début titre ou début mot important
    {
        est_important = 1;
    }
    else if (!strcmp(noeud->nom_balise, "/titre") || !strcmp(noeud->nom_balise, "/important")) // Cas : fin titre ou fin mot important
    {
        est_important = 0;
    }
    else if (!strcmp(noeud->nom_balise, "item")) // Cas : début item
    {
        debuter_ligne(); // On débute la ligne avec le décalage
        printf("#  "); // Puis on ajoute le début de l'item
        position += 3; // Et on modifie la position en accord avec l'ajout effectué
    }
    else if (!strcmp(noeud->nom_balise, "liste")) // Cas : début liste
    {
        tabulations += 2; // On décale de 2 vers la droite
        debuter_ligne(); // Puis on dessine le début de la ligne
    }
    else if (!strcmp(noeud->nom_balise, "/liste")) // Cas : fin liste
    {
        tabulations -= 2; // On redécale vers la gauche
    }
    else if (!strcmp(noeud->nom_balise, "br/")) // Cas : retour à la ligne forcé
    {
        finaliser_ligne();
    }
}

void rendre_texte(t_noeud *noeud_a_parcourir)
{
    // On appelle la fonction qui gère le type de noeud et le traitement à effectuer
    traiter_noeud(noeud_a_parcourir);
    if (noeud_a_parcourir->fils != NULL) // On parcours tous les fils
    {
        rendre_texte(noeud_a_parcourir->fils);
    }
    if (noeud_a_parcourir->pt_frere != NULL) // Puis on parcours tous les fils des frères 
    {
        rendre_texte(noeud_a_parcourir->pt_frere);
    }
}