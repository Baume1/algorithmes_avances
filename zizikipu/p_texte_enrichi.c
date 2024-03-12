#include "p_texte_enrichi.h"
#include <stdio.h>
#include <string.h>

int nb_indentations = 0;
int nb_blocs = 0;
int largeur_tab = 2;
int place_restante_ligne = 80;
t_mode mode_actuel;

void changer_mode(t_mode mode){
    mode_actuel = mode;
}

t_mode mode(){
    return mode_actuel;
}

void ouvrir_bloc(){
    //Pipes d'ouverture
    for(int i=0;i<nb_blocs;i++){
            printf("%s","|");
        }
    //Affichage de la barre
    printf("%s","+");
    for(int i=0; i<78-2*(nb_blocs); i++){
        printf("%s","-");
    }
    printf("%s", "+");
    //Pipes de fermeture
    for(int i=0;i<nb_blocs;i++){
            printf("%s","|");
        }
    nb_blocs++;
    printf("%s","\n");
}

void fermer_bloc(){
    nb_blocs--;
    //Pipes d'ouverture
    for(int i=0;i<nb_blocs;i++){
            printf("%s","|");
        }    
    //Affichage de la barre
    printf("%s","+");
    for(int i=0; i<78-2*(nb_blocs); i++){
        printf("%s","-");
    }
    printf("%s", "+");
    //Pipes de fermeture
    for(int i=0;i<nb_blocs;i++){
            printf("%s","|");
        }
    printf("%s","\n"); 
}

void indenter(){
    nb_indentations++;
    for(int i=0;i<nb_indentations;i++){
        printf("%s","  ");
        place_restante_ligne-=largeur_tab;
    }
}

void desindenter(){
    nb_indentations--;
}

int est_en_fin_de_ligne(){
    if(nb_blocs!=0){
        if(place_restante_ligne - nb_blocs==0){ 
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(place_restante_ligne==0){
        return 1;
    }
    else{
        return 0;  
    }    
}

int est_au_debut_de_ligne(){
    if(nb_blocs!=0){
        if(place_restante_ligne+nb_blocs==0){ 
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(place_restante_ligne==80){
        return 1;
    }
    else{
        return 0;
    }
}

void entamer_ligne(){
    if(nb_blocs==1){
        printf("%s","|");
        place_restante_ligne--;
    }
    else if(nb_blocs>1){
        for(int i=0;i<nb_blocs;i++){
            printf("%s","|");
            place_restante_ligne--;
        }
    }    
}

void terminer_ligne(){
    if(nb_blocs>0){
        for(int i=0;i<place_restante_ligne-nb_blocs;i++){
            printf("%s"," ");
        }
        for(int i=0;i<nb_blocs;i++){
                printf("%s","|"); 
        }
        printf("%s","\n"); 
        place_restante_ligne=80;       
    }
    else{
        for(int i=0;i<place_restante_ligne;i++){
            printf("%s"," ");
        }
        printf("%s","\n"); 
        place_restante_ligne=80;       
    }
}

void pucer(){
    printf("%s","*");
    printf("%s","  ");
    place_restante_ligne-=3;
}

void ecrire_mot(const char* mot){
    char motchange[strlen(mot) + 1];

    if(mode_actuel==NORMAL){
        strcpy(motchange,mot);
    }
    else if(mode_actuel==MAJUSCULE){
        for(size_t i=0; i<strlen(mot);i++){
            if (mot[i]  >= 97 &&  mot[i] <= 122)
                motchange[i] = mot[i] - 32;
            else{
                motchange[i] = mot[i];
            }
        }
    }
    else if(mode_actuel==MINUSCULE){
        for(size_t i=0; i<strlen(mot);i++){
            if (mot[i]  >= 65 &&  mot[i] <= 90)
                motchange[i] = mot[i] + 32;
            else{
                motchange[i] = mot[i];
            }
        }
    }
    printf("%s",motchange);
    place_restante_ligne-=strlen(motchange);
    if(est_en_fin_de_ligne()==0){
        printf("%s"," ");
        place_restante_ligne--;
    }
}

int peut_ecrire(int nb_caracteres){
    if(place_restante_ligne>nb_caracteres){
        return 1;
    }
    else{
        return 0;
    }
}
