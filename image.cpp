#include "image.h"
#include <iostream>
#include <fstream>


Image::Image(vector<vector<int>> &rouge, vector<vector<int>> &vert, vector<vector<int>> &bleu){

    bool valide = rouge.size() == vert.size() && rouge.size() == bleu.size() && bleu.size() == vert.size();
    int i=0;

    while (valide && i < rouge.size()){ 
        valide = rouge[i].size() == vert[i].size() && rouge[i].size() == bleu[i].size() && bleu[i].size() == vert[i].size();
        i++;
    }

    if (!valide) throw invalid_argument("Les vecteurs ne sont pas tous de même taille ");

    _rouge = rouge;
    _vert = vert;
    _bleu = bleu;
    _longueur = rouge[0].size();
    _largeur = rouge.size();
}



Image::Image(){_rouge={}; _vert={}; _bleu={}; _largeur=0; _longueur=0;}



vector<vector<int>> Image::getRouge()const{return _rouge;}
vector<vector<int>> Image::getVert()const{return _vert;}
vector<vector<int>> Image::getBleu()const{return _bleu;}
int Image::getLongueur()const{return _longueur;}
int Image::getLargeur()const{return _largeur;}



void Image::affiche()const{
    cout << "Affichage de l'image de taille " << _largeur << "x"<< _longueur << " : " << endl<<endl;
    for(int i =0; i<_largeur; i++){
        for(int j=0; j<_longueur; j++){
            cout << "Niveau de rouge : "<< _rouge[i][j] <<"\t" << endl;
            cout << "Niveau de vert : "<< _vert[i][j] <<"\t" << endl;
            cout << "Niveau de bleu : "<< _bleu[i][j] <<"\t" << endl<<endl;
        }
    }
    cout<<endl;
}



Image Image::copie(){return Image(_rouge, _vert, _bleu);}



Image Image::composanteRouge()const{

    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;

    Image imgRouge = Image(rouge, vert, bleu);
    for(int i=0; i<imgRouge._largeur; i++){
        for (int j=0; j<imgRouge._longueur; j++){
            imgRouge._vert[i][j]=0;
            imgRouge._bleu[i][j]=0;
        }
    }
    return imgRouge;
}



bool Image::detection(int R, int V, int B)const{
    bool existe = false; int i=0, j=0;
    while(!existe && i<_largeur && j<_longueur){
        existe = _rouge[i][j] == R && _vert[i][j] == V && _bleu[i][j] == B;
        i++; j++;
    }
    return existe;
}



Image Image::niveauGris(){
    Image imgGris = Image(_rouge, _vert, _bleu);

    for(int i=0; i<imgGris._largeur; i++){
        for(int j=0; j<imgGris._longueur; j++){
            imgGris._rouge[i][j] = (_rouge[i][j] + _vert[i][j] + _bleu[i][j])/3;
            imgGris._vert[i][j] = (_rouge[i][j] + _vert[i][j] + _bleu[i][j])/3;
            imgGris._bleu[i][j] = (_rouge[i][j] + _vert[i][j] + _bleu[i][j])/3;
        }
    }
    return imgGris;
}



Image Image::noirEtBlanc(int seuil){

    Image noirBlanc = Image(_rouge, _vert, _bleu).niveauGris();

    for(int i=0; i<noirBlanc._largeur; i++){
        for (int j=0; j<noirBlanc._longueur; j++){
            if(noirBlanc._rouge[i][j]<seuil){
                noirBlanc._rouge[i][j] = 0;
                noirBlanc._vert[i][j] = 0;
                noirBlanc._bleu[i][j] = 0;
            }
            else{
                noirBlanc._rouge[i][j] = 255;
                noirBlanc._vert[i][j] = 255;
                noirBlanc._bleu[i][j] = 255;
            }
        }
    }
    return noirBlanc;
}



vector<int> Image::histogrammeGris(){
    vector<int> histGris(256, 0);
    Image gris = Image(_rouge, _vert, _bleu).niveauGris();
    for(int i = 0; i < gris._largeur; i++)
        for(int j=0; j< gris._longueur; j++)
            histGris[gris._rouge[i][j]]++;
    return histGris;
}



Image Image::luminosityUp(float lum){

    while(lum<1){cout<<"Erreur : la valeur saisie doit etre superieure a 1 \n"; cin>>lum;}

    Image lumPlus = Image(_rouge, _vert, _bleu);

    for(int i =0; i<_largeur; i++){
        for(int j=0; j<_longueur; j++){
            lumPlus._rouge[i][j]*=lum;
            lumPlus._bleu[i][j]*=lum;
            lumPlus._vert[i][j]*=lum;

            if(lumPlus._rouge[i][j]>255) lumPlus._rouge[i][j]=255;
            if(lumPlus._vert[i][j]>255) lumPlus._vert[i][j]=255;
            if(lumPlus._bleu[i][j]>255) lumPlus._bleu[i][j]=255;
        }
    }
    return lumPlus;
}



Image Image::luminosityDown(float lum){
    while(lum>1){cout<<"Erreur : la valeur saisie doit etre inferieure a 1 \n";cin>>lum;}
    Image lumMoins = Image(_rouge, _vert, _bleu);
        for(int i =0; i<_largeur; i++){
            for(int j=0; j<_longueur; j++){
                lumMoins._rouge[i][j]*=lum;
                lumMoins._bleu[i][j]*=lum;
                lumMoins._vert[i][j]*=lum;}
    }
    return lumMoins;
}



string saisieNomFichier(){
    string nomFichier; bool valide;
    do{
        cout << "Veuillez saisir le nom du fichier image sur lequel vous souhaitez travailler : "<< endl;
        cin >> nomFichier;
        if(nomFichier.length()<4) cout<<"Nom du fichier invalide...";
        valide = nomFichier.substr(nomFichier.length()-4,nomFichier.length()-1)== ".ppm";
        if(!valide) cout<<"Le nom de fichier doit finir par .ppm... ";
    } while(!valide);
    return nomFichier;
}



void Menu(){
    cout<<endl<<"----------------- Menu -------------------"<<endl;
    cout<<"Voici les différentes fonctionnalités disponibles :"<<endl;
    cout<<"1 : Copie d'une image"<<endl;
    cout<<"2 : Composante de rouge d'une image"<<endl;
    cout<<"3 : Détection d'un pixel dans l'image"<<endl;
    cout<<"4 : Niveau de gris d'une image"<<endl;
    cout<<"5 : Noir et blanc de l'image "<<endl;
    cout<<"6 : Histogramme de gris de l'image "<<endl;
    cout<<"7 : Augmentation de la luminosité "<<endl;
    cout<<"8 : Diminution de la luminosité "<<endl;
    cout<<"9 : Rogner le haut de l'image "<<endl;
    cout<<"10 : Rogner le bas de l'image "<<endl;
    cout<<"11 : Rogner la gauche de l'image "<<endl;
    cout<<"12 : Rogner la droite de l'image "<<endl;
    cout<<"13 : Retournement vertical "<<endl;
    cout<<"14 : Retournement horizontal "<<endl;
    cout<<"15 : Rotation à droite "<<endl;
    cout<<"16 : Rotation à gauche "<<endl;
    cout<<"17 : Agrandissement de l'image"<<endl;
    cout<<"18 : Rotation des couleurs "<<endl;
    cout<<"19 : QUITTER "<<endl<<endl;
}



int saisieChoix(){
    int choix;
    cout<<"Veuillez saisir la modification à effectuer : "<<endl;
    cin>>choix;
    return choix;
}



Image::Image(string &nom){

    vector<vector<int>> red;
    vector<vector<int>> green;
    vector<vector<int>> blue;

    string line; 
    string format; 
    string name; 
    vector <int> mypixels; 
    ifstream entree; 
    int hauteur; 
    int taille;

    name = nom;
    
    entree.open(name);

    while(!entree){

        cerr << "Erreur ! Impossible de lire de fichier " << name << " ! " << endl;
        cerr << "Veuillez redonner le nom du fichier à ouvrir. Attention, ce fichier doit avoir un nom du type fichier.ppm." << endl;
        cin >> name;
        entree.open(name);
    }

    entree >> format;

    getline(entree, line);
    getline(entree, line);
    entree >> taille >> hauteur;
    getline(entree, line); 

    while (format != "P3"){
        if (format != "P3"){
            cerr << "Erreur! L'image que vous nous avez donnee a un format ne verifiant pas les conditions requises." << endl;
            cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et non en brut." << endl;
        }
	entree.close();

        do{
            cerr << "Veuillez redonner un nom de fichier qui respecte les conditions de format et de taille. Attention, ce nom doit etre de la forme nom.ppm." << endl;
            cin >> name;
            entree.open(name); 
        }while(!entree);

        entree >> format;
        getline(entree, line); 
         
        getline(entree, line);
        
        entree >> taille >> hauteur; 
        getline(entree, line);
    }

    getline(entree, line);
    
    
    int pix;
    mypixels.resize(3*taille*hauteur); // taille fixe : on alloue une fois pour toutes
    for (int i = 0; i < 3*taille*hauteur; i++){
      entree >> pix;
      mypixels[i]=pix;
    }
   
   
   int val;
    red.resize(hauteur);
    green.resize(hauteur);
    blue.resize(hauteur);
    for(int i = 0; i < hauteur; i++){
        vector <int> ligneR(taille);
        vector <int> ligneB(taille);  
        vector <int> ligneG(taille);
        for(int j = 0; j < taille; j++){
            val =  mypixels[3*j + 3*taille*i];
            ligneR[j]=val;
            val = mypixels[3*j + 1 + 3*taille*i];
            ligneG[j]=val;
            val = mypixels[3*j + 2 + 3*taille*i];
            ligneB[j]=val;
        }
        red[i]=ligneR;
        green[i]=ligneG;
        blue[i]=ligneB;
    }

    cout << "L'image " << name << " a bien été chargée. " << endl;
     entree.close();

    _rouge = red;
    _vert = green;
    _bleu = blue;
    _longueur = red[0].size();
    _largeur = red.size();
 }



void savePicture(Image & img){
    string nom; ofstream sortie; bool valide;
    do{
        cout << "Comment souhaitez-vous nommer votre fichier ?  "<<endl;
        cin >> nom;
        if(nom.length()<4) cout<<"Nom du fichier invalide...";
        valide = nom.substr(nom.length()-4, nom.length()-1)== ".ppm";
        if(!valide) cout<<"Le nom de fichier doit finir par .ppm... ";
    } while(!valide);sortie.open(nom);

    if(sortie.is_open()){
    sortie << "P3" << endl;
    sortie << img.getLongueur() << " " << img.getLargeur() << endl << 255 <<endl;
    for(int i=0; i<img.getLargeur(); i++){
        for(int j=0; j<img.getLongueur(); j++){
            sortie<<img.getRouge()[i][j]<<endl;
            sortie<<img.getVert()[i][j]<<endl;
            sortie<<img.getBleu()[i][j]<<endl;
        }
    }
    cout<<"L'image a bien ete sauvegardee. "<<endl<<endl;

    sortie.close();}
 }



 Image Image::rognerB(int nb){
    if(nb>_largeur) throw invalid_argument("Vous ne pouvez pas supprimer plus de lignes qu'il n'y en a dans l'image ! ");
    Image img = Image(_rouge, _vert, _bleu);
    for(int i=0; i<nb; i++){
        img._rouge.pop_back();
        img._vert.pop_back();
        img._bleu.pop_back();
    }
    img._largeur-=nb;
    return img;
 }



 Image Image::rognerH(int nb){
    if(nb>_largeur) throw invalid_argument("Vous ne pouvez pas supprimer plus de lignes qu'il n'y en a dans l'image ! ");
    Image img = Image(_rouge, _vert, _bleu);
    reverse(img._rouge.begin(), img._rouge.end());
    reverse(img._vert.begin(), img._vert.end());
    reverse(img._bleu.begin(), img._bleu.end());
    for(int i=0; i<nb; i++){
        img._rouge.pop_back();
        img._vert.pop_back();
        img._bleu.pop_back();
    }
    reverse(img._rouge.begin(), img._rouge.end());
    reverse(img._vert.begin(), img._vert.end());
    reverse(img._bleu.begin(), img._bleu.end());
    img._largeur-=nb;
    return img;
 }



 Image Image::rognerD(int nb){
    if(nb>_longueur) throw invalid_argument("Vous ne pouvez pas supprimer plus de colonnes qu'il n'y en a dans l'image ! ");
    Image img = Image(_rouge, _vert, _bleu);
    for(int i=0; i<nb; i++){
        img._rouge[i].pop_back();
        img._vert[i].pop_back();
        img._bleu[i].pop_back();
    }
    img._longueur-=nb;
    return img;
 }



 Image Image::rognerG(int nb){
    if(nb>_longueur) throw invalid_argument("Vous ne pouvez pas supprimer plus de colonnes qu'il n'y en a dans l'image ! ");
    Image img = Image(_rouge, _vert, _bleu);
    for(int i=0; i<_largeur; i++){
        reverse(img._rouge[i].begin(), img._rouge[i].end());
        reverse(img._vert[i].begin(), img._vert[i].end());
        reverse(img._bleu[i].begin(), img._bleu[i].end());
        for(int j=0; j<nb; j++){
            img._rouge[i].pop_back();
            img._vert[i].pop_back();
            img._bleu[i].pop_back();
        }
    reverse(img._rouge[i].begin(), img._rouge[i].end());
    reverse(img._vert[i].begin(), img._vert[i].end());
    reverse(img._bleu[i].begin(), img._bleu[i].end());
    }
    img._longueur-=nb;
    return img;
 }



Image Image::retournementV(){
    Image img = Image(_rouge, _vert, _bleu);
    reverse(img._rouge.begin(), img._rouge.end());
    reverse(img._vert.begin(), img._vert.end());
    reverse(img._bleu.begin(), img._bleu.end());
    return img;
}



Image Image::retournementH(){
    Image img = Image(_rouge, _vert, _bleu);
    for(int i=0; i<_largeur; i++){
        reverse(img._rouge[i].begin(), img._rouge[i].end());
        reverse(img._vert[i].begin(), img._vert[i].end());
        reverse(img._bleu[i].begin(), img._bleu[i].end());
    }
    return img;
}



Image Image::rotationD(){
    vector<vector<int>> rouge (_longueur, vector<int> (_largeur));
    vector<vector<int>> vert (_longueur, vector<int> (_largeur));
    vector<vector<int>> bleu (_longueur, vector<int> (_largeur));
    for(int i=0; i<_longueur; i++){
        for(int j=0; j<_largeur; j++){
            rouge[i][j] = _rouge[_largeur-j-1][i];
            vert[i][j] = _vert[_largeur-j-1][i];
            bleu[i][j] = _bleu[_largeur-j-1][i];
        }
    }
    Image img = Image(rouge, vert, bleu);
    return img;
}



Image Image::rotationG(){
    vector<vector<int>> rouge (_longueur, vector<int> (_largeur));
    vector<vector<int>> vert (_longueur, vector<int> (_largeur));
    vector<vector<int>> bleu (_longueur, vector<int> (_largeur));
    for(int i=0; i<_longueur; i++){
        for(int j=0; j<_largeur; j++){
            rouge[i][j] = _rouge[j][_longueur-i-1];
            vert[i][j] = _vert[j][_longueur-i-1];
            bleu[i][j] = _bleu[j][_longueur-i-1];
        }
    }
    Image img = Image(rouge, vert, bleu);
    return img;
}



Image Image::agrandissement(int facteur){
    vector<vector<int>> rouge (facteur*_largeur, vector<int> (facteur*_longueur));
    vector<vector<int>> vert (facteur*_largeur, vector<int> (facteur*_longueur));
    vector<vector<int>> bleu (facteur*_largeur, vector<int> (facteur*_longueur));
     for (int i = 0; i < _largeur; ++i) {
        for (int j = 0; j < _longueur; ++j) {
            for (int k = 0; k < facteur; ++k) {
                for (int l = 0; l < facteur; ++l) {
                    rouge[i * facteur + k][j * facteur + l] = _rouge[i][j];
                    vert[i * facteur + k][j * facteur + l] = _vert[i][j];
                    bleu[i * facteur + k][j * facteur + l] = _bleu[i][j];}}}}
    Image img = Image(rouge, vert, bleu);
    return img;
}



void Image::rotationCouleur(){

    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;


    vert = _rouge;
    bleu = _vert;
    rouge= _bleu;


    _rouge = rouge;
    _vert = vert;
    _bleu = bleu;
}