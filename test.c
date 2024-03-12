#include <stdio.h>
#include <stdlib.h>
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
    lire_caractere();
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
    fprintf(stderr, "Erreur : caractere attendu : %c, caractere trouve : %c\n", terminal, curr_char);
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

void lire_balise(char *nom_balise)
{
  consommer_terminal('<');
  // Utilisation de  size_t au lieu de int pour l'avertissement.
  for (size_t i = 0; i < strlen(nom_balise); i++)
  {
    consommer_terminal(nom_balise[i]);
  }
  consommer_terminal('>');
}

void lire_balise_partielle(char *nom_balise)
{
  // pareil qu'au-dessus
  for (size_t i = 0; i < strlen(nom_balise); i++)
  {
    consommer_terminal(nom_balise[i]);
  }
  consommer_terminal('>');
}

void annexes()
{
  while (curr_char != EOF)
  {
    lire_balise("annexe");
    // contenu();
    passer_espaces();
    lire_balise("/annexe");
  }
}

void document()
{
  lire_balise("document");
  contenu();
  passer_espaces();
  lire_balise("/document");
}
void texte_enrichi()
{
  passer_espaces();
  document();
  passer_espaces();
  annexes();
}

char* stocker_balise() {
    static char buffer[81];
    size_t i = 0;

    consommer_terminal('<');
    // Si c'est une balise de fermeture, consommez le '/'
    if (curr_char == '/') {
        buffer[i++] = curr_char;
        lire_caractere();
    }

    // Continuez à lire le nom de la balise
    while (curr_char != '>' && i < sizeof(buffer) - 1) {
        buffer[i++] = curr_char;
        lire_caractere();
    }
    buffer[i] = '\0'; // Assurez-vous de terminer la chaîne correctement
    consommer_terminal('>');
    return buffer;
}

void contenu() {
    char* buffer;
    while(!strcmp(buffer, "/annexe") && !strcmp(buffer, "/document")) {
        passer_espaces();
        buffer = stocker_balise();

        if(strcmp(buffer, "section") == 0) {
            section();
        } else if(strcmp(buffer, "titre") == 0) {
            titre();
        } else if(strcmp(buffer, "liste") == 0) {
            liste();
        } else if(strcmp(buffer, "/section") == 0) {
            // Logique pour gérer la fin d'une section
        } else if(strcmp(buffer, "/titre") == 0) {
            // Logique pour gérer la fin d'un titre
        } else if(strcmp(buffer, "/liste") == 0) {
            // Logique pour gérer la fin d'une liste
        } else {
            fprintf(stderr, "Balise inconnue ou mal formée: %s\n", buffer);
            exit(1);
        }
    }
}

void section()
{
  lire_balise("section");
  passer_espaces();
  // contenu();
  lire_balise("/section");
}

void titre()
{
  lire_balise("titre");
  passer_espaces();
  texte();
  lire_balise("/titre");
}

void liste()
{
  lire_balise("liste");
  passer_espaces();

  while (curr_char != EOF && curr_char != '<') // pas certain de l'autre condition m'enfin
  {
    item();
    passer_espaces();
  }

  lire_balise("/liste");
}

void item()
{
  lire_balise("item");
  passer_espaces();
  texte_liste();
  lire_balise("/item");
}

void liste_texte()
{
  if (curr_char == '<')
  {
    liste();
    texte_liste();
  }
  // epsilon
}

void texte_liste()
{
  texte();
  passer_espaces();
  if (curr_char == '<')
  {
    liste_texte();
  }
  // epsilon
}

void texte()
{
  while (curr_char != EOF && curr_char != '<')
  {
    /* mot_enrichi(); */
    passer_espaces();
  }
}

// Implémentation de mot_enrichi()
void mot_enrichi()
{
  // Déterminez s'il s'agit d'un mot simple, d'un mot important ou d'un retour à la ligne
  if (curr_char == '<') {
    char *balise = stocker_balise();
    if (strcmp(balise, "debut_important") == 0) {
      mot_important();
    } else {
      fprintf(stderr, "Balise de mot enrichi inconnue: %s\n", balise);
      exit(1);
    }
  } else {
    // Considérez tout caractère qui n'est pas '<' comme un mot simple
    while (curr_char != EOF && curr_char != '<' && curr_char != ' ' && curr_char != '\n' && curr_char != '\t') {
      printf("%c", curr_char); // Affichez le mot simple
      lire_caractere();
    }
  }
}


void mot_important()
{
  lire_balise("debut_important");
  passer_espaces();
  while(curr_char != EOF && curr_char != '<') {
    printf("%c", curr_char); // Affichez le mot important
    lire_caractere();
  }
  lire_balise("/fin_important");
}

int main()
{

  amorcer();
  texte_enrichi();
  fclose(mon_fichier);

  return 0;
}