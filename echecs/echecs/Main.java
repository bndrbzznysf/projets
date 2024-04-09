package echecs;

import javax.swing.*;
import java.awt.*;

public class Main extends JFrame {


   public static void main(String[] args) {

      //Window config
      JFrame window = new JFrame("Jeux d'échecs par Ines <3");
      Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
      window.setSize(1200, 1200);
      window.setLocation(dim.width/2 - window.getWidth()/2, dim.height/2 - window.getHeight()/2);


      //Adding the board
      window.add(new Board());


      //Icon
      ImageIcon image = new ImageIcon("Waluigi.ico");
      window.setIconImage(image.getImage());

      window.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
      window.setResizable(false);
      window.setVisible(true);
      
   }
}