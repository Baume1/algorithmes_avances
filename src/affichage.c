#include "affichage.h"

const int taille_fenetre = 50;
int fenetre_actu = taille_fenetre;

int position = 0;
int tabulations = 0;

int est_important = 0;

void retour_ligne()
{
    printf("\n"); // On retourne à la ligne
    position = 0; // On réinitialise la position à 0
}

void limite_fenetre()
{
    for (position; position < taille_fenetre - fenetre_actu; position++) // On met autant de "|" que le décalage
    {
        printf("|");
    }
    printf("+");                                        // On dessine le coin gauche
    for (position; position < fenetre_actu; position++) // On met autant de tirets que la taille de la fenêtre actuelle§/qu'on dessine
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
        if (est_important)
        {
            if (mot[cpt_mot] >= 'a' && mot[cpt_mot] <= 'z')
            {
                printf("%c", mot[cpt_mot] - 32); // Pour convertir en majuscule
            }
            else
            {
                printf("%c", mot[cpt_mot]);
            }
        }
        else
        {
            printf("%c", mot[cpt_mot]);
        }
        cpt_mot++;
        position++;
    }
    printf(" "); // On laisse un espace pour un nouveau mot
    position++;
}

void traiter_noeud(t_noeud *noeud)
{
    // J'aurais dû utiliser un enum...
    if (!strcmp(noeud->nom_balise, "mot"))
    {
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
        if (noeud->fils == NULL)
        {
            finaliser_ligne();
        }
    }
    else if (!strcmp(noeud->nom_balise, "document") || !strcmp(noeud->nom_balise, "annexe") || !strcmp(noeud->nom_balise, "section"))
    {
        ouvrir_fenetre();
        debuter_ligne();
    }
    else if (!strcmp(noeud->nom_balise, "/document") || !strcmp(noeud->nom_balise, "/annexe") || !strcmp(noeud->nom_balise, "/section"))
    {
        fermer_fenetre();
    }
    else if (!strcmp(noeud->nom_balise, "titre") || !strcmp(noeud->nom_balise, "important"))
    {
        est_important = 1;
    }
    else if (!strcmp(noeud->nom_balise, "/titre") || !strcmp(noeud->nom_balise, "/important"))
    {
        finaliser_ligne();
        est_important = 0;
    }
    else if (!strcmp(noeud->nom_balise, "item"))
    {
        printf("#  ");
        position += 3;
    }
    else if (!strcmp(noeud->nom_balise, "/item"))
    {
        finaliser_ligne();
        debuter_ligne();
    }
    else if (!strcmp(noeud->nom_balise, "liste"))
    {
        debuter_ligne();
        tabulations += 2;
    }
    else if (!strcmp(noeud->nom_balise, "/liste"))
    {
        finaliser_ligne();
        tabulations -= 2;
    }
    else if (!strcmp(noeud->nom_balise, "br/"))
    {
        finaliser_ligne();
        debuter_ligne();
    }
}

void rendre_texte(t_noeud *noeud_a_parcourir)
{
    traiter_noeud(noeud_a_parcourir);
    if (noeud_a_parcourir->fils != NULL)
    {
        rendre_texte(noeud_a_parcourir->fils);
    }
    if (noeud_a_parcourir->pt_frere != NULL)
    {
        rendre_texte(noeud_a_parcourir->pt_frere);
    }
}