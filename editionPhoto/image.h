#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


//déclaration de la classe Image
class Image {

private:
    vector<vector<int>> _rouge; //vecteur 2D de la couleur rouge
    vector<vector<int>> _vert;  //vecteur 2D de la couleur vert
    vector<vector<int>> _bleu;  //vecteur 2D de la couleur bleu
    int _longueur; //entier qui définit la longeur du vecteur stockant les dimensions de l’image.
    int _largeur;  //entier qui définit la largeur du vecteur stockant les dimensions de l’image.

public:
    //Image() : premier constructeur de Image, construit une image de taille donnée
    Image(vector<vector<int>> &rouge, vector<vector<int>> &vert,vector<vector<int>> &bleu);

    //Image() : deuxième constructeur de Image à partir de loadPicture()
    Image(string &nom);

    //constructeur vide
    Image();

    //geters : renvoient les vecteurs privés rouge, vert et bleu
    vector<vector<int>> getRouge()const;
    vector<vector<int>> getVert()const;
    vector<vector<int>> getBleu()const;
    int getLongueur()const;
    int getLargeur()const;

    void affiche()const; //affichage d'une Image
    Image copie(); //copie d'une Image
    Image composanteRouge()const; //crée une nouvelle Image avec le niveau de vert et de bleu à 0 et conserve les proportions de rouge d'une Image
    bool detection(int R, int V, int B)const; //renvoie true si le pixel entré en paramètres existe et false sinon
    Image niveauGris(); //crée une nouvelle image à partir de l'Image cible dont tous les pixels sont gris
    Image noirEtBlanc(int seuil); //crée une nouvelle image en noir et blanc à partir de l'Image cible
    vector<int> histogrammeGris(); //renvoie un vecteur d'entiers représentant l'histogramme de niveau de gris d'une Image
    Image luminosityUp(float lum); //crée une nouvelle image à partir de l'Image cible dont la luminosité est augmentée
    Image luminosityDown(float lum); //crée une nouvelle image à partir de l'Image cible dont la luminosité est diminuée


    Image rognerD(int nb); //cree une nouvelle image à partir de l'image cible qui supprime nb colonnes à droite
    Image rognerG(int nb); //cree une nouvelle image à partir de l'image cible qui supprime nb colonnes à gauche
    Image rognerH(int nb); //cree une nouvelle image à partir de l'image cible qui supprime nb lignes en haut
    Image rognerB(int nb); //cree une nouvelle image à partir de l'image cible qui supprime nb lignes en bas
    Image retournementV(); //cree une nouvelle image à partie de l'image cible qui la retourne verticalement
    Image retournementH(); //cree une nouvelle image à partie de l'image cible qui la retourne horizontalement
    Image rotationD();  //crée une nouvelle image à partir de l’image cible qui effectue une rotation de l’image de 90° vers la droite
    Image rotationG();  //crée une nouvelle image à partir de l’image cible qui effectue une rotation de l’image de 90° vers la gauche
    Image agrandissement(int facteur);  //crée une nouvelle image à partir de l’image cible qui agrandit l’image d’un facteur entier.


    //AJOUT D'UNE FONCTIONNALITE : ROTATION COULEUR
    void rotationCouleur(); //effectue un changement de teinte de l'image : le rouge devient vert, le vert devient bleu et le bleu devient rouge
};


string saisieNomFichier(); //saisie du nom du fichier image sur lequel l'utilisateur souhaite travaiiler
void Menu(); //affichage du menu présentant les différentes fonctionnalités offertes par le logiciel
int saisieChoix(); //saisie du choix de l'utilisateur sur la modification de l'image qu'il souhaite effectuer

void savePicture(Image & img); //permet d'enregistrer une image dans un nouveau fichier ppm à partir d'un objet Image

