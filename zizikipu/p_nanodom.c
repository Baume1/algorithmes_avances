#include "p_nanodom.h"
#include "p_texte_enrichi.h"

void creer_noeud(
    p_noeud *ceci,
    t_token etiquette,
    const char *contenu,
    p_noeud pere,
    p_noeud premier_fils,
    p_noeud dernier_fils,
    p_noeud grand_frere,
    p_noeud petit_frere)
{
    *ceci = (p_noeud)malloc(sizeof(t_noeud));
    (*ceci)->l_etiquette = etiquette;
    (*ceci)->le_contenu = contenu;
    (*ceci)->les_parentes[PERE] = pere;
    (*ceci)->les_parentes[PREMIER_FILS] = premier_fils;
    (*ceci)->les_parentes[DERNIER_FILS] = dernier_fils;
    (*ceci)->les_parentes[GRAND_FRERE] = grand_frere;
    (*ceci)->les_parentes[PETIT_FRERE] = petit_frere;
}

const char *t_token_image(t_token ceci)
{
    switch (ceci)
    {
    case 0:
        return "DOCUMENT";
        break;
    case 1:
        return "ANNEXE";
        break;
    case 2:
        return "SECTION";
        break;
    case 3:
        return "TITRE";
        break;
    case 4:
        return "LISTE";
        break;
    case 5:
        return "ITEM";
        break;
    case 6:
        return "IMPORTANT";
        break;
    case 7:
        return "RETOUR_A_LA_LIGNE";
        break;
    case 8:
        return "MOT";
        break;
    }
    return 0;
}

const char *t_parente_image(t_parente ceci)
{
    switch (ceci)
    {
    case 0:
        return "PERE";
        break;
    case 1:
        return "PREMIER FILS";
        break;
    case 2:
        return "DERNIER FILS";
        break;
    case 3:
        return "GRAND FRERE";
        break;
    case 4:
        return "PETIT FRERE";
        break;
    case 5:
        return "NB_PARENTES";
        break;
    }
    return 0;
}

void detruire_noeud(p_noeud *ceci)
{
    free((*ceci)->les_parentes);
    free(*ceci);
}

void modifier_etiquette_noeud(p_noeud ceci, t_token nouvelle_etiquette)
{
    ceci->l_etiquette = nouvelle_etiquette;
}

void modifier_contenu_noeud(p_noeud ceci, char *nouveau_contenu)
{
    ceci->le_contenu = nouveau_contenu;
}

void modifier_parente_noeud(p_noeud ceci, t_parente lien_de_parente, p_noeud nouveau_parent)
{
    ceci->les_parentes[lien_de_parente] = nouveau_parent;
}

void debugger_noeud(p_noeud ceci)
{
    printf("%s %p %s", "Noeud rangé à l'adresse ", ceci, "\n");
    printf("%s %s %s", "     - L'étiquette : ", t_token_image(ceci->l_etiquette), "\n");
    printf("%s %s %s", "     - Le contenu : ", ceci->le_contenu, "\n");
    printf("%s %p %s", "     - Le père : ", ceci->les_parentes[PERE], "\n");
    printf("%s %p %s", "     - Le premier fils : ", ceci->les_parentes[PREMIER_FILS], "\n");
    printf("%s %p %s", "     - Le dernier fils : ", ceci->les_parentes[DERNIER_FILS], "\n");
    printf("%s %p %s", "     - Le grand frère : ", ceci->les_parentes[GRAND_FRERE], "\n");
    printf("%s %p %s", "     - Le petit frère : ", ceci->les_parentes[PETIT_FRERE], "\n");
}

void inserer_aine(p_noeud ceci, p_noeud orphelin)
{
    if (ceci != NOEUD_VIDE && orphelin != NOEUD_VIDE)
    {
        if (ceci->les_parentes[PREMIER_FILS] == NOEUD_VIDE)
        {
            modifier_parente_noeud(ceci, PREMIER_FILS, orphelin);
            modifier_parente_noeud(ceci, DERNIER_FILS, orphelin);
        }
        else if (ceci->les_parentes[PREMIER_FILS] != NOEUD_VIDE)
        {
            // ajout grand frère/petit frère
            modifier_parente_noeud(orphelin, PETIT_FRERE, ceci->les_parentes[PREMIER_FILS]);
            modifier_parente_noeud(ceci->les_parentes[PREMIER_FILS], GRAND_FRERE, orphelin);
            // ajout père/dernier fils
            modifier_parente_noeud(ceci, PREMIER_FILS, orphelin);
        }
        modifier_parente_noeud(ceci->les_parentes[PREMIER_FILS], PERE, ceci);
    }
}

void inserer_cadet(p_noeud ceci, p_noeud orphelin)
{
    if (ceci != NOEUD_VIDE && orphelin != NOEUD_VIDE)
    {
        if (ceci->les_parentes[DERNIER_FILS] == NOEUD_VIDE)
        {
            modifier_parente_noeud(ceci, PREMIER_FILS, orphelin);
            modifier_parente_noeud(ceci, DERNIER_FILS, orphelin);
        }
        else if (ceci->les_parentes[DERNIER_FILS] != NOEUD_VIDE)
        {
            // ajout grand frère/petit frère
            modifier_parente_noeud(orphelin, GRAND_FRERE, ceci->les_parentes[DERNIER_FILS]);
            modifier_parente_noeud(ceci->les_parentes[DERNIER_FILS], PETIT_FRERE, orphelin);
            // ajout père/dernier fils
            modifier_parente_noeud(ceci, DERNIER_FILS, orphelin);
        }
        modifier_parente_noeud(ceci->les_parentes[DERNIER_FILS], PERE, ceci);
    }
}

void inserer_apres(p_noeud ceci, p_noeud orphelin)
{
    if (ceci->les_parentes[PETIT_FRERE] == NOEUD_VIDE)
    {
        inserer_cadet(ceci->les_parentes[PERE], orphelin);
    }
    else
    {

        modifier_parente_noeud(ceci->les_parentes[PETIT_FRERE], GRAND_FRERE, orphelin);
        modifier_parente_noeud(orphelin, PETIT_FRERE, ceci->les_parentes[PETIT_FRERE]);

        modifier_parente_noeud(ceci, PETIT_FRERE, orphelin);
        modifier_parente_noeud(orphelin, GRAND_FRERE, ceci);

        modifier_parente_noeud(orphelin, PERE, ceci->les_parentes[PERE]);
    }
}

void inserer_avant(p_noeud ceci, p_noeud orphelin)
{
    if (ceci->les_parentes[GRAND_FRERE] == NOEUD_VIDE)
    {
        inserer_aine(ceci->les_parentes[PERE], orphelin);
    }
    else
    {

        modifier_parente_noeud(ceci->les_parentes[GRAND_FRERE], PETIT_FRERE, orphelin);
        modifier_parente_noeud(orphelin, GRAND_FRERE, ceci->les_parentes[GRAND_FRERE]);

        modifier_parente_noeud(ceci, GRAND_FRERE, orphelin);
        modifier_parente_noeud(orphelin, PETIT_FRERE, ceci);

        modifier_parente_noeud(orphelin, PERE, ceci->les_parentes[PERE]);
    }
}
void extraire(p_noeud ceci)
{
    // cas ou ceci est premier et dernier fils en meme temps
    if (ceci->les_parentes[PERE]->les_parentes[PREMIER_FILS] == ceci && ceci->les_parentes[PERE]->les_parentes[DERNIER_FILS] == ceci)
    {
        ceci->les_parentes[PERE]->les_parentes[PREMIER_FILS] = NOEUD_VIDE;
        ceci->les_parentes[PERE]->les_parentes[DERNIER_FILS] = NOEUD_VIDE;
        ceci->les_parentes[PERE] = NOEUD_VIDE;
    }
    // cas ou ceci est premier fils
    else if (ceci->les_parentes[PERE]->les_parentes[PREMIER_FILS] == ceci && ceci->les_parentes[PERE]->les_parentes[DERNIER_FILS] != ceci)
    {
        // changement de qui est le premier fils
        ceci->les_parentes[PERE]->les_parentes[PREMIER_FILS] = ceci->les_parentes[PETIT_FRERE];
        // le nouveau premier fils n'a plus de grand frere
        ceci->les_parentes[PETIT_FRERE]->les_parentes[GRAND_FRERE] = NOEUD_VIDE;

        // on supprime le lien entre ceci et son pere
        ceci->les_parentes[PERE] = NOEUD_VIDE;
        // on supprime le lien entre ceci et son petit frere
        ceci->les_parentes[PETIT_FRERE] = NOEUD_VIDE;
    }
    // cas ou ceci est dernier fils
    else if (ceci->les_parentes[PERE]->les_parentes[PREMIER_FILS] != ceci && ceci->les_parentes[PERE]->les_parentes[DERNIER_FILS] != ceci)
    {
        // changement de qui est le dernier fils
        ceci->les_parentes[PERE]->les_parentes[DERNIER_FILS] = ceci->les_parentes[GRAND_FRERE];
        // le nouveau dernier fils n'a plus de petit frere
        ceci->les_parentes[GRAND_FRERE]->les_parentes[PETIT_FRERE] = NOEUD_VIDE;

        // on supprime le lien entre ceci et son pere
        ceci->les_parentes[PERE] = NOEUD_VIDE;
        // on supprime le lien entre ceci et son grand frere
        ceci->les_parentes[GRAND_FRERE] = NOEUD_VIDE;
    }
    // cas ou ceci n'est ni dernier ni premier fils
    else
    {
        // on supprime le lien entre ceci et son pere
        ceci->les_parentes[PERE] = NOEUD_VIDE;
        // interchangement des freres
        ceci->les_parentes[GRAND_FRERE]->les_parentes[PETIT_FRERE] = ceci->les_parentes[PETIT_FRERE];
        ceci->les_parentes[PETIT_FRERE]->les_parentes[GRAND_FRERE] = ceci->les_parentes[GRAND_FRERE];
        // on supprime les liens entre ceci et ses freres
        ceci->les_parentes[GRAND_FRERE] = NOEUD_VIDE;
        ceci->les_parentes[PETIT_FRERE] = NOEUD_VIDE;
    }
}

void afficher_elabore(t_arbre_nanodom ceci)
{
    ceci = (p_noeud)ceci;
    if (ceci != NOEUD_VIDE)
    {
        switch (ceci->l_etiquette)
        {
        case DOCUMENT:
            ouvrir_bloc();
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
            fermer_bloc();
            break;
        case SECTION:
            ouvrir_bloc();
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
            fermer_bloc();
            break;
        case TITRE:
            changer_mode(MAJUSCULE);
            entamer_ligne();
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
            terminer_ligne();
            changer_mode(NORMAL);
            break;
        case LISTE:
            entamer_ligne();
            indenter();
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
            break;
        case ITEM:
            pucer();
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
            terminer_ligne();
            break;
        case IMPORTANT:
            changer_mode(MAJUSCULE);
            afficher_elabore(ceci->les_parentes[PREMIER_FILS]);
            break;
        case RETOUR_A_LA_LIGNE:
            terminer_ligne();
            break;
        case MOT:
            // vérifie si c'est le premier mot
            if (ceci->les_parentes[GRAND_FRERE] != NOEUD_VIDE && ceci->les_parentes[GRAND_FRERE]->l_etiquette != MOT && ceci->les_parentes[GRAND_FRERE]->l_etiquette != IMPORTANT)
            {
                entamer_ligne();
            }
            ecrire_mot(ceci->le_contenu);
            // si le petit frère n'est pas un mot
            if (ceci->les_parentes[PETIT_FRERE] != NOEUD_VIDE && (ceci->les_parentes[PETIT_FRERE]->l_etiquette != MOT && ceci->les_parentes[PETIT_FRERE]->l_etiquette != IMPORTANT))
            {
                terminer_ligne();
            }
            break;
        default:
            break;
        }
        afficher_elabore(ceci->les_parentes[PETIT_FRERE]);
    }
}

int nb_indentations_enrichi = 0;

void indenter_enrichi()
{
    for (int i = 0; i < nb_indentations_enrichi; i++)
    {
        printf("%s", "    ");
    }
}
void afficher_enrichi(t_arbre_nanodom ceci)
{
    ceci = (p_noeud)ceci;
    if (ceci != NOEUD_VIDE)
    {
        switch (ceci->l_etiquette)
        {

        case DOCUMENT:
            indenter_enrichi();
            printf("%s", "<DOCUMENT>\n");
            nb_indentations_enrichi++;
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            nb_indentations_enrichi--;
            printf("%s", "</DOCUMENT>");
            break;

        case SECTION:
            indenter_enrichi();
            printf("%s", "<SECTION>\n");
            nb_indentations_enrichi++;
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            nb_indentations_enrichi--;
            indenter_enrichi();
            printf("%s", "</SECTION>\n");
            break;

        case TITRE:
            indenter_enrichi();
            printf("%s", "<TITRE>");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            printf("%s", "</TITRE>\n");
            break;

        case LISTE:
            indenter_enrichi();
            printf("%s", "<LISTE>\n");
            nb_indentations_enrichi++;
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            nb_indentations_enrichi--;
            indenter_enrichi();
            printf("%s", "</LISTE>\n");

            break;

        case ANNEXE:
            break;

        case ITEM:
            indenter_enrichi();
            printf("%s", "<ITEM>");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            printf("%s", "</ITEM>\n");

            break;

        case IMPORTANT:
            printf("%s", "<IMPORTANT>");
            afficher_enrichi(ceci->les_parentes[PREMIER_FILS]);
            printf("%s", "</IMPORTANT>");
            break;

        case MOT:
            if (ceci->les_parentes[GRAND_FRERE] != NOEUD_VIDE && ceci->les_parentes[GRAND_FRERE]->l_etiquette != MOT && ceci->les_parentes[GRAND_FRERE]->l_etiquette != IMPORTANT)
            {
                indenter_enrichi();
            }
            ecrire_mot(ceci->le_contenu);
            if (ceci->les_parentes[PETIT_FRERE] != NOEUD_VIDE && (ceci->les_parentes[PETIT_FRERE]->l_etiquette != MOT && ceci->les_parentes[PETIT_FRERE]->l_etiquette != IMPORTANT))
            {
                indenter_enrichi();
                printf("%s", "\n");
            }
            break;

        case RETOUR_A_LA_LIGNE:
            break;
        }

        afficher_enrichi(ceci->les_parentes[PETIT_FRERE]);
    }
}

int nb_indentations_sauvegarde = 0;

void sauvegarder_enrichi(t_arbre_nanodom ceci, FILE *fichier)
{
    ceci = (p_noeud)ceci;
    if (ceci != NOEUD_VIDE)
    {
        switch (ceci->l_etiquette)
        {

        case DOCUMENT:
            for (int i = 0; i < nb_indentations_sauvegarde; i++)
            {
                fprintf(fichier, "%s", "    ");
            }
            fprintf(fichier, "%s", "<DOCUMENT>\n");
            nb_indentations_sauvegarde++;
            sauvegarder_enrichi(ceci->les_parentes[PREMIER_FILS], fichier);
            nb_indentations_sauvegarde--;
            fprintf(fichier, "%s", "</DOCUMENT>");
            break;

        case SECTION:
            for (int i = 0; i < nb_indentations_sauvegarde; i++)
            {
                fprintf(fichier, "%s", "    ");
            }
            fprintf(fichier, "%s", "<SECTION>\n");
            nb_indentations_sauvegarde++;
            sauvegarder_enrichi(ceci->les_parentes[PREMIER_FILS], fichier);
            nb_indentations_sauvegarde--;
            for (int i = 0; i < nb_indentations_sauvegarde; i++)
            {
                fprintf(fichier, "%s", "    ");
            }
            fprintf(fichier, "%s", "</SECTION>\n");
            break;

        case TITRE:
            for (int i = 0; i < nb_indentations_sauvegarde; i++)
            {
                fprintf(fichier, "%s", "    ");
            }
            fprintf(fichier, "%s", "<TITRE>");
            sauvegarder_enrichi(ceci->les_parentes[PREMIER_FILS], fichier);
            fprintf(fichier, "%s", "</TITRE>\n");
            break;

        case LISTE:
            for (int i = 0; i < nb_indentations_sauvegarde; i++)
            {
                fprintf(fichier, "%s", "    ");
            }
            fprintf(fichier, "%s", "<LISTE>\n");
            nb_indentations_sauvegarde++;
            sauvegarder_enrichi(ceci->les_parentes[PREMIER_FILS], fichier);
            nb_indentations_sauvegarde--;
            for (int i = 0; i < nb_indentations_sauvegarde; i++)
            {
                fprintf(fichier, "%s", "    ");
            }
            fprintf(fichier, "%s", "</LISTE>\n");
            break;

        case ANNEXE:
            break;

        case ITEM:
            for (int i = 0; i < nb_indentations_sauvegarde; i++)
            {
                fprintf(fichier, "%s", "    ");
            }
            fprintf(fichier, "%s", "<ITEM>");
            sauvegarder_enrichi(ceci->les_parentes[PREMIER_FILS], fichier);
            fprintf(fichier, "%s", "</ITEM>\n");
            break;

        case IMPORTANT:
            fprintf(fichier, "%s", "<IMPORTANT>");
            sauvegarder_enrichi(ceci->les_parentes[PREMIER_FILS], fichier);
            fprintf(fichier, "%s", "</IMPORTANT>");
            break;

        case MOT:
            if (ceci->les_parentes[GRAND_FRERE] != NOEUD_VIDE && ceci->les_parentes[GRAND_FRERE]->l_etiquette != MOT && ceci->les_parentes[GRAND_FRERE]->l_etiquette != IMPORTANT)
            {
                for (int i = 0; i < nb_indentations_sauvegarde; i++)
                {
                    fprintf(fichier, "%s", "    ");
                }
            }
            fprintf(fichier, "%s", ceci->le_contenu);
            if (ceci->les_parentes[PETIT_FRERE] != NOEUD_VIDE && (ceci->les_parentes[PETIT_FRERE]->l_etiquette != MOT && ceci->les_parentes[PETIT_FRERE]->l_etiquette != IMPORTANT))
            {
                for (int i = 0; i < nb_indentations_sauvegarde; i++)
                {
                    fprintf(fichier, "%s", "    ");
                }
                fprintf(fichier, "%s", "\n");
            }
            break;

        case RETOUR_A_LA_LIGNE:
            break;
        }

        sauvegarder_enrichi(ceci->les_parentes[PETIT_FRERE], fichier);
    }
}

void destruction_debug_noeud(p_noeud ceci)
{
    printf("%s %p %s", "DESTRUCTION Noeud rangé à l'adresse ", ceci, "\n");
    printf("%s %s %s", "     - L'étiquette : ", t_token_image(ceci->l_etiquette), "\n");
    printf("%s %s %s", "     - Le contenu : ", ceci->le_contenu, "\n");
    printf("%s %p %s", "     - Le père : ", ceci->les_parentes[PERE], "\n");
    printf("%s %p %s", "     - Le premier fils : ", ceci->les_parentes[PREMIER_FILS], "\n");
    printf("%s %p %s", "     - Le dernier fils : ", ceci->les_parentes[DERNIER_FILS], "\n");
    printf("%s %p %s", "     - Le grand frère : ", ceci->les_parentes[GRAND_FRERE], "\n");
    printf("%s %p %s", "     - Le petit frère : ", ceci->les_parentes[PETIT_FRERE], "\n");
}

void detruire_nanodom(t_arbre_nanodom *ceci)
{
    if ((*ceci) != NOEUD_VIDE)
    {
        // Conditions pour parcourir tout l'arbre en récursif
        if ((*ceci)->les_parentes[DERNIER_FILS] != NOEUD_VIDE)
        {
            detruire_nanodom(&(*ceci)->les_parentes[DERNIER_FILS]);
            destruction_debug_noeud((*ceci));
            detruire_noeud(&(*ceci));
        }
        else if ((*ceci)->les_parentes[PREMIER_FILS] == NOEUD_VIDE && (*ceci)->les_parentes[GRAND_FRERE] != NOEUD_VIDE)
        {
            detruire_nanodom(&(*ceci)->les_parentes[GRAND_FRERE]);
            destruction_debug_noeud((*ceci)->les_parentes[PETIT_FRERE]);
            detruire_noeud(&(*ceci)->les_parentes[PETIT_FRERE]);
            destruction_debug_noeud((*ceci));
            detruire_noeud(&(*ceci));
        }
        detruire_nanodom(&(*ceci)->les_parentes[PERE]);
    }
}