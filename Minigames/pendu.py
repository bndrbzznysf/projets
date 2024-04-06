import random

#PENDU

#on génère un mot parmi une liste contenu dans le fichier "mots.txt"
def choix_mot():
    mots = ["AVION",
            "BALAI",
            "VOITURE",
            "LIVRE",
            "ARBRE",
            "POMME",
            "CLEMENTINE",
            "CRAYON",
            "LIMITES",
            "OISEAU",
            "TOMATE",
            "CHAT",
            "DRAPEAU",
            "SOURIS",
            "ORDINATEUR",
            "CHAISE",
            "FOURMI",
            "JOURNAL",
            "OXYGENE",
            "CROCHET",
            "TROUSSE",
            "ECRAN"]

    return mots[random.randint(0, len(mots)-1)]


#affichage du mot selon les lettres devinées par le joueur : des "_" pour les lettres qu'il n'a pas deviné et les lettres du mot sinon
def affichage(mot, lettres_devinees):
    affichage = ''
    for lettre in mot:
        if lettre in lettres_devinees:
            affichage+=lettre
        else:
            affichage+='_'
    return affichage


#lance un partie de pendu
def pendu():
    print("Dans ce jeu, vous devrez deviner un mot généré aléatoirement. Vous aurez droit à 10 erreurs avant d'avoir perdu. Pensez à écrire toutes vos saisies en lettres minuscules")
    mot = choix_mot()
    nb_tentatives = 10
    lettres_devinees = []
    print(affichage(mot, lettres_devinees), end="\n\n")

    while nb_tentatives>0 and "_" in affichage(mot, lettres_devinees):
        lettre = input("Veuillez saisir une lettre : ").upper()
        while len(lettre) != 1:
            lettre = input("Vous ne devez saisir qu'une seule lettre ! Veuillez en saisir une autre : ")
        if lettre in lettres_devinees:
            print("Vous avez déjà deviné cette lettre !")
        elif lettre not in mot:
            nb_tentatives-=1
            print("Cette lettre n'est pas dans le mot à deviner, il vous reste", nb_tentatives, "tentatives")   
        else:
            lettres_devinees.append(lettre)
        print(affichage(mot, lettres_devinees), end="\n\n")

        if "_" not in affichage(mot, lettres_devinees):
            print("Vous avez gagné ! Le mot à deviner était bien :", mot)
        elif nb_tentatives==0:
            print("Vous avez perdu... Le mot à deviner était : ", mot)
    if input("Voulez-vous rejouer ? (tapez 'oui' ou 'non')  ").upper() == 'OUI': pendu()