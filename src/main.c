#include "non_terminaux.h"
#include "terminaux.h"
#include "globals.h"

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