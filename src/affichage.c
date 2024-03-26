#include "main.h"

const int taille_fenetre = 50;
int fenetre_actu = taille_fenetre;

int position = 0;
int tabulations = 0;

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
}
