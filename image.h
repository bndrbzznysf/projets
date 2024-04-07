#include <iostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


class Image {

private:
    vector<vector<int>> _rouge; 
    vector<vector<int>> _vert;  
    vector<vector<int>> _bleu;
    int _longueur; 
    int _largeur;

public:
    
    Image(vector<vector<int>> &rouge, vector<vector<int>> &vert,vector<vector<int>> &bleu);

    
    Image(string &nom);

    
    Image();

    
    vector<vector<int>> getRouge()const;
    vector<vector<int>> getVert()const;
    vector<vector<int>> getBleu()const;
    int getLongueur()const;
    int getLargeur()const;


    void affiche()const; 
    Image copie(); 
    Image composanteRouge()const; 
    bool detection(int R, int V, int B)const; 
    Image niveauGris(); 
    Image noirEtBlanc(int seuil);
    vector<int> histogrammeGris(); 
    Image luminosityUp(float lum); 
    Image luminosityDown(float lum);


    Image rognerD(int nb); 
    Image rognerG(int nb);
    Image rognerH(int nb);
    Image rognerB(int nb); 
    Image retournementV(); 
    Image retournementH();
    Image rotationD();
    Image rotationG();
    Image agrandissement(int facteur); 
    
    
    void rotationCouleur();
};


string saisieNomFichier(); 
void Menu(); 
int saisieChoix();
void savePicture(Image & img); 
