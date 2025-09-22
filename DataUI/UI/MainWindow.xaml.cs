using DataUI.UI.ViewModels;
using System.Windows;
using Wpf.Ui.Appearance;
using Wpf.Ui.Controls;

namespace DataUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : FluentWindow, IWindowViewModelHost
    {
        #region Construction

        public MainWindow()
        {
            if (!ApplicationThemeManager.IsAppMatchesSystem())
            {
                ApplicationThemeManager.ApplySystemTheme();
            }

            SystemThemeWatcher.Watch(this);

            InitializeComponent();
            InitializeViewModel();
        }

        #endregion

        #region Properties

        public MainWindowViewModel ViewModel => (MainWindowViewModel)Resources["ViewModel"];

        public ResourceDictionary ApplicationResources => Application.Current.Resources;

        public ResourceDictionary WindowResources => Resources;

        #endregion

        #region Events

        public event ThemeChangedEvent? ThemeChanged;

        #endregion

        #region Methods

        public Task ShowMessageBoxAsync(string title, string content)
        {
            var msgBox = new Wpf.Ui.Controls.MessageBox()
            {
                Title = (string)ApplicationResources["Error"],
                Content = (string)ApplicationResources["ProviderFailedLabel"],
            };

            return msgBox.ShowDialogAsync();
        }

        #endregion

        #region Event Handlers

        void OnThemeManagerChanged(ApplicationTheme currentApplicationTheme, System.Windows.Media.Color systemAccent)
        {
            ThemeChanged?.Invoke(currentApplicationTheme, systemAccent);
        }

        void OnClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            UninitializeViewModel();
        }

        void OnCloseBtn(object sender, RoutedEventArgs e)
        {
            Close();
        }

        #endregion

        #region Helper Methods

        void InitializeViewModel()
        {
            ApplicationThemeManager.Changed += OnThemeManagerChanged;

            ViewModel.Initialize(this);
        }

        void UninitializeViewModel()
        {
            ViewModel.Dispose();

            ApplicationThemeManager.Changed -= OnThemeManagerChanged;
        }

        #endregion

    }
}