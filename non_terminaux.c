#include "non_terminaux.h"

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
    tag_value[cpt] = '\0'; // On ajoute '\0' pour la lecture

    ecraser_balise("mot");
    passer_espaces();
}
