#include "image.h"
const int FIN = 19;

int main()
{
    string nom;
    Image img; int choix;

    do{
        nom = saisieNomFichier();
        img = Image(nom);
        Menu();
        choix = saisieChoix();
        vector<int> histGris; float lum; int rogne, facteur;

        switch(choix){

            case 1: img = img.copie(); savePicture(img); break;
            case 2: {img = img.composanteRouge(); savePicture(img); break;}
            case 3: int R, V, B;
                cout<<"Veuillez saisir les composantes de Rouge, Vert et Bleu du pixel à rechercher dans l'image : "<<endl; cin >>R>>V>>B;
                if(img.detection(R, V, B)) cout<<"Le pixel se trouve dans l'image"<<endl; else cout<<"Le pixel ne se trouve pas dans l'image"<<endl; break;
            case 4: img = img.niveauGris(); savePicture(img); break;
            case 5: int seuil; cout<<"Veuillez saisir un seuil : "<<endl; cin>>seuil; img = img.noirEtBlanc(seuil); savePicture(img); break;
            case 6: histGris = img.histogrammeGris();
                for(int i=0; i<histGris.size(); i++){cout<<"Nombre de pixels dont le niveau de gris est "<<i<<" : "<<histGris[i]<<endl;} break;
            case 7: cout<<"Facteur par lequel la luminosite doit etre augmentee : "; cin>>lum; img = img.luminosityUp(lum); savePicture(img); break;
            case 8: cout<<"Facteur par lequel la luminosite doit etre diminuee : "; cin>>lum; img = img.luminosityDown(lum); savePicture(img); break;
            case 9: cout<<"De combien de lignes souhaitez-vous rogner votre image ? "; cin>>rogne; img = img.rognerH(rogne); savePicture(img); break;
            case 10: cout<<"De combien de lignes souhaitez-vous rogner votre image ? "; cin>>rogne; img = img.rognerB(rogne); savePicture(img); break;
            case 11: cout<<"De combien de colonnes souhaitez-vous rogner votre image ? "; cin>>rogne; img = img.rognerG(rogne); savePicture(img); break;
            case 12: cout<<"De combien de colonnes souhaitez-vous rogner votre image ? "; cin>>rogne; img = img.rognerD(rogne); savePicture(img); break;
            case 13: img = img.retournementV(); savePicture(img); break;
            case 14: img = img.retournementH(); savePicture(img); break;
            case 15: img = img.rotationD(); savePicture(img); break;
            case 16: img = img.rotationG(); savePicture(img); break;
            case 17: cout<<"Par quel facteur souhaitez-vous agrandir votre image ? "; cin>>facteur; img = img.agrandissement(facteur); savePicture(img); break;
            case 18: img.rotationCouleur(); savePicture(img); break;
            case FIN: cout<<"Au revoir ! "; break;
            default: cout<<"Ceci n'est pas une option proposée... ";
        }
    } while (choix!=FIN);

    return 0;
}
