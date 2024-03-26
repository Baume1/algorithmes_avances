#include "main.h"
#include "arbre.h"

FILE *fichier_sauvegarde;

void initialiser_arbre()
{
    curr_node = malloc(sizeof(t_noeud));

    strcpy(curr_node->nom_balise, "texte_enrichi");
    strcpy(curr_node->valeur_balise, "");

    curr_node->fils = NULL;
    curr_node->pt_frere = NULL;
    curr_node->gd_frere = NULL;

    racine = curr_node;

    utiliser_arbre = 1;
}

void remonter_noeuds_eg(char *nom_balise) // Remonter tous les noeuds qui ont le même nom que celui en paramètre
{
    if (curr_node->pere != NULL)
    {
        if (!strcmp(curr_node->pere->nom_balise, nom_balise))
        {
            curr_node = curr_node->pere;
            remonter_noeuds_eg(nom_balise);
        }
    }
}

void remonter_noeuds_ineg(char *nom_balise) // Remonter tous les noeuds qui ont un nom différent de celui en paramètre
{
    if (curr_node->pere != NULL)
    {
        if (strcmp(curr_node->nom_balise, nom_balise))
        {
            curr_node = curr_node->pere;
            remonter_noeuds_ineg(nom_balise);
        }
    }
}

void remonter_pere() // Remonter jusqu'au père
{
    if (curr_node->pere == NULL && curr_node->gd_frere != NULL)
    {
        curr_node = curr_node->gd_frere;
        remonter_pere();
    }
    else if (curr_node->pere != NULL)
    {
        curr_node = curr_node->pere;
    }
    else
    {
        fprintf(stderr, "\nLe pere et grand frere n'existent pas\n");
        exit(102);
    }
}

void maj_curr_node(t_noeud *new_node)
{
    // On fait la manipulation avec le noeud actuel
    if (curr_node->fils == NULL)
    {
        // On lui ajoute le nouveau noeud comme fils si il n'a pas de fils
        new_node->pere = curr_node;
        curr_node->fils = new_node;
    }
    else if (curr_node->pt_frere == NULL)
    {
        // Sinon on lui ajoute comme frère
        new_node->gd_frere = curr_node;
        curr_node->pt_frere = new_node;
    }
    else
    {
        fprintf(stderr, "Le noeud est invalide, son frere et son pere sont deja occupes. Le noeud :\n");
        afficher_noeud_actuel();
        exit(101);
    }
    curr_node = new_node;
}

void ajouter_noeud()
{
    t_noeud *nv_noeud = malloc(sizeof(t_noeud));

    strcpy((nv_noeud->nom_balise), curr_tag);
    strcpy((nv_noeud->valeur_balise), tag_value);

    nv_noeud->fils = NULL;
    nv_noeud->pere = NULL;
    nv_noeud->gd_frere = NULL;
    nv_noeud->pt_frere = NULL;

    maj_curr_node(nv_noeud);
}

void maj_arbre()
{
    ///*
    // Si on arrive à la fin d'une chaîne sans br/ mais qu'on ouvre une balise, on retourne à la racine de la suite de mots
    if (curr_tag[0] != '/' && strcmp(curr_tag, curr_node->nom_balise) && strcmp(curr_tag, "br/"))
    {
        remonter_noeuds_eg("mot");
    }
    ajouter_noeud();
    if (curr_node->pere != NULL)
    {
        if (!strcmp(curr_node->pere->nom_balise, "mot") && strcmp(curr_node->nom_balise, "mot") || !strcmp(curr_node->nom_balise, "br/"))
        {
            remonter_noeuds_eg("mot");
        }
    }
    if (curr_tag[0] == '/')
    {
        remonter_noeuds_eg("mot");
        remonter_pere();
    }
    // afficher_noeud_actuel();
    //*/

    /*
    if (!strcmp(curr_tag, "mot"))
    {
        ajouter_noeud();
    }
    else
    {
        if (curr_tag[0] == '/')
        {
            ajouter_noeud();
            remonter_noeuds_eg("mot");
            remonter_pere();
        }
        else if (!strcmp(curr_node->nom_balise, "mot") || !strcmp(curr_tag, "br/"))
        {
            remonter_noeuds_eg("mot");
        }
        else if (curr_node->pere != NULL)
        {
            if (!strcmp(curr_node->pere->nom_balise, "mot") && curr_node->nom_balise[0] != '/')
            {
                remonter_noeuds_eg("mot");
            }
        }
        else if (strcmp(curr_tag, "br/")) // Si c'est différent de br/
        {
            ajouter_noeud();
        }
    }
    //*/
}

void afficher_noeud_actuel()
{
    /*
    printf("\nAdresse du noeud : %X\n", curr_node);
    printf("Balise du noeud : %s\n", curr_node->nom_balise);
    printf("Valeur de la balise : %s\n", curr_node->valeur_balise);
    printf("Son pere : %X\n", curr_node->pere);
    printf("Son fils : %X\n", curr_node->fils);
    printf("Son gd frere : %X\n", curr_node->gd_frere);
    printf("Son pt frere : %X\n", curr_node->pt_frere);
    */
    printf("\n{");
    printf("\n\"adresse\": \"%X\",", curr_node);
    printf("\n\"nom\": \"%s\",", curr_node->nom_balise);
    printf("\n\"valeur\": \"%s\",", curr_node->valeur_balise);
    printf("\n\"pere\": \"%X\",", curr_node->pere);
    printf("\n\"fils\": \"%X\",", curr_node->fils);
    printf("\n\"pt_frere\": \"%X\",", curr_node->pt_frere);
    printf("\n\"gd_frere\": \"%X\"", curr_node->gd_frere);
    printf("\n},");
}

void sauvegarder()
{
    fichier_sauvegarde = fopen("arbre_json.txt", "w");
    fprintf(fichier_sauvegarde, "[");
    /*
    fprintf(fichier_sauvegarde, "\n{");
    fprintf(fichier_sauvegarde, "\n\"adresse\": \"%X\",", racine);
    fprintf(fichier_sauvegarde, "\n\"nom\": \"%s\",", racine->nom_balise);
    fprintf(fichier_sauvegarde, "\n\"valeur\": \"%s\",", racine->valeur_balise);
    fprintf(fichier_sauvegarde, "\n\"pere\": \"%X\",", racine->pere);
    fprintf(fichier_sauvegarde, "\n\"fils\": \"%X\",", racine->fils);
    fprintf(fichier_sauvegarde, "\n\"pt_frere\": \"%X\",", racine->pt_frere);
    fprintf(fichier_sauvegarde, "\n\"gd_frere\": \"%X\"", racine->gd_frere);
    fprintf(fichier_sauvegarde, "\n}");
    */
    sauvegarder_arbre(racine);
    fprintf(fichier_sauvegarde, "\n]");
}

void sauvegarder_noeud(t_noeud *noeud_a_sauvegarder)
{
    // Sauvegarder dans le fichier selon une certaine syntaxe
    fprintf(fichier_sauvegarde, "\n{");
    fprintf(fichier_sauvegarde, "\n\"adresse\": \"%X\",", noeud_a_sauvegarder);
    fprintf(fichier_sauvegarde, "\n\"nom\": \"%s\",", noeud_a_sauvegarder->nom_balise);
    fprintf(fichier_sauvegarde, "\n\"valeur\": \"%s\",", noeud_a_sauvegarder->valeur_balise);
    fprintf(fichier_sauvegarde, "\n\"pere\": \"%X\",", noeud_a_sauvegarder->pere);
    fprintf(fichier_sauvegarde, "\n\"fils\": \"%X\",", noeud_a_sauvegarder->fils);
    fprintf(fichier_sauvegarde, "\n\"pt_frere\": \"%X\",", noeud_a_sauvegarder->pt_frere);
    fprintf(fichier_sauvegarde, "\n\"gd_frere\": \"%X\"", noeud_a_sauvegarder->gd_frere);
    fprintf(fichier_sauvegarde, "\n},");
}

void sauvegarder_arbre(t_noeud *noeud_a_parcourir)
{
    sauvegarder_noeud(noeud_a_parcourir);
    if (noeud_a_parcourir->fils != NULL)
    {
        sauvegarder_arbre(noeud_a_parcourir->fils);
    }
    if (noeud_a_parcourir->pt_frere != NULL)
    {
        sauvegarder_arbre(noeud_a_parcourir->pt_frere);
    }
}

void afficher_noeud(t_noeud *noeud_a_afficher)
{
    printf("\nAdresse du noeud : %X\n", noeud_a_afficher);
    printf("Balise du noeud : %s\n", noeud_a_afficher->nom_balise);
    printf("Valeur de la balise : %s\n", noeud_a_afficher->valeur_balise);
    printf("Son pere : %X\n", noeud_a_afficher->pere);
    printf("Son fils : %X\n", noeud_a_afficher->fils);
    printf("Son gd frere : %X\n", noeud_a_afficher->gd_frere);
    printf("Son pt frere : %X\n", noeud_a_afficher->pt_frere);
}

void afficher_arbre(t_noeud *noeud_a_parcourir)
{
    afficher_noeud(noeud_a_parcourir);
    if (noeud_a_parcourir->fils != NULL)
    {
        afficher_arbre(noeud_a_parcourir->fils);
    }
    if (noeud_a_parcourir->pt_frere != NULL)
    {
        afficher_arbre(noeud_a_parcourir->pt_frere);
    }
}

void liberer_arbre(t_noeud *noeud_a_parcourir)
{
    if (noeud_a_parcourir->fils != NULL)
    {
        liberer_arbre(noeud_a_parcourir->fils);
    }
    if (noeud_a_parcourir->pt_frere != NULL)
    {
        liberer_arbre(noeud_a_parcourir->pt_frere);
    }
    free(noeud_a_parcourir);
}