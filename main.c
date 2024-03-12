#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *mon_fichier;
char curr_char = '\0';

char curr_tag[81];
char tag_value[81];

void amorcer(char* nom_fichier)
{
    mon_fichier = fopen(nom_fichier, "r");
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

/*
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
*/

void lire_balise(){
  strcpy(curr_tag, "");

  consommer_terminal('<'); // Si on lit une balise, elle commence par un "<"

  size_t cpt = 0;
  while(curr_char != '>'){
    curr_tag[cpt++] = curr_char;
    lire_caractere();
  }
  curr_tag[cpt] = '\0';

  consommer_terminal('>'); // Si on lit une balise, elle finit par un ">"
}

void ecraser_balise(char* nom){
  strcpy(curr_tag, "");

  size_t cpt = 0;
  while (nom[cpt] != '\0'){
    curr_tag[cpt] = nom[cpt];
    cpt++;
  }
  curr_tag[cpt] = '\0';
}

void valider_balise(char* nom){
  if(strcmp(curr_tag, nom)){
    fprintf(stderr, "Mauvaise balise '%s', balise attendue : %s\n", curr_tag, nom);
    exit(2);
  }
}

void lire_et_valider_balise(char* nom){
  if(strcmp(curr_tag, nom)){
    lire_balise();
  }
  valider_balise(nom);
}

void annexes()
{
  while (curr_char != EOF)
  {
    lire_balise();
    contenu();
  }
}

void document()
{
  lire_et_valider_balise("document");
  contenu();
  lire_et_valider_balise("/document");
  passer_espaces();
}

void texte_enrichi()
{
  document();
  annexes();
}

void contenu()
{
  while(strcmp(curr_tag, "/annexe") && strcmp(curr_tag, "/document") && strcmp(curr_tag, "/section") && curr_char != EOF){
    passer_espaces();

    if(curr_char == '<'){

      // On lit et stocke la balise
      lire_balise();
      passer_espaces();

      if(!strcmp(curr_tag, "section")){
        section();
      }
      else if(!strcmp(curr_tag, "titre")){
        titre();
      }
      else if (!strcmp(curr_tag, "liste")){
        liste();
      }else{
        printf(stderr, "Mauvaise balise de rencontree");
      }
    }else{
      ecraser_balise("mot");
      mot_enrichi();
    }
    passer_espaces();
  }
}

void section()
{
  contenu();
  valider_balise("/section");
}

void titre()
{
  texte();
  lire_balise();
}

void liste()
{
  while (curr_char != EOF && strcmp(curr_tag, "/liste"))
  {
    item();
    passer_espaces();
  }
  lire_balise();
}

void item()
{
  lire_balise();
  passer_espaces();
  if(curr_char == '<'){
    liste_texte();
  }
  else{
    texte_liste();
  }
  texte_liste();
  lire_balise();
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
  lire_balise();
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
  lire_balise();
}

void mot_simple(){
  strcpy(tag_value, ""); // On écrase la valeur précédente

  size_t cpt = 0;
  // Puis on lit le "contenu" du document jusqu'à arriver à un espace ou à la fin du doc
  while(!isspace(curr_char) && curr_char != EOF){
    tag_value[cpt++] = curr_char; // Stocker le caractère
    lire_caractere(); // Puis le lire/passer
  }
  tag_value[cpt] = '\0';

  passer_espaces();
}

int main(int argc, char** argv)
{
  if(argc != 2){
      printf("nb paramètres incorrect\n");
      exit(-2);
  }
  amorcer(argv[1]);
  texte_enrichi();
  fclose(mon_fichier);

  return 0;
}