public class Case {

    String couleur;
    boolean occupe;
    Piece piece;

    public Case(String couleur, boolean occupe) {
        this.couleur = couleur;
        this.occupe = occupe;
    }

    public String getCouleur(){
        return this.couleur;
    }

    public void setCouleur(String couleur){
        this.couleur = couleur;
    }

    public boolean estOccupe(){
        return this.occupe;
    }

    public void setOccupe(Piece piece){
        this.occupe = true;
        this.piece = piece;
    }

    public void setNonOccupe(){
        this.occupe = false;
        this.piece = null;
    }

    public Piece getPion(){
        return this.piece;
    }

    public void setPion(Piece pion){
        this.piece = pion;
    }

}