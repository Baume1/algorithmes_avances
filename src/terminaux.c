#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Pour la fonction isspace()

#include "terminaux.h"

void amorcer(char *nom_fichier)
{
    mon_fichier = fopen(nom_fichier, "r"); // On ouvre le fichier donné en paramètre en mode "read"
    if (mon_fichier == NULL)
    {
        printf("Fichier introuvable, verifiez que vous avez entre une extension\nLe creer malgre tout ?\n");
        int test = 0;
        (scanf("%d", &test) ? mon_fichier = fopen(nom_fichier, "w") : 0);
        exit(-1);
    }
    lire_caractere();
}

void lire_caractere()
{
    // fgetc() lit caractère par caractère le fichier donné en paramètre
    curr_char = fgetc(mon_fichier);
    // printf("%c", curr_char);
}

void consommer_terminal(char terminal)
{
    // On vérifie que le caractère en paramètre est le même que celui actuel
    if (terminal != curr_char)
    {
        // S'il ne l'est pas, on renvoie une erreur
        fprintf(stderr, "Erreur : caractere attendu : %c, caractere trouve : %c\n", terminal, curr_char);
        exit(1);
    }
    lire_caractere();
}

void passer_espaces()
{
    // Tant que le caractère actuel est un espace (cf doc de la fonction isspace()) on le passe
    while (isspace(curr_char) && curr_char != EOF)
    {
        lire_caractere();
    }
}

void lire_balise()
{
    strcpy(curr_tag, "");

    consommer_terminal('<'); // Si on lit une balise, elle commence par un "<"

    // On insère tous les caractères de la balise dans la variable curr_tag
    size_t cpt = 0;
    while (curr_char != '>')
    {
        curr_tag[cpt++] = curr_char;
        lire_caractere();
    }
    curr_tag[cpt] = '\0';    // On rajoute le \0 sinon la lecture ne fonctionne pas
    consommer_terminal('>'); // Si on lit une balise, elle finit par un ">"

    strcpy(tag_value, ""); // Si on lit une balise alors sa valeur est nulle

    if (utiliser_arbre)
    {
        maj_arbre(); // Pour ajouter le token à l'arbre
    }
    // afficher_token(); // A décommenter pour débugger le programme (aussi dans ecraser_balise())
}

void ecraser_balise(char *nom)
{
    // On réinitialise l'étiquette du token
    strcpy(curr_tag, "");

    // On insère tous les caractères du paramètre dans la variable curr_tag
    size_t cpt = 0;
    while (nom[cpt] != '\0')
    {
        curr_tag[cpt] = nom[cpt];
        cpt++;
    }
    curr_tag[cpt] = '\0'; // On rajoute le \0 car il est évité à cause du while

    if (utiliser_arbre)
    {
        maj_arbre(); // Pour ajouter le token à l'arbre
    }
    // afficher_token(); // A décommenter pour débugger le programme (aussi dans lire_balise())
}

void valider_balise(char *nom)
{
    // On vérifie que l'étiquette du token corresponde avec la valeur donnée en paramètre
    if (strcmp(curr_tag, nom))
    {
        // Comme consommer_terminal(), si ça ne correspond pas : on renvoie une erreur
        fprintf(stderr, "Mauvaise balise '%s', balise attendue : %s\n", curr_tag, nom);
        exit(2);
    }
}

void lire_et_valider_balise(char *nom)
{
    // Si la balise actuelle est bonne alors on évite de la passer (dans le cas où on utilise la balise précédente)
    if (strcmp(curr_tag, nom))
    {
        lire_balise();
    }
    valider_balise(nom); // On vérifie si elle correspond
}

void ecraser_tag_value(char *valeur)
{
    // On remplace la valeur du token par la valeur passée en paramètre (cf strcpy())
    strcpy(tag_value, valeur);
}

void afficher_token()
{
    printf("\n(Balise : %s, valeur : %s)\n", curr_tag, tag_value);
}