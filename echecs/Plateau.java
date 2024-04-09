public class Plateau {

    static final int nbLignes = 8;
    static Case[][] sesCases = new Case[nbLignes][nbLignes];


    public Plateau() {

        Case[] ligneBlancTrue = new Case[nbLignes];
        for (int j = 0; j < nbLignes; j+=2) {
            ligneBlancTrue[j] = new Case("Blanc", true);
            ligneBlancTrue[j+1] = new Case("Noir", true);
        }
        

        Case[] ligneNoirTrue = new Case[nbLignes];
        for (int j = 0; j < nbLignes; j+=2) {
            ligneNoirTrue[j] = new Case("Noir", true);
            ligneNoirTrue[j+1] = new Case("Blanc", true);
        }
        

        Case[] ligneBlancFalse = new Case[nbLignes];
        for (int j = 0; j < nbLignes; j+=2) {
            ligneBlancFalse[j] = new Case("Blanc", false);
            ligneBlancFalse[j+1] = new Case("Noir", false);
        }

        Case[] ligneNoirFalse = new Case[nbLignes];
        for (int j = 0; j < nbLignes; j+=2) {
            ligneNoirFalse[j] = new Case("Noir", false);
            ligneNoirFalse[j+1] = new Case("Blanc", false);
        }
            

        sesCases[0]=ligneBlancTrue;
        sesCases[1]=ligneNoirTrue;
        sesCases[6]=ligneBlancTrue;  
        sesCases[7]=ligneBlancTrue; 

        for(int i=2; i<6; i+=2){
            sesCases[i]=ligneBlancFalse;
            sesCases[i+1]=ligneNoirFalse;
        }
        
    }


    public String toString(){
        String plateau = "Etat du plateau :\n";
        for(int i = 0; i<sesCases.length; i++){
            for(int j = 0; j<sesCases[i].length; j++){
                plateau+=sesCases[i][j].estOccupe() + "\t";
            }
            plateau+="\n";
        }
        return plateau;
    }
    
    
    public static void main(String args[]){
        Plateau p = new Plateau();
        System.out.println(p);

    }
}