using DataUI.UI.ViewModels;
using System.Windows;
using Wpf.Ui.Controls;

namespace DataUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : FluentWindow
    {
        #region Construction

        public MainWindow()
        {
            InitializeComponent();
            InitializeViewModel();
        }

        #endregion

        #region Properties

        public MainWindowViewModel ViewModel => (MainWindowViewModel)Resources["ViewModel"];

        #endregion

        #region Event Handlers

        void OnLoaded(object sender, RoutedEventArgs e)
        {
            Wpf.Ui.Appearance.SystemThemeWatcher.Watch(
                this,                                    // Window class
                Wpf.Ui.Controls.WindowBackdropType.Mica, // Background type
                true                                     // Whether to change accents automatically
            );
        }

        void OnClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            ViewModel.Dispose();
        }

        void OnClose(object sender, RoutedEventArgs e)
        {
            Close();
        }

        #endregion

        #region Helper Methods

        void InitializeViewModel()
        {
            ViewModel.Initialize();
        }

        #endregion

    }
}