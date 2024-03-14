#include "globals.h"

// Ces variables sont globales (vues dans tout le programme)
FILE *mon_fichier;     // On déclare ici le fichier
char curr_char = '\0'; // On déclare le caractère actuel

char curr_tag[81];  // L'étiquette du token
char tag_value[81]; // La valeur du token