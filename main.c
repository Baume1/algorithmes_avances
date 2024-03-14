#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Ces variables sont globales (vues dans tout le programme)
FILE *mon_fichier;     // On déclare ici le fichier
char curr_char = '\0'; // On déclare le caractère actuel

char curr_tag[81];  // L'étiquette du token
char tag_value[81]; // La valeur du token

void amorcer(char *nom_fichier)
{
  mon_fichier = fopen(nom_fichier, "r"); // On ouvre le fichier donné en paramètre en mode "read"
  if (mon_fichier == NULL)
  {
    printf("Fichier introuvable, verifiez que vous avez entre une extension\nLe creer malgre tout ?\n");
    int test = 0;
    (scanf("%d", &test) ? mon_fichier = fopen("test1.txt", "w") : 0);
    exit(-1);
  }
  lire_caractere();
}

void lire_caractere()
{
  // fgetc() lit caractère par caractère le fichier donné en paramètre
  curr_char = fgetc(mon_fichier);
  printf("%c", curr_char);
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

  // afficher_token();
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
  // afficher_token();
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

//-----------------------------Grammaire : cf le document--------------------------------------------------

void annexes()
{
  while (curr_char != EOF)
  {
    lire_et_valider_balise("annexe");
    contenu();
    lire_et_valider_balise("/annexe");
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
  while (strcmp(curr_tag, "/annexe") && strcmp(curr_tag, "/document") && curr_char != EOF)
  {
    passer_espaces();

    // Si c'est une balise, elle commence par '<'
    if (curr_char == '<')
    {

      // On lit et stocke la balise
      lire_balise();
      passer_espaces();

      // Equivalent case switch mais avec des char*
      if (strcmp(curr_tag, "/section") && strcmp(curr_tag, "/document") && strcmp(curr_tag, "/annexe"))
      {
        if (!strcmp(curr_tag, "section"))
        {
          section();
        }
        else if (!strcmp(curr_tag, "titre"))
        {
          titre();
        }
        else if (!strcmp(curr_tag, "liste"))
        {
          liste();
        }
        else if (!strcmp(curr_tag, "br/"))
        {
          ecraser_balise("retour_ligne");
          ecraser_tag_value("\n");
        }
        else
        {
          // Si aucun cas ne correspondent on envoie une erreur et où elle se situe
          fprintf(stderr, "\nMauvaise balise rencontree dans contenu(), balise rencontree : %s\n", curr_tag);
          exit(2);
        }
      }
      else
      {
        return;
      }
    }
    else
    {
      // Si ce n'est pas une balise, c'est que c'est un mot
      mot_enrichi();
    }
    passer_espaces();
  }
}

void section()
{
  lire_et_valider_balise("section");
  contenu();
  lire_et_valider_balise("/section");
}

void titre()
{
  lire_et_valider_balise("titre");
  texte();
  lire_et_valider_balise("/titre");
}

void liste()
{
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

  // Si on tombe sur une balise, c'est que ce n'est pas du texte donc on rappelle liste_texte()
  if (curr_char == '<')
  {
    liste_texte();
  }
  // Sinon c'est un mot et on appelle texte_liste()
  else
  {
    texte_liste();
  }
  lire_et_valider_balise("/item");
}

void liste_texte()
{
  if (curr_char == '<')
  {
    lire_balise();
    if (!strcmp(curr_tag, "liste"))
    // Si on retombe sur une liste, on rappelle la fonction
    //(pour continuer la boucle récursive et la casser dans le cas échéant)
    {
      liste();
      texte_liste();
    }
  }
  // epsilon
}

void texte_liste()
{
  // On vérifie bien qu'on est pas sur une balise, sinon on stoppe la boucle recursive
  if (curr_char != '<')
  {
    texte();
    liste_texte();
  }
  // epsilon
}

void texte()
{
  // Tant qu'on ne tombe pas sur la fin du fichier ou sur une balise, on lit tous les mots
  while (curr_char != EOF && curr_char != '<')
  {
    mot_enrichi();
    passer_espaces();
  }
}

void mot_enrichi()
{
  // Si on est sur une balise, c'est qu'on a un mot important
  if (curr_char == '<')
  {
    mot_important();
  }
  else
  {
    // Sinon un simple mot
    mot_simple();
  }
}

void mot_important()
{
  lire_et_valider_balise("important");
  while (curr_char != '<')
  {
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

void mot_simple()
{
  strcpy(tag_value, ""); // On écrase la valeur précédente

  size_t cpt = 0;
  // Puis on lit le "contenu" du document jusqu'à arriver à un espace ou à la fin du doc
  while (!isspace(curr_char) && curr_char != EOF)
  {
    tag_value[cpt++] = curr_char; // Stocker le caractère dans la valeur du token
    lire_caractere();             // Puis le lire/passer
  }
  tag_value[cpt] = '\0';

  ecraser_balise("mot");
  passer_espaces();
}

int main(int argc, char **argv)
{
  // On vérifie qu'on a bien un nom de fichier donné en paramètre
  if (argc != 2)
  {
    printf("Nombre de parametres incorrect, veuillez ajouter le nom du fichier suivi de l'extension\n");
    exit(-2);
  }
  amorcer(argv[1]);
  texte_enrichi();
  fclose(mon_fichier);

  return 0;
}