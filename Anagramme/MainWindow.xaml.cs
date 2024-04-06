using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace AnagrammeWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        
        private String[] tabMots;
        private String mot;
        private const int NB_MAX_ESSAIS = 10;
        private int essais = 1;
        private int nbParties = 0;


        public MainWindow()
        {
            InitializeComponent();
        }



        private void initialisation()
        {
            tabMots = new String[]
            {"AVION",
            "BALAI",
            "VOITURE",
            "LIVRE",
            "ARBRE",
            "POMME",
            "CLEMENTINE",
            "CRAYON",
            "LIMITES",
            "OISEAU",
            "TOMATE",
            "CHAT",
            "DRAPEAU",
            "SOURIS",
            "ORDINATEUR",
            "CHAISE",
            "FOURMI",
            "JOURNAL",
            "OXYGENE",
            "CROCHET",
            "TROUSSE",
            "ECRAN"};

            mot = tabMots[0];
            essais = 1;
            LBLMotADeviner.Content = melanger(mot);
        }



        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            initialisation();
        }


        private String melanger(String chaine)
        {
            Random rand = new Random();
            StringBuilder melange = new StringBuilder();
            for (int i = 0; i < chaine.Length; i++) {
                melange.Insert(rand.Next(melange.Length), chaine[i]);
             }
            return melange.ToString();
        }


        private void nouvellePartie()
        {
            Random rand = new Random();
            mot = tabMots[rand.Next(tabMots.Length)];
            essais = 0;
            LBLMotADeviner.Content = melanger(mot);
            LSTBessais.Items.Clear();
        }


        private void motCorrect()
        {
            if (MessageBox.Show("Vous avez trouvé le mot !\nVoulez-vous rejouer ?", "Bravo ! ", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
            {
                nbParties++;
                LSTBhistorique.Items.Add("Partie " + nbParties + " - " + mot + " - Gagnée - " + essais + " essais");
                nouvellePartie();
            }
            else Application.Current.Shutdown();
        }


        private void motIncorrect()
        {
            if (essais== NB_MAX_ESSAIS)
            {
                if (MessageBox.Show("Le mot à trouver était : " + mot + "\nVoulez-vous rejouer ?", "Perdu ! ", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
                {
                    nbParties++;
                    LSTBhistorique.Items.Add("Partie " + nbParties + " - " + mot + " - Perdue - " + essais + " essais");
                    nouvellePartie();
                }
                else Application.Current.Shutdown();
            }

            else {LSTBessais.Items.Add(TXTBproposition.Text);}
        }


        private void BTNtester_Click(object sender, RoutedEventArgs e)
        {
            TXTBproposition.Text = TXTBproposition.Text.ToUpper();
            if (TXTBproposition.Text == mot) motCorrect();
            else motIncorrect();
            essais++;
        }

        private void BTNrejouer_Click(object sender, RoutedEventArgs e)
        {
            if (MessageBox.Show("Voules-vous vraiment rejouer ?", "Rejouer ? ", MessageBoxButton.YesNo) == MessageBoxResult.Yes)
            {
                nbParties++;
                LSTBhistorique.Items.Add("Partie " + nbParties + " - " + mot + " - Abandonnée - " + essais + " essais");
                nouvellePartie();
            }
        }

        private void BTNquitter_Click(object sender, RoutedEventArgs e)
        {
            if (MessageBox.Show("Voules-vous vraiment quitter le jeu ?", "Quitter ? ", MessageBoxButton.YesNo) == MessageBoxResult.Yes) Application.Current.Shutdown();
        }

        private void TXTBproposition_TextChanged(object sender, TextChangedEventArgs e)
        {
            
        }
    }
}
