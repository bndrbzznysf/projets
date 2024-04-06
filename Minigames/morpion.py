import random

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
        
    if input("Voulez-vous rejouer ? (tapez 'oui' ou 'non')  ").upper() == 'OUI': morpion()
    else: print("Au revoir !")