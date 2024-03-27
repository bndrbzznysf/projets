#include "image.h"

//premier constructeur : initialisation de l'Image
Image::Image(vector<vector<int>> &rouge, vector<vector<int>> &vert, vector<vector<int>> &bleu){
    bool valide = rouge.size() == vert.size() && rouge.size() == bleu.size() && bleu.size() == vert.size();
    int i=0;

    while (valide && i < rouge.size()){ //on vérifie que tous les vecteurs sont de même taille
        valide = rouge[i].size() == vert[i].size() && rouge[i].size() == bleu[i].size() && bleu[i].size() == vert[i].size();
        i++;}

    if (!valide) throw invalid_argument("Les vecteurs ne sont pas tous de même taille ");

    _rouge = rouge;
    _vert = vert;
    _bleu = bleu;
    _longueur = rouge[0].size();
    _largeur = rouge.size();
}


//constructeur vide
Image::Image(){_rouge={}; _vert={}; _bleu={}; _largeur=0; _longueur=0;}

//récupèrent les attributs privés et permettent de les renvoyer
vector<vector<int>> Image::getRouge()const{return _rouge;}
vector<vector<int>> Image::getVert()const{return _vert;}
vector<vector<int>> Image::getBleu()const{return _bleu;}
int Image::getLongueur()const{return _longueur;}
int Image::getLargeur()const{return _largeur;}

//affichage de Image
void Image::affiche()const{
    cout << "Affichage de l'image de taille " << _largeur << "x"<< _longueur << " :" << endl<<endl;
    for(int i =0; i<_largeur; i++){
        for(int j=0; j<_longueur; j++){
            cout << "Niveau de rouge : "<< _rouge[i][j] <<"\t" << endl;
            cout << "Niveau de vert : "<< _vert[i][j] <<"\t" << endl;
            cout << "Niveau de bleu : "<< _bleu[i][j] <<"\t" << endl<<endl;}
    }
    cout<<endl;
}


//copie
Image Image::copie(){return Image(_rouge, _vert, _bleu);}


//nouvelle image avec le niveau de vert et de bleu à 0
Image Image::composanteRouge()const{
		vector<vector<int>> rouge = _rouge;
		vector<vector<int>> vert = _vert;
		vector<vector<int>> bleu = _bleu;

    Image imgRouge = Image(rouge, vert, bleu);
    for(int i=0; i<imgRouge._largeur; i++){
        for (int j=0; j<imgRouge._longueur; j++){
            imgRouge._vert[i][j]=0;
            imgRouge._bleu[i][j]=0;}
    }
    return imgRouge;
}


//prend en paramètre le code RVB d’un pixel et renvoie vrai s'il existe dans l’image cible.
bool Image::detection(int R, int V, int B)const{
    bool existe = false; int i=0, j=0;
    while(!existe && i<_largeur && j<_longueur){
        existe = _rouge[i][j] == R && _vert[i][j] == V && _bleu[i][j] == B;
        i++; j++;}
    return existe;
}


//crée une nouvelle image à partir des niveaux de gris d'une autre image
Image Image::niveauGris(){
    Image imgGris = Image(_rouge, _vert, _bleu);

    for(int i=0; i<imgGris._largeur; i++){
        for(int j=0; j<imgGris._longueur; j++){
            imgGris._rouge[i][j] = (_rouge[i][j] + _vert[i][j] + _bleu[i][j])/3;
            imgGris._vert[i][j] = (_rouge[i][j] + _vert[i][j] + _bleu[i][j])/3;
            imgGris._bleu[i][j] = (_rouge[i][j] + _vert[i][j] + _bleu[i][j])/3;}
    }
    return imgGris;
}


//crée une image en noir et blanc d'une image cible
Image Image::noirEtBlanc(int seuil){
    Image noirBlanc = Image(_rouge, _vert, _bleu).niveauGris();
    for(int i=0; i<noirBlanc._largeur; i++){
        for (int j=0; j<noirBlanc._longueur; j++){
            if(noirBlanc._rouge[i][j]<seuil){
                noirBlanc._rouge[i][j] = 0;
                noirBlanc._vert[i][j] = 0;
                noirBlanc._bleu[i][j] = 0;}
            else{
                noirBlanc._rouge[i][j] = 255;
                noirBlanc._vert[i][j] = 255;
                noirBlanc._bleu[i][j] = 255;}
        }
    }
    return noirBlanc;
}


//histogramme de gris d'une Image
vector<int> Image::histogrammeGris(){
vector<int> histGris(256, 0);
Image gris = Image(_rouge, _vert, _bleu).niveauGris();
    for(int i = 0; i < gris._largeur; i++)
        for(int j=0; j< gris._longueur; j++)
            histGris[gris._rouge[i][j]]++;
    return histGris;
}



//nouvelle image avec la luminosité augmentée
Image Image::luminosityUp(float lum){
    while(lum<1){cout<<"Erreur : la valeur saisie doit etre superieure a 1 \n";cin>>lum;}
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



//nouvelle Image avec la luminosité diminuée
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



//saisie du nom du fichier
string saisieNomFichier(){
    string nomFichier; bool valide;
    do{
        cout << "Veuillez saisir le nom du fichier image sur lequel vous souhaitez travailler : "<<endl;
        cin >> nomFichier;
        if(nomFichier.length()<4) cout<<"Nom du fichier invalide...";
        valide = nomFichier.substr(nomFichier.length()-4,nomFichier.length()-1)== ".ppm";
        if(!valide) cout<<"Le nom de fichier doit finir par .ppm... ";
    }while(!valide);
    return nomFichier;
}


//menu proposant les différentes fonctionnalités offertes par le logiciel
void Menu(){
    cout<<endl<<"----------------- Menu -------------------"<<endl;
    cout<<"Voici les differentes fonctionnalites disponibles :"<<endl;
    cout<<"1 : copie "<<endl;
    cout<<"2 : composante rouge "<<endl;
    cout<<"3 : detection "<<endl;
    cout<<"4 : niveauGris "<<endl;
    cout<<"5 : noirEtBlanC "<<endl;
    cout<<"6 : histogrammeGris "<<endl;
    cout<<"7 : luminosityUp "<<endl;
    cout<<"8 : luminosityDown "<<endl;
    cout<<"9 : rognerH "<<endl;
    cout<<"10 : rognerB "<<endl;
    cout<<"11 : rognerG "<<endl;
    cout<<"12 : rognerD "<<endl;
    cout<<"13 : retournement vertical "<<endl;
    cout<<"14 : retournement horizontal "<<endl;
    cout<<"15 : rotation droite "<<endl;
    cout<<"16 : rotation gauche "<<endl;
    cout<<"17 : agrandissement "<<endl;
    cout<<"18 : rotationCouleur "<<endl;
    cout<<"19 : QUITTER "<<endl<<endl;
}


//saisie du choix de l'utilisateur
int saisieChoix(){
    int choix;
    cout<<"Veuillez saisir la modification a effectuer : "<<endl;
    cin>>choix;
    return choix;
}


//deuxième constructeur : initialisation de l'Image
Image::Image(string &nom){

    vector<vector<int>> red;
    vector<vector<int>> green;
    vector<vector<int>> blue;

    string line; // pour recuperer les lignes du fichier image au format .ppm, qui est code en ASCII.
    string format; //pour recuperer le format de l'image : celui-ci doit être de la forme P3
    string name; // au cas où l'utilisateur se trompe dans le nom de l'image a charger, on redemande le nom.
    int taille;
    vector <int> mypixels; // pour recuperer les donnees du fichier de maniere lineaire. On repartira ensuite ces donnees dans les tableaux correspondants
    ifstream entree; // Declaration d'un "flux" qui permettra ensuite de lire les donnees de l'image.
    int hauteur; // pour bien verifier que l'image est carree, et de taille respectant les conditions fixees par l'enonce
    // Initialisation des variables
    name = nom;
    // Permet d'ouvrir le fichier portant le nom picture
    // ouverture du fichier portant le nom picture
    entree.open(name);
    // On verifie que le fichier a bien ete ouvert. Si cela n'est pas le cas, on redemande un nom de fichier valide
    while (!entree){
        //cin.rdbuf(oldbuf);
        cerr << "Erreur! Impossible de lire de fichier " << name << " ! " << endl;
        cerr << "Redonnez le nom du fichier a ouvrir SVP. Attention ce fichier doit avoir un nom du type nom.ppm." << endl;
        cin >> name;
        entree.open(name); //relance
    }
    // Lecture du nombre definissant le format (ici P3)
    entree >> format;
    // on finit de lire la ligne (caractere d'espacement)
    getline(entree, line);
    // Lecture du commentaire
    getline(entree, line);
    //lecture des dimensions
    entree >> taille >> hauteur;
    getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    // On verifie que l'image a une taille qui verifie bien les conditions requises par l'enonce.
    // Si cela n'est pas le cas, on redemande un fichier valide, et ce, tant que necessaire.
    while (format != "P3"){
        if (format != "P3"){
            cerr << "Erreur! L'image que vous nous avez donnee a un format ne verifiant pas les conditions requises." << endl;
            cerr << "L'image que vous nous avez donnee doit etre codee en ASCII et non en brut." << endl;
        }
	entree.close();
        // On va redemander un nom de fichier valide.
        do{
            cerr << "Veuillez redonner un nom de fichier qui respecte les conditions de format et de taille. Attention, ce nom doit etre de la forme nom.ppm." << endl;
            cin >> name;
            entree.open(name); // relance
        }while(!entree);
         // Lecture du nombre definissant le format (ici P3)
         entree >> format;
         getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
        // Lecture du commentaire
        getline(entree, line);
        //lecture des dimensions
        entree >> taille >> hauteur; // relance
        getline(entree, line); // on finit de lire la ligne (caractere d'espacement)
    }
    //Lecture de la valeur max
    getline(entree, line);
    //Lecture des donnees et ecriture dans les tableaux :
    // Pour plus de simplicite, on stocke d'abord toutes les donnees dans mypixels
    // dans l'ordre de lecture puis ensuite on les repartira dans les differents tableaux.
    //Les donnees stockees dans mypixels sont de la forme RGB RGB RGB ....
    // Il faudra donc repartir les valeurs R correspondant a la composante rouge de l'image
    // dans le tableau red, de même pour G et B.
    int pix;
    mypixels.resize(3*taille*hauteur); // taille fixe : on alloue une fois pour toutes
    for (int i = 0; i < 3*taille*hauteur; i++){
      entree >> pix;
      mypixels[i]=pix;
    }
    // Remplissage des 3 tableaux : on repartit maintenant les valeurs dans les bonnes composantes
    // Comme dans mypixels, les donnees sont stockees de la maniere suivante : RGB RGB RGB, il faut mettre
    // les valeurs correspondant a la composante rouge dans red, ...
    // Ainsi, les valeurs de la composante rouge correspondent aux valeurs stockes aux indices
    // congrus a 0 mod 3 dans mypixels, que les valeurs de la composante verte correspond aux valeurs
    // stockes aux indices sont congrus a 1 mod 3, ...
     // les valeurs d'une ligne
    int val;
    red.resize(hauteur);
    green.resize(hauteur);
    blue.resize(hauteur);
    for (int i = 0; i < hauteur; i++){
      vector <int> ligneR(taille);
      vector <int> ligneB(taille);  // les lignes ont toutes la même taille
      vector <int> ligneG(taille);
      for (int j = 0; j < taille; j++){
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
    // Informations a l'utilisateur pour dire que tout s'est bien passe
    cout << "L'image " << name << " a bien ete chargee. " << endl;
     entree.close();
    //affectation des attributs privés de l'Image
    _rouge = red;
    _vert = green;
    _bleu = blue;
    _longueur = red[0].size();
    _largeur = red.size();
 }


//enregistrement d'une image dans un nouveau fichier
void savePicture(Image & img){
    string nom; ofstream sortie; bool valide;
    do{
        cout << "Comment souhaitez-vous nommer votre fichier ?  "<<endl;
        cin >> nom;
        if(nom.length()<4) cout<<"Nom du fichier invalide...";
        valide = nom.substr(nom.length()-4, nom.length()-1)== ".ppm";
        if(!valide) cout<<"Le nom de fichier doit finir par .ppm... ";
    }while(!valide);sortie.open(nom);

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


 //rogner en bas
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


//rogner en haut
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


 //rogner à droite
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


//rogner à gauche
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


//retournement vertical
Image Image::retournementV(){
    Image img = Image(_rouge, _vert, _bleu);
    reverse(img._rouge.begin(), img._rouge.end());
    reverse(img._vert.begin(), img._vert.end());
    reverse(img._bleu.begin(), img._bleu.end());
    return img;
}


//retournement horizontal
Image Image::retournementH(){
    Image img = Image(_rouge, _vert, _bleu);
    for(int i=0; i<_largeur; i++){
        reverse(img._rouge[i].begin(), img._rouge[i].end());
        reverse(img._vert[i].begin(), img._vert[i].end());
        reverse(img._bleu[i].begin(), img._bleu[i].end());
    }
    return img;
}


//rotation à droite
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



//rotation à gauche
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


//ROTATION COULEUR
void Image::rotationCouleur(){
    //déclaration de vecteurs temporaires pour effectuer les changements de valeurs de _rouge, _vert et _bleu
    vector<vector<int>> rouge = _rouge;
    vector<vector<int>> vert = _vert;
    vector<vector<int>> bleu = _bleu;

    //on fait une rotation des valeurs dans les tableaux temporaires en affectant du vert à la place du rouge, du bleu à la place du vert et du rouge à la place du bleu
    vert = _rouge;
    bleu = _vert;
    rouge= _bleu;

    //on affecte les tableaux en tant qu'attributs définitifs de l'image
    _rouge = rouge;
    _vert = vert;
    _bleu = bleu;
}
