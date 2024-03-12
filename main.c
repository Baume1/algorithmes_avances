#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *mon_fichier;
char curr_char = '\0';

char curr_tag[81];
char tag_value[81];

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
  while (isspace(curr_char) && curr_char != EOF)
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
  passer_espaces();
}

void lire_balise_partielle(char *nom_balise)
{
  // pareil qu'au-dessus
  for (size_t i = 0; i < strlen(nom_balise); i++)
  {
    consommer_terminal(nom_balise[i]);
  }
  consommer_terminal('>');
  passer_espaces();
}

void annexes()
{
  while (curr_char != EOF)
  {
    lire_balise("annexe");
    contenu();
  }
}

void document()
{
  lire_balise("document");
  contenu();
  // /document lu par le buffer
}

void texte_enrichi()
{
  document();
  annexes();
}

/*
char* stocker_balise(){
  char buffer[81];
  consommer_terminal('<');
  size_t cpt = 0;
  while(curr_char != '>'){
    buffer[cpt++] = curr_char;
  }
  consommer_terminal('>');
  buffer[cpt] = '\0';
  return buffer;
}
*/

void contenu()
{
  char buffer[81];
  while(strcmp(buffer, "/annexe") && strcmp(buffer, "/document") && strcmp(buffer, "/section") && curr_char != EOF){
    strcpy(buffer, "");
    passer_espaces();

    // On lit et stocke la balise
    if(curr_char == '<'){

      consommer_terminal('<');
      size_t cpt = 0;
      while(curr_char != '>'){
        buffer[cpt++] = curr_char;
        lire_caractere();
      }
      buffer[cpt] = '\0';
      consommer_terminal('>');

      passer_espaces();
      if(!strcmp(buffer, "section")){
        section();
      }
      else if(!strcmp(buffer, "titre")){
        titre();
      }
      else if (!strcmp(buffer, "liste")){
        liste();
      }
    }else{
      mot_enrichi();
    }
    passer_espaces();
    //printf("\n Buffer : %s et curr char : %c\n", buffer, curr_char);
  }
  printf("Sortie boucle\n");
}

void section()
{
  contenu();
}

void titre()
{
  texte();
  lire_balise("/titre");
}

void liste()
{
  while (curr_char != EOF) // pas certain de l'autre condition m'enfin
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
  if(curr_char == '<'){
    liste_texte();
  }
  else{
    texte_liste();
  }
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
  if (curr_char != '<')
  {
    texte();
    liste_texte();
  }
  // epsilon
}

void texte()
{
  while (curr_char != EOF && curr_char != '<')
  {
    mot_enrichi();
    passer_espaces();
  }
}

void mot_enrichi()
{
  if(curr_char == '<'){
    mot_important();
  }
  else{
    mot_simple();
  }
}

void mot_important()
{
  lire_balise("important");
  while(curr_char != '<'){
    mot_simple();
    
    /*
    // Mettre le caractère en majuscule = lui retrancher 26 + 6 (à cause des caractères entre les deux)
    if ('a' <= curr_char && curr_char <= 'z'){
      curr_char += 32;
    }
    // Stocker le caractère
    lire_caractere(); // Puis le lire
    */
  }
  lire_balise("/important");
}

void mot_simple(){
  while(!isspace(curr_char) && curr_char != EOF){
    // Stocker le caractère
    lire_caractere(); // Puis le lire/passer
  }
  passer_espaces();
}

int main()
{

  amorcer();
  texte_enrichi();
  fclose(mon_fichier);

  return 0;
}