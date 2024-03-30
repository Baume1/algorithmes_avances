# Le Projet

Ce projet est divisé en deux parties : une partie en C et une partie en Python. \
Voici les instructions pour chaque partie :

## Partie C
> Le programme est fait pour fonctionner sur le powershell. Aucune interface graphique ni stop ne sont mis en place pour tout autre type d'affichage.

La partie C se trouve dans le dossier `src`. Pour compiler le code, exécutez la commande suivante **dans ce dossier src** : `make all`

Différentes fonctions peuvent être activées en décommentant les lignes correspondantes dans le code source. Voici les fonctions disponibles :

- `initialiser_arbre()` : Initialise l'arbre de données.
- `amorcer(argv[1])` : Ouvre le fichier spécifié en argument.
- `texte_enrichi()` : Effectue un traitement sur le texte.
- `sauvegarder()` : Sauvegarde les données dans un fichier.
- `afficher_arbre(racine)` : Affiche l'arbre de données.
- `rendre_texte(racine)` : Génère du texte à partir de l'arbre de données.

## Partie Python
> Pour installer graphviz, lancez "py -m pip install grapviz". \
> Si il y a eu une erreur lorsque vous lancez le programme, installez la libriairie (le zip) via [le site graphviz](https://graphviz.org/download/) \
> Une fois installé, décompressez le bin dans le bin de `visu_arbre`, puis relancez le programme.

La partie Python se trouve dans le dossier `visu_arbre/src`. Avant d'exécuter cette partie, vous devez effectuer les étapes suivantes dans la partie C :

1. Décommentez les lignes `initialiser_arbre()` et `sauvegarder()` dans le code C.
2. Compilez et exécutez le code C.
3. Copiez le résultat généré dans le fichier `arbre_json.txt` se trouvant dans le dossier `src` et collez-le dans un fichier `.json` dans le dossier `visu_arbre`.
4. Supprimez la dernière virgule du fichier `.json`.
5. Dans le fichier `main.py` situé dans `visu_arbre/src`, modifiez la variable `nom_fichier` sans extension ni chemin pour quelle corresponde à votre fichier `.json`.

Une fois ces étapes effectuées, vous pouvez exécuter le code Python **dans le src de visu arbre** pour visualiser l'arbre de données se trouvant dans le dossier image.
