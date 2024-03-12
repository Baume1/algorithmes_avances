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

  strcpy(tag_value, ""); // Si on lit une balise alors sa valeur est nulle

  afficher_token();
}

void ecraser_balise(char* nom){
  strcpy(curr_tag, "");

  size_t cpt = 0;
  while (nom[cpt] != '\0'){
    curr_tag[cpt] = nom[cpt];
    cpt++;
  }
  curr_tag[cpt] = '\0';
  afficher_token();
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

void ecraser_tag_value(char* valeur){
  strcpy(tag_value, valeur);
}

void afficher_token(){
  printf("\n(Balise : %s, valeur : %s)\n", curr_tag, tag_value);
}

//-------------------------------------------------------------------------------------------------

void annexes(){
  while (curr_char != EOF)
  {
    lire_et_valider_balise("annexe");
    contenu();
    lire_et_valider_balise("/annexe");
  }
}

void document(){
  lire_et_valider_balise("document");
  contenu();
  lire_et_valider_balise("/document");
  passer_espaces();
}

void texte_enrichi(){
  document();
  annexes();
}

void contenu(){
  while(strcmp(curr_tag, "/annexe") && strcmp(curr_tag, "/document") && curr_char != EOF){
    passer_espaces();

    if(curr_char == '<'){

      // On lit et stocke la balise
      lire_balise();
      passer_espaces();
      
      if(strcmp(curr_tag,"/section") && strcmp(curr_tag,"/document") && strcmp(curr_tag, "/annexe")){
        if(!strcmp(curr_tag, "section")){
          section();
        }
        else if(!strcmp(curr_tag, "titre")){
          titre();
        }
        else if (!strcmp(curr_tag, "liste")){
          liste();
        }
        else if(!strcmp(curr_tag, "br/")){
          ecraser_balise("retour_ligne");
          ecraser_tag_value("\n");
        }
        else{
          fprintf(stderr, "\nMauvaise balise rencontree, balise rencontree : %s\n", curr_tag);
          exit(2);
        }
      }else{
        return;
      }
    }else{
      mot_enrichi();
    }
    passer_espaces();
  }
}

void section(){
  lire_et_valider_balise("section");
  contenu();
  lire_et_valider_balise("/section");
}

void titre(){
  lire_et_valider_balise("titre");
  texte();
  lire_et_valider_balise("/titre");
}

void liste(){
  passer_espaces();
  lire_et_valider_balise("liste");
  while (curr_char != EOF && strcmp(curr_tag, "/liste"))
  {
    item();
    passer_espaces();
    lire_balise(); // On lit la balise pour s'assurer que la balise suivante n'est pas /liste avant de redémarrer et de rappeler item()
  }
  lire_et_valider_balise("/liste");
}

void item()
{
  lire_et_valider_balise("item");
  passer_espaces();
  if(curr_char == '<'){
    liste_texte();
  }
  else{
    texte_liste();
  }
  lire_et_valider_balise("/item");
}

void liste_texte(){
  if (curr_char == '<')
  {
    lire_balise();
    if(!strcmp(curr_tag, "liste")){
      liste();
      texte_liste();
    }
  }
  // epsilon
}

void texte_liste(){
  if (curr_char != '<')
  {
    texte();
    liste_texte();
  }
  // epsilon
}

void texte(){
  while (curr_char != EOF && curr_char != '<')
  {
    mot_enrichi();
    passer_espaces();
  }
}

void mot_enrichi(){
  if(curr_char == '<'){
    mot_important();
  }
  else{
    mot_simple();
  }
}

void mot_important(){
  lire_et_valider_balise("important");
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
  lire_et_valider_balise("/important");
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

  ecraser_balise("mot");
  passer_espaces();
}

int main(int argc, char** argv)
{
  if(argc != 2){
    printf("Nombre de parametres incorrect, veuillez ajouter le nom du fichier suivi de l'extension\n");
    exit(-2);
  }
  amorcer(argv[1]);
  texte_enrichi();
  fclose(mon_fichier);

  return 0;
}