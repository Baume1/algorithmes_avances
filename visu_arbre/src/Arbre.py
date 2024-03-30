import graphviz
import os
os.environ["PATH"] += os.pathsep + '../bin'

import json

class Arbre:
    def __init__(self):
        self.liste = []
    
    """
    def __str__(self):
        print("Alphabet : ", self.alphabet)
        print("Etats : ", self.etats)
        print("Etats initiaux : ", self.etats_init)
        print("Etats terminaux : ", self.etats_term)
        print("Transitions :")
        for transition in self.transitions:
            print("\t", transition[0], "--(" + self.str_symboles(transition[1]) + ")-->", transition[2])
    """

    def to_dot(self):
        """
        #Retourne la description du graphe au format dot
        """
        dot = graphviz.Digraph()
        dot.attr(rankdir="TB")
        dot.node("__1__", shape="point")
        
        dot.edge(tail_name="__1__", head_name=self.liste[0]["adresse"], label="DEBUT_ARBRE")
        for noeud in self.liste:
            # print(noeud["nom"],noeud["fils"])
            label_correct = noeud["nom"] if noeud["nom"] != "mot" else "mot : " + noeud["valeur"]
            dot.node(name=noeud["adresse"], label = label_correct, shape="circle")
            if(noeud["pere"] != '0'):
                dot.edge(tail_name=noeud["pere"], head_name=noeud["adresse"], label="enfant")
            
            if(noeud["gd_frere"] != '0'):
                dot.edge(tail_name=noeud["gd_frere"], head_name=noeud["adresse"], label="frere")
            
        return dot
    
    def to_png(self, filename):
        """
        Génère l'image dans le fichier filename
        """
        dot = self.to_dot()
        dot.render(filename="../images/"+filename, format="png")

    #---------------------------------Sauvegarde et chargement-----------------------------------

    def charger(self, filename):
        """
        Charge les informations d'un automate à partir d'un fichier texte.

        Args:
            filename (str): Nom du fichier texte contenant les informations de l'automate, sans l'extension '.txt'.

        Le fichier texte doit respecter le format suivant :
        Ligne 1 : Alphabet de l'automate, séparé par des espaces.
        Ligne 2 : Liste des états de l'automate, séparés par des espaces.
        Ligne 3 : Liste des états initiaux de l'automate, séparés par des espaces.
        Ligne 4 : Liste des états terminaux de l'automate, séparés par des espaces.
        Lignes suivantes : Transitions de l'automate, chacune sur une ligne séparée, au format 'état_initial symbole état_final'.

        Après avoir lu le fichier, les attributs suivants de l'objet automate sont mis à jour :
            - self.alphabet (set) : Ensemble des symboles de l'alphabet.
            - self.etats (set) : Ensemble des états de l'automate.
            - self.etats_init (set) : Ensemble des états initiaux de l'automate.
            - self.etats_term (set) : Ensemble des états terminaux de l'automate.
            - self.transitions (list) : Liste des transitions de l'automate, ajoutées à l'aide de la méthode self.ajouter_transition().
        """
        fichier = open("../"+filename+".json", "r")

        self.liste = json.load(fichier)
        
        fichier.close()
