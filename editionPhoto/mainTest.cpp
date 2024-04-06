#include "image.h"
using namespace std;

int mainTest() {


    vector<vector<int>> rouge = {{0, 0, 0, 0}, {0, 0, 255, 255}, {0, 255, 255, 255}, {255, 255, 255, 255}};
    vector<vector<int>> vert = {{0, 0, 255, 255}, {0, 255, 255, 255}, {255, 255, 255, 0}, {255, 255, 0, 0}};
    vector<vector<int>> bleu = {{255, 255, 0, 0},{255 ,0, 0, 0}, {0 ,0, 0, 0}, {255 ,255, 255, 255}};

    Image img = Image(rouge, vert, bleu);  
    vector<vector<int>> compoVide = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}; //déclaration d'une composition d'une couleur vide pour comparer lors des tests
    vector<vector<int>> nvGris = {{85, 85, 85, 85}, {85, 85, 170, 170}, {85, 170, 170, 85}, {255, 255, 170, 170}}; //d閏laration d'un vecteur de niveaux de gris pour comparer lors des tests
    vector<vector<int>> nvNB = {{0, 0, 0, 0}, {0, 0, 255, 255}, {0, 255, 255, 0}, {255, 255, 255, 255}}; //d閏laration d'un vecteur pour comparer lors des tests de noirEtBlanc

    cout<< endl << "----- Tests automatiques de composanteRouge -------" << endl;
    cout<<"Cas general : ";
    Image copie = Image(rouge, vert, bleu); 
    Image imgRouge = copie.composanteRouge();
    if(imgRouge.getVert()==compoVide && imgRouge.getBleu()==compoVide) cout<<"Valide"<<endl<<endl;
    else{
      cout << "Erreur : apres  copie.composanteRouge() les niveaux de vert et de bleu de l'image doivent etre a 0, on obtient imgRouge : "<<endl;
      imgRouge.affiche();
      cout<< " (attendu : rouge = {{0, 0, 0, 0}, {0, 0, 255, 255}, {0, 255, 255, 255}, {255, 255, 255, 255}};  vert = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}} , bleu = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}} )" << endl;
    }



    cout << endl << "----- Tests automatiques de detection -------" << endl;
    cout<<"Cas general (pixel dans l'Image) : ";
    if (copie.detection(0,0,255)) cout<<"Valide"<<endl<<endl;
    else cout << "Erreur : apres  detection l'image revoie "<< copie.detection(0,0,255) << " (boolen attendu : faux)" << endl;

    cout<<"Cas ou pixel n'est pas dans l'Image : ";
    if (!copie.detection(1,1,1)) cout<<"Valide"<<endl<<endl;
    else cout << "Erreur : apres  detection l'Image revoie "<< copie.detection(1,1,1) << " (boolen attendu : vrai)" << endl;



    cout << endl << "----- Tests automatiques de niveauGris -------" << endl;
    cout<<"Cas general : ";
    copie = Image(rouge, vert, bleu);   
    Image imgGris = copie.niveauGris();
    if(imgGris.getRouge()==nvGris && imgGris.getVert()==nvGris && imgGris.getBleu()==nvGris) cout<<"Valide"<<endl<<endl;
    else{
        cout << "Erreur : apres  niveauGris l'image doit cree une nouvelle image, on obtient : " <<endl;
        imgGris.affiche();
        cout<<" (attendu : rouge = {{85, 85, 85, 85}, {85, 85, 170, 170}, {85, 170, 170, 85}, {255, 255, 170, 170}},  vert = {{85, 85, 85, 85}, {85, 85, 170, 170}, {85, 170, 170, 85}, {255, 255, 170, 170}}, bleu = {{85, 85, 85, 85}, {85, 85, 170, 170}, {85, 170, 170, 85}, {255, 255, 170, 170}} )" << endl;
    }


    cout << endl << "----- Tests automatiques noirEtBlanc -------" << endl;
    copie = Image(rouge, vert, bleu); 
    Image imgNB = copie.noirEtBlanc(127);
    cout<<"seuil = 127 : ";
    if(imgNB.getRouge()==nvNB && imgNB.getVert()==nvNB && imgNB.getBleu()==nvNB) cout<<"Valide"<<endl<<endl;
    else{
        cout << "Erreur : apres  noirEtBlanc l'image doit creer une nouvelle image, on obtient imgNB : " <<endl;
          imgNB.affiche();
        cout <<" (attendu : rouge = {{0, 0, 0, 0}, {0, 0, 255, 255}, {0, 255, 255, 0}, {255, 255, 255, 255}}, vert = {{0, 0, 0, 0}, {0, 0, 255, 255}, {0, 255, 255, 0}, {255, 255, 255, 255}}, bleu = {{0, 0, 0, 0}, {0, 0, 255, 255}, {0, 255, 255, 0}, {255, 255, 255, 255}} )" << endl;
    }



    cout << endl << "----- Tests automatiques histogrammeGris -------" << endl;
    copie = Image(rouge, vert, bleu);   
    vector<int> grey = copie.histogrammeGris();
    if(grey[85]==8 && grey[170]==6 && grey[255]==2) cout<<"Valide"<<endl<<endl;
    else{
        cout << "Erreur : apres  histogrammeGris l'image doit creer remplir le vecteur grey : " <<endl;
          for(int i=0; i<grey.size(); i++) cout<<grey[i] <<"\t";
        cout <<" (attendu : grey[85]=8, grey[170]=6, grey[255]=2)"<<endl;
    }



    vector<vector<int>> r = {{0,127,138}};
    vector<vector<int>> v = {{255,200,127}};
    vector<vector<int>> b = {{0,64,120}};

    vector<vector<int>> rMoins = {{0,63,69}};
    vector<vector<int>> vMoins = {{127, 100, 63}};
    vector<vector<int>> bMoins = {{0,32,60}};

    vector<vector<int>> rPlus = {{0,126,138}};
    vector<vector<int>> vPlus = {{254,200,126}};
    vector<vector<int>> bPlus = {{0,64,120}};

    Image jpg = Image(r, v, b);


    cout << endl << "----- Tests automatiques luminosityDown -------" << endl;
    cout<<"Cas general : ";
    jpg = jpg.luminosityDown(0.5);
    if(jpg.getRouge() == rMoins && jpg.getVert() == vMoins && jpg.getBleu() == bMoins) {cout<<"Valide"<<endl<<endl;}
    else{
        cout << "Erreur : apres  luminosityDown l'image cree doit avoir diminue la luminosite : " <<endl;
        jpg.affiche();
    }

    cout << endl << "----- Tests automatiques luminosityUp -------" << endl;
    cout<< "Cas general : ";
    jpg = jpg.luminosityUp(2);
    if(jpg.getRouge() == rPlus && jpg.getVert() == vPlus && jpg.getBleu() == bPlus) {cout<<"Valide"<<endl<<endl;}
    else{
        cout << "Erreur : apres  luminosityDown l'image cree doit avoir diminue la luminosite : " <<endl;
        jpg.affiche();
    }


    string nom = "Algeria.ppm";
    Image test = Image(nom);
    test = test.agrandissement(2);
    savePicture(test);

    return 0;
}

