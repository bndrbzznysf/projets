import pendu
import mastermind
import morpion

#Menu principal
print("Ces jeux vous sont présentés par NSI1 Minigames !")
jeu = int(input("A quel jeu souhaitez-vous jouer ? \n1 - Pendu \n2 - Mastermind \n3 - Morpion\n"))

if jeu == 1: pendu.pendu()
elif jeu == 2: mastermind.mastermind(mastermind.menu())
elif jeu == 3: morpion.morpion()
else: jeu = int(input("Cette option n'est pas proposée, veuillez choisir un chiffre entre 1, 2 et 3\n"))