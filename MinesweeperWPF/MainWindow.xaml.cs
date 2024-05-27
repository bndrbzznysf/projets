using System;
using System.Data.Common;
using System.Linq;
using System.Media;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Media;
using static System.Reflection.Metadata.BlobBuilder;

namespace MinesweeperWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        private int gridSize;
        private int nbMines;
        private int nbCellOpen = 0;
        private int[,] matrix;


        public MainWindow()
        {
            InitializeComponent();
        }


        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            initialisation();
        }


        public void initialisation()
        {
            matrix = new int[gridSize, gridSize];
            poseMine();
            nbCellOpen = 0;
            GRDGame.Children.Clear();
            GRDGame.ColumnDefinitions.Clear();
            GRDGame.RowDefinitions.Clear();
            for (int i = 0; i < gridSize; i++)
            {
                GRDGame.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
                GRDGame.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });

                for (int j = 0; j < gridSize; j++)
                {
                    Border b = new Border();
                    b.BorderThickness = new Thickness(1);
                    b.BorderBrush = new SolidColorBrush(Colors.DarkGray);
                    b.SetValue(Grid.RowProperty, j);
                    b.SetValue(Grid.ColumnProperty, i);
                    GRDGame.Children.Add(b);

                    Grid gridButton = new Grid();
                    gridButton.Background = Brushes.LightGray;
                    Label label = new Label();
                    Button btn = new Button();
                    btn.Style = (Style)FindResource("NoHoverButtonStyle");
                    btn.Click += BTN_Click;

                    label.Content = matrix[i, j];
                    label.HorizontalAlignment = HorizontalAlignment.Center;
                    label.VerticalAlignment = VerticalAlignment.Center;
                    label.FontWeight = FontWeights.Bold;

                    if (matrix[i, j] == 0) label.Content = null;
                    else if (matrix[i, j] != -1) 
                    {
                        switch(matrix[i, j])
                        {
                            case 1: label.Foreground = Brushes.Blue; break;
                            case 2: label.Foreground = Brushes.Green; break;
                            case 3: label.Foreground = Brushes.Red; break;
                            case 4: label.Foreground = Brushes.Navy; break;
                            case 5: label.Foreground = Brushes.Maroon; break;
                            case 6: label.Foreground = Brushes.Teal; break;
                            case 8: label.Foreground = Brushes.Gray; break;
                            default: label.Foreground = Brushes.Black; break;
                        }
                    }
                    else label.Content = "💣"; 

                    gridButton.Children.Add(label);
                    gridButton.Children.Add(btn);
                    b.Child = gridButton;

                }

            }

        }


        private void Menu()
        {

        }


        private void poseMine()
        {
            Random random = new Random();
            int randRow;
            int randCol;
            int minesPlacees = 0;
            while (minesPlacees < nbMines)
            {
                randRow = random.Next(gridSize);
                randCol = random.Next(gridSize);

                if (matrix[randRow, randCol] != -1)
                {
                    matrix[randRow, randCol] = -1;
                    minesPlacees++;
                }
            }

            for (int i = 0; i < gridSize; i++)
            {
                for (int j = 0; j < gridSize; j++)
                {
                    if (matrix[i, j] == 0)
                    {
                        matrix[i, j] = nbBombesVoisines(i, j);
                    }
                }
            }

        }

        private int nbBombesVoisines(int col, int row)
        {
            int count = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int newRow = row + i;
                    int newCol = col + j;

                    if (newRow >= 0 && newRow < gridSize && newCol >= 0 && newCol < gridSize && matrix[newCol, newRow] == -1)
                    {
                        count++;
                    }
                }
            }

            return count;
        }


        private bool verifieCellule(int column, int row)
        {
            Border caseAverfier = (Border)GetUIElementFromPosition(GRDGame, column, row);
            Grid gridCase = (Grid)caseAverfier.Child;
            Button bouton = gridCase.Children.OfType<Button>().First();
            Label label = gridCase.Children.OfType<Label>().First();
            if (bouton.Visibility == Visibility.Visible) 
            {
                bouton.Visibility = Visibility.Collapsed;
                nbCellOpen++;
                if (matrix[column, row] == -1)
                {
                    for(int i = 0; i<gridSize; i++)
                    {
                        for(int j = 0; j < gridSize; j++)
                        {
                            if (matrix[i, j] == -1)
                            {
                                Border caseBombe = (Border)GetUIElementFromPosition(GRDGame, i, j);
                                Grid bombe = (Grid)caseBombe.Child;
                                Button boutonBombe = bombe.Children.OfType<Button>().First();
                                boutonBombe.Visibility = Visibility.Collapsed;
                                bombe.Background = Brushes.Tomato;
                            }
                        }
                    }
                    gridCase.Background = Brushes.Red; 
                    SystemSounds.Beep.Play();
                    MessageBox.Show("Vous avez perdu !!", "Perdu");
                    initialisation();
                    return true;
                }
                else {
                    if (nbCellOpen == (gridSize*gridSize - nbMines))
                    {
                        MessageBox.Show("Vous avez gagné !!", "Gagné");
                        initialisation();
                        return true;
                    }
                    else {
                        if (matrix[column, row] == 0) 
                        {
                            for(int i=Math.Max(0, column-1); i <= Math.Min(gridSize-1, column + 1); i++)
                            {
                                for(int j = Math.Max(0, row-1); j <= Math.Min(gridSize-1, row + 1); j++)
                                {
                                    bool res = verifieCellule(i, j);
                                    if(res) return true;
                                }
                            }
                        }
                    }
                }
            }
            return false;
        }



        private void BTN_Click(object sender, RoutedEventArgs e)
        {
            Button btn = (Button)sender;
            Border b = (Border)VisualTreeHelper.GetParent(VisualTreeHelper.GetParent(btn));
            int col = Grid.GetColumn(b);
            int row = Grid.GetRow(b);
            verifieCellule(col, row);
        }


        private UIElement GetUIElementFromPosition(Grid g, int col, int row)
        {
            return g.Children.Cast<UIElement>().First(e => Grid.GetRow(e) == row && Grid.GetColumn(e) == col);
        }


        private void BTN_reset(object sender, RoutedEventArgs e)
        {
            initialisation();
        }


        private void taille8_checked(object sender, RoutedEventArgs e)
        {
            if (ITEM_8!=null) ITEM_8.IsChecked = true;
            if (ITEM_9 != null) ITEM_9.IsChecked = false;
            if (ITEM_16 != null) ITEM_16.IsChecked = false;
            gridSize = 8;
            nbMines=10;
            initialisation();
        }

        private void taille9_checked(object sender, RoutedEventArgs e)
        {
            if (ITEM_8 != null) ITEM_8.IsChecked = false;
            if (ITEM_9 != null) ITEM_9.IsChecked = true;
            if (ITEM_16 != null) ITEM_16.IsChecked = false;
            gridSize = 9;
            nbMines=12;
            initialisation();
        }

        private void taille16_checked(object sender, RoutedEventArgs e)
        {
            if (ITEM_8 != null) ITEM_8.IsChecked = false;
            if (ITEM_9 != null) ITEM_9.IsChecked = false;
            if (ITEM_16 != null) ITEM_16.IsChecked = true;
            gridSize = 16;
            nbMines=40;
            initialisation();
        }


        private void nouvellePartie(object sender, RoutedEventArgs e)
        {
            initialisation();
        }

    }
}
