import random

#Penser à changer le chemin si jamais Python ne détecte pas le fichier 'mots.txt'
import os
cwd = r"C:\Users\Ce PC\Desktop\Projects\Python"
os.chdir(cwd)

#PENDU

#on génère un mot parmi une liste contenu dans le fichier "mots.txt"
def choix_mot():
    mots = open("mots.txt", "r")
    mots= [mot.strip() for mot in mots]
    return random.choice(mots)


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
        lettre = input("Veuillez saisir une lettre : ")
        while len(lettre) != 1:
            lettre = input("Vous ne devez saisir qu'une seule lettre ! Veuillez en saisir une autre : ")
        if lettre not in mot:
            nb_tentatives-=1
            print("Cette lettre n'est pas dans le mot à deviner, il vous reste", nb_tentatives, "tentatives")
        if lettre in lettres_devinees:
            print("Vous avez déjà deviné cette lettre ! ")
        else:
            lettres_devinees.append(lettre)
        print(affichage(mot, lettres_devinees), end="\n\n")

        if "_" not in affichage(mot, lettres_devinees):
            print("Vous avez gagné ! Le mot à deviner était bien :", mot)
        elif nb_tentatives==0:
            print("Vous avez perdu... Le mot à deviner était : ", mot)
    if input("Voulez-vous rejouer ? (tapez 'oui' ou 'non')  ") == 'oui': pendu()
    else: print("Au revoir !")

        


#MASTERMIND

#on génère une combinaison selon le niveau choisi par le joueur
def genere_combinaison(taille):
    return [random.randint(1, 9) for i in range(taille)] #on génère une liste de "taille" éléments aléatoires allant de 0 à 9


#on renvoie le nombre de pions présents bien placés ou mal placés dans la proposition saisie par le joueur
def evalue_proposition(essai, combi):
    occurences = {}
    bien_place = 0
    mal_place = 0

    for chiffre in combi:
        if chiffre not in occurences:
            occurences[chiffre] = 0
        occurences[chiffre] +=1
    
    for i in range(len(combi)):
        if essai[i] == combi[i]:
            bien_place +=1
            occurences[essai[i]] -=1

    for chiffre_essai in essai: 
        if chiffre_essai in occurences and occurences[chiffre_essai] > 0:
            mal_place +=1
            occurences[chiffre_essai] -=1

    return bien_place, mal_place   


#menu d'affichage avec sélection du niveau
def menu():
    print("Dans ce jeu, vous devrez deviner une combinaison de chiffres allant de 1 à 9 inclus.\n")
    print("Veuillez choisir votre niveau : ")
    print("1 : Facile - Vous aurez droit à 10 tentatives pour deviner une combinaison de 4 chiffres")
    print("2 : Moyen - Vous aurez droit à 8 tentatives pour deviner une combinaison de 5 chiffres")
    print("3 : Difficile - Vous aurez droit à 8 tentatives pour deviner une combinaison de 6 chiffres")
    niveau = int(input())
    while niveau !=1 and niveau !=2 and niveau!=3:
        niveau = int(input("Ce niveau n'est pas disponible, veuillez choisir un niveau..."))
    return niveau


#lance une partie selon les paramètres du niveau (nombre d'essais et taille de la combinaison à deviner)
def mastermind(niveau):
    if niveau == 1:
        essais = 10
        taille = 4
    elif niveau == 2:
        essais = 8
        taille = 5
    else:
        essais = 8
        taille = 6
    
    combinaison = genere_combinaison(taille)
    proposition = []
    while essais > 0 and proposition != combinaison:
        proposition = list(input("Veuillez saisir votre proposition : "))
        while(len(proposition) != len(combinaison)):
            proposition = list(input("Combinaison invalide, veuillez saisir à nouveau votre proposition : "))
        proposition = [int(chiffre) for chiffre in proposition]
        
        essais-=1
        print("Chiffres bien placés : ", evalue_proposition(proposition, combinaison)[0])
        print("Chiffres mal placés : ", evalue_proposition(proposition, combinaison)[1])
        print("Nombres d'essais restants : ", essais)
    if proposition == combinaison:
        print("Vous avez gagné : la combinaison était bien", ''.join(str(chiffre) for chiffre in combinaison), ", bravo !")
    else:
        print("Vous avez perdu, c'est dommage... La combinaison était ", ''.join(str(chiffre) for chiffre in combinaison))

    if input("Voulez-vous rejouer ? (tapez 'oui' ou 'non')  ") == 'oui': mastermind(menu())
    else: print("Au revoir !")


#MORPION

#affichage de la grille avec les pions
def affiche_grille(grille):
    for i in range(2):
        for j in range(2):
            print(grille[i][j], end='|')
        print(grille[i][2])
        print("-----")
    for j in range(2):
        print(grille[2][j], end='|')
    print(grille[2][2])
    print("\n")


#saisie du pion du joueur
def saisie_joueur():
    ligne=int(input("Veuillez saisir une ligne : "))
    colonne=int(input("Veuillez saisir une colonne : ")) 
    while ligne < 0 or ligne > 3:
        ligne=int(input("Cette case n'existe pas, veuillez en saisir une autre : "))
    while colonne < 0 or colonne > 3:
        colonne=int(input("Cette case ne fonctionne pas, veuillez en saisir une autre : "))
    return ligne, colonne


#génération du pion de l'ordinateur
def saisie_ordinateur():
    ligne=random.randint(0, 2)
    colonne=random.randint(0, 2)
    return ligne, colonne


#renvoie true si joueur a gagné et false sinon
def victoire(grille, joueur):
    for ligne in grille:
        if all(case == joueur for case in ligne):
            return True
    for colonne in range(3):
        if all(grille[ligne][colonne] == joueur for ligne in range(3)):
            return True
    if all(grille[i][i] == joueur for i in range(3)) or all(grille[i][2 - i] == joueur for i in range(3)):
        return True

    return False


#partie de morpion
def morpion():
    print("Dans ce jeu, vous devrez saisir le numéro de la ligne puis le numéro de la colonne de la case où vous souhaitez placer votre pion.")
    grille = [[' ', ' ', ' '], [' ', ' ', ' '], [' ', ' ', ' ']]
    cases_restantes = 9
    affiche_grille(grille)

    while cases_restantes > 0 and not victoire(grille, 'X') and not victoire(grille, 'O'):
        joueur = 'O'
        print("Votre tour !")
        ligne_j, colonne_j = saisie_joueur()
        while grille[ligne_j-1][colonne_j-1] != ' ':
            ligne_j, colonne_j = saisie_joueur()
        grille[ligne_j-1][colonne_j-1] = 'O'
        cases_restantes-=1
        affiche_grille(grille)
        if cases_restantes == 0:
            break
        if victoire(grille, 'O'):
            print("Félicitations ! Vous avez gagné !")
            break
        

        joueur = 'X'
        print("A l'ordinateur !")
        ligne_o, colonne_o = saisie_ordinateur()
        while grille[ligne_o-1][colonne_o-1] != ' ':
            ligne_o, colonne_o = saisie_ordinateur()
        grille[ligne_o-1][colonne_o-1] = 'X'
        cases_restantes-=1
        affiche_grille(grille)
        if cases_restantes == 0:
            break
        if victoire(grille, 'X'):
            print("Dommage, vous avez perdu")
            break
        
        if cases_restantes == 0 and not victoire(grille, 'X') and not victoire(grille, 'O'):
            print("Match nul!")
            break
        
    if input("Voulez-vous rejouer ? (tapez 'oui' ou 'non')  ") == 'oui': morpion()
    else: print("Au revoir !")



#menu principal
print("Ces jeux vous sont présentés par NSI1 Minigames !")
jeu = int(input("A quel jeu souhaitez-vous jouer ? \n1 - Pendu \n2 - Mastermind \n3 - Morpion\n"))

if jeu == 1: pendu()
elif jeu == 2: mastermind(menu())
elif jeu == 3: morpion()
else: jeu = int(input("Cette option n'est pas proposée, veuillez choisir un chiffre entre 1, 2 et 3\n"))