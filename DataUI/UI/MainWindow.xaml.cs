using DataUI.UI.ViewModels;
using System.Windows;
using System.Windows.Controls;
using Wpf.Ui.Appearance;
using Wpf.Ui.Controls;

namespace DataUI
{
    public interface IMainWindowViewModelHost : IWindowViewModelHost
    {
        void BuildGridLayout();
    }

    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : FluentWindow, IMainWindowViewModelHost
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
                Title = title ?? string.Empty,
                Content = content ?? string.Empty,
            };

            return msgBox.ShowDialogAsync();
        }

        public void BuildGridLayout()
        {
            var gpuCount = ViewModel.GPUs.Count();
            var hasCpu = ViewModel.CPU != default;
            var hasGpu = gpuCount > 0;
            var rows = hasGpu ? gpuCount : 1;

            GraphGrid.Children.Clear();
            GraphGrid.RowDefinitions.Clear();
            GraphGrid.ColumnDefinitions.Clear();

            if (hasGpu)
            {
                for (var row = 0; row < rows; row++)
                {
                    GraphGrid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });
                }

                GraphGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(3, GridUnitType.Star) });
                GraphGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(2, GridUnitType.Star) });
            }
            else
            {
                GraphGrid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });
                GraphGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            }

            if (hasCpu)
            {
                var cpuPlotView = new OxyPlot.Wpf.PlotView()
                {
                    Margin = new Thickness(3),
                    Model = ViewModel.CPU!.Model,
                    DefaultTrackerTemplate = default
                };

                Grid.SetColumn(cpuPlotView, 0);
                Grid.SetRow(cpuPlotView, 0);
                Grid.SetRowSpan(cpuPlotView, rows);
                GraphGrid.Children.Add(cpuPlotView);
            }

            if (hasGpu)
            {
                foreach (var (gpu, row) in ViewModel.GPUs.Select((gpu, index) => (gpu, index)))
                {
                    var gpuPlotView = new OxyPlot.Wpf.PlotView()
                    {
                        Margin = new Thickness(3),
                        Model = gpu.Model,
                        DefaultTrackerTemplate = default
                    };

                    Grid.SetColumn(gpuPlotView, 1);
                    Grid.SetRow(gpuPlotView, row);
                    GraphGrid.Children.Add(gpuPlotView);
                }
            }
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