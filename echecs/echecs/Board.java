package echecs;

import javax.swing.*;
import java.awt.*;

public class Board extends JPanel {

    public Board(){

        //Board
        setLayout(new GridLayout(8, 8));
        for(int i = 0; i<8; i+=2){
            for(int j = 0; j<8; j+=2){
               Panel panelBlanc = new Panel();
               panelBlanc.setBackground(new Color(237, 239, 242));
               add(panelBlanc);
   
               Panel panelNoir = new Panel();
               panelNoir.setBackground(new Color(6, 40, 94));
               add(panelNoir);
            }
   
            for(int j = 0; j<8; j+=2){
               Panel panelNoir = new Panel();
               panelNoir.setBackground(new Color(6, 40, 94));
               add(panelNoir);
               
               Panel panelBlanc = new Panel();
               panelBlanc.setBackground(new Color(237, 239, 242));
               add(panelBlanc);
            }
         }
    }

}