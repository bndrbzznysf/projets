#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


//d�claration de la classe Image
class Image {

private:
    vector<vector<int>> _rouge; //vecteur 2D de la couleur rouge
    vector<vector<int>> _vert;  //vecteur 2D de la couleur vert
    vector<vector<int>> _bleu;  //vecteur 2D de la couleur bleu
    int _longueur; //entier qui d�finit la longeur du vecteur stockant les dimensions de l�image.
    int _largeur;  //entier qui d�finit la largeur du vecteur stockant les dimensions de l�image.

public:
    //Image() : premier constructeur de Image, construit une image de taille donn�e
    Image(vector<vector<int>> &rouge, vector<vector<int>> &vert,vector<vector<int>> &bleu);

    //Image() : deuxi�me constructeur de Image � partir de loadPicture()
    Image(string &nom);

    //constructeur vide
    Image();

    //geters : renvoient les vecteurs priv�s rouge, vert et bleu
    vector<vector<int>> getRouge()const;
    vector<vector<int>> getVert()const;
    vector<vector<int>> getBleu()const;
    int getLongueur()const;
    int getLargeur()const;

    void affiche()const; //affichage d'une Image
    Image copie(); //copie d'une Image
    Image composanteRouge()const; //cr�e une nouvelle Image avec le niveau de vert et de bleu � 0 et conserve les proportions de rouge d'une Image
    bool detection(int R, int V, int B)const; //renvoie true si le pixel entr� en param�tres existe et false sinon
    Image niveauGris(); //cr�e une nouvelle image � partir de l'Image cible dont tous les pixels sont gris
    Image noirEtBlanc(int seuil); //cr�e une nouvelle image en noir et blanc � partir de l'Image cible
    vector<int> histogrammeGris(); //renvoie un vecteur d'entiers repr�sentant l'histogramme de niveau de gris d'une Image
    Image luminosityUp(float lum); //cr�e une nouvelle image � partir de l'Image cible dont la luminosit� est augment�e
    Image luminosityDown(float lum); //cr�e une nouvelle image � partir de l'Image cible dont la luminosit� est diminu�e


    Image rognerD(int nb); //cree une nouvelle image � partir de l'image cible qui supprime nb colonnes � droite
    Image rognerG(int nb); //cree une nouvelle image � partir de l'image cible qui supprime nb colonnes � gauche
    Image rognerH(int nb); //cree une nouvelle image � partir de l'image cible qui supprime nb lignes en haut
    Image rognerB(int nb); //cree une nouvelle image � partir de l'image cible qui supprime nb lignes en bas
    Image retournementV(); //cree une nouvelle image � partie de l'image cible qui la retourne verticalement
    Image retournementH(); //cree une nouvelle image � partie de l'image cible qui la retourne horizontalement
    Image rotationD();  //cr�e une nouvelle image � partir de l�image cible qui effectue une rotation de l�image de 90� vers la droite
    Image rotationG();  //cr�e une nouvelle image � partir de l�image cible qui effectue une rotation de l�image de 90� vers la gauche
    Image agrandissement(int facteur);  //cr�e une nouvelle image � partir de l�image cible qui agrandit l�image d�un facteur entier.


    //AJOUT D'UNE FONCTIONNALITE : ROTATION COULEUR
    void rotationCouleur(); //effectue un changement de teinte de l'image : le rouge devient vert, le vert devient bleu et le bleu devient rouge
};


string saisieNomFichier(); //saisie du nom du fichier image sur lequel l'utilisateur souhaite travaiiler
void Menu(); //affichage du menu pr�sentant les diff�rentes fonctionnalit�s offertes par le logiciel
int saisieChoix(); //saisie du choix de l'utilisateur sur la modification de l'image qu'il souhaite effectuer

void savePicture(Image & img); //permet d'enregistrer une image dans un nouveau fichier ppm � partir d'un objet Image

