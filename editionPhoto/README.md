Fichier README

Il faut suivre les instructions dans l’ordre pour une meilleure expérience et compréhension du code.

- Télécharger le dossier S102
 
- Créer un projet sur CodeBlocks et y ajouter les fichiers image.h, image.cpp et main.cpp qui sont dans le dossier S102. 

- Exécuter le code (une saisie s’affiche : « Veuillez saisir le nom du fichier image sur lequel vous souhaitez travailler : »)

- Vous pouvez utiliser n'importe quelle image au format ppm CODEE EN ASCII ET NON EN BRUT (très important). Il faut placer l'image en question dans le dossier S102 où se trouvent les fichiers nécessaires à l'utilisation du code.

- Si l’image est bien conforme alors la phrase « L'image *nom_de_fichier*.ppm a bien été chargée dans les tableaux. » confirme que l’image est bien prise en compte et qu’elle est au bon format.


	Le menu suivant s’affiche :
		----------------- Menu -------------------
		Voici les differentes fonctionnalites disponibles :
		1 : copie                                                                                         
		2 : composante rouge
		3 : detection
		4 : niveauGris
		5 : noirEtBlanC
		6 : histogrammeGris
		7 : luminosityUp
		8 : luminosityDown
		9 : rognerH
		10 : rognerB
		11 : rognerG
		12 : rognerD
		13 : retournement vertical
		14 : retournement horizontal
		15 : rotation droite
		16 : rotation gauche
		17 : agrandissement
		18 : QUITTER

- Saisir le nombre en fonction de votre demande (explication en dessous de chaque fonctionnalité)
 Si le nombre est saisi 18 alors le programme s’arrête en vous disant « Au revoir ! »

Attention !!!!  Plus l’image est volumineuse plus elle mettra de temps à charger dans le logiciel !

- Vous devrez ensuite nommer votre nom de fichier, en n'oubliant pas de rajouter l'extension ".ppm" afin que le bon format de fichier soit créé.


* Le nombre 1 permet de crée une copie exacte de l’image cible au début on vous demande de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 2 créer une nouvelle image à partir de l’image cible qui a la même composante Rouge et les autres composantes à zéro. On vous demande de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 3 vous demande d’entrer un pixel soit trois nombres entre 0 et 255 avec un espace entre chacun qui correspondent au code RVB d’une couleur. Et vous dit s’il y est ou non dans l’image cible.

* Le nombre 4 créer une nouvelle image à partir de l’image cible dont chaque pixel est gris. Pour obtenir le niveau de gris d’un pixel, on fait la moyenne des trois composantes. On vous demande de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 5 créer une nouvelle image à partir de l’image cible dont chaque pixel est ou noir, ou blanc. Si le niveau de gris est plus clair qu’un seuil passé en paramètre le pixel est blanc et s’il est plus sombre que le seuil le pixel devient noir. Saisir un seuil entre 0 et 255. On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 6 l’histogramme donne un tableau avec le nombre de pixel que contient chaque niveau de gris de l’image cible de 0 à 255.

* Le nombre 7 créer une nouvelle image à partir de l’image cible dont la luminosité a été augmentée. Donnée un entier entre 2 et 255 (chaque pixels sera multiplier par celui-ci) Exemple : 2. On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 8 créer une nouvelle image à partir de l’image cible dont la luminosité a été diminuée. Donnée un entier entre 2 et 255 (chaque pixels sera multiplier par celui-ci) Exemple : 2. On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 9 créer une nouvelle image à partir de l’image cible qui supprime nombre des lignes de pixel de l’image respectivement en haut. Saisir le nombre de ligne qui sera supprimé.  On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 10 créer une nouvelle image à partir de l’image cible qui supprime nombre des lignes de pixel de l’image respectivement en bas. Saisir le nombre de ligne qui sera supprimé.  On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 11 créer une nouvelle image à partir de l’image cible qui supprime nombre des colonnes de pixel de l’image respectivement à gauche. Saisir le nombre de colonnes qui sera supprimé.  On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 12 créer une nouvelle image à partir de l’image cible qui supprime nombre des colonnes de pixel de l’image respectivement à droite. Saisir le nombre de colonnes qui sera supprimé.  On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 13 créer une nouvelle image à partir de l’image cible qui effectue une symétrie de l’image d’axe vertical. On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 14 créer une nouvelle image à partir de l’image cible qui effectue une symétrie de l’image d’axe horizontal. On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 15 créer une nouvelle image à partir de l’image cible qui effectue une rotation de l’image de 90° vers la droite (sens horaire).  On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 16 créer une nouvelle image à partir de l’image cible qui effectue une rotation de l’image de 90° vers la gauche (sens trigonométrique). On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

* Le nombre 17 créer une nouvelle image à partir de l’image cible qui agrandit l’image d’un facteur entier. Saisir un entier supérieur par le quelle chaque pixel sera dupliquer. On vous demande ensuite de donner un nom a cette nouvelle image pour qu’elle soit conforme il faut forcément un .ppm et aucun espace dans le nom.

-Après vos manipulations si vous avez créé des fichiers vous les retrouverez dans le dossier S102 que vous pourrez observer avec le logiciel GIMP.

Bonne utilisation !

DURAND Inès
BENDAR Ines
1M

