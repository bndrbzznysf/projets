public abstract class Piece {

    String nom;
    String couleur;
    int nbDeplacements;
    int xPos;
    int yPos;
    

    Piece(String nom, String couleur, int xPos, int yPos){
        this.nom = nom;
        this.couleur = couleur;
        this.xPos = xPos;
        this.yPos = yPos;
    }

}