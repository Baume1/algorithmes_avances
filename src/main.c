#include "non_terminaux.h"
#include "terminaux.h"

// Ces variables sont globales (vues dans tout le programme)
FILE *mon_fichier;     // On déclare ici le fichier
char curr_char = '\0'; // On déclare le caractère actuel

char curr_tag[81];  // L'étiquette du token
char tag_value[81]; // La valeur du token

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