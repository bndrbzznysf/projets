import random

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

    if input("Voulez-vous rejouer ? (tapez 'oui' ou 'non')  ").upper() == 'OUI': mastermind(menu())
    else: print("Au revoir !")