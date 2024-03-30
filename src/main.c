#include "non_terminaux.h"
#include "terminaux.h"
#include "arbre.h"
#include "affichage.h"

// Ces variables sont globales (vues dans tout le programme)
FILE *mon_fichier;     // On déclare ici le fichier
char curr_char = '\0'; // On déclare le caractère actuel

char curr_tag[81];  // L'étiquette du token
char tag_value[81]; // La valeur du token

t_noeud *racine;    // Le premier noeud de l'arbre (document, normalement)
t_noeud *curr_node; // Le noeud que l'on traite actuellement

int utiliser_arbre = 0; // Booléen permettant d'appliquer ou non les fonctions relatives à l'arbre

int main(int argc, char **argv)
{
  // On vérifie qu'on a bien un nom de fichier donné en paramètre
  if (argc != 2)
  {
    printf("Nombre de parametres incorrect, veuillez ajouter le nom du fichier suivi de l'extension\n");
    exit(-2);
  }

  initialiser_arbre(); // Initialise l'arbre et modifie le comportement du programme en cascade, à commenter avec libérer arbre si on ne l'utilise pas
  amorcer(argv[1]);
  texte_enrichi();

  // A décommenter pour utiliser les fonctions
  if(utiliser_arbre){
    // sauvegarder();
    // afficher_arbre(racine);
    rendre_texte(racine);
  }

  fclose(mon_fichier);
  if(utiliser_arbre){
    liberer_arbre(racine);
  }

  return 0;
}