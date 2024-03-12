#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *mon_fichier;
char curr_char = '\0';

void amorcer()
{
    mon_fichier = fopen("test1.txt", "r");
    if (mon_fichier == NULL)
    {
        printf("Probleme de fichier\nLe creer ?\n");
        int test = 0;
        (scanf("%d", &test) ? mon_fichier = fopen("test1.txt", "w") : 0);
        exit(-1);
    }
}

void lire_caractere()
{
    curr_char = fgetc(mon_fichier);
    printf("%c", curr_char);
}

void consommer_terminal(char terminal)
{
    if (terminal != curr_char)
    {
        fprintf(stderr, "Erreur : caractere attendu : %d, caractere trouve : %d\n", terminal, curr_char);
        exit(1);
    }
    lire_caractere();
}


void passer_espaces()
{
    while (curr_char == ' ' || curr_char == '\t' || curr_char == '\n')
    {
        lire_caractere();
    }
}

void lire_balise(char* nom_balise){
    consommer_terminal('<');
    for(int i = 0; i < strlen(nom_balise); i++){
        consommer_terminal(nom_balise[i]);
    }
    consommer_terminal('>');
}

int main(){
    amorcer();
    lire_caractere();
    lire_balise("document");
    fclose(mon_fichier);
    return 0;
}