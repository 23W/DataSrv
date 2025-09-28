using DataSrvLib;
using OxyPlot;
using System.Diagnostics;

namespace DataUI.UI.ViewModels
{
    public class MainWindowViewModel : ObservableModel
    {
        #region Properties

        public PlotModel CPUPlotModel { get; init; } = new PlotModel();

        public CPUProviderViewModel? CPU { get; private set; } = default;

        public IEnumerable<GPUProviderViewModel> GPUs { get; private set; } = Enumerable.Empty<GPUProviderViewModel>();

        IMainWindowViewModelHost? Host { get; set; } = default;

        #endregion

        #region Construction

        public void Initialize(IMainWindowViewModelHost host)
        {
            Debug.Assert(host != default);

            Host = host;

            if (Host != default)
            {
                Host.Loaded += OnLoadedAsync;
            }
        }

        public void Dispose()
        {
            CPU?.Clean();
            CPU = default;

            if (GPUs.Any())
            {
                foreach(var gpu in GPUs)
                {
                    gpu.Clean();
                }

                GPUs = Enumerable.Empty<GPUProviderViewModel>();
            }


            if (Host != default)
            {
                Host.Loaded -= OnLoadedAsync;
                Host = default;
            }
        }

        #endregion

        #region Event Handlers

        async void OnLoadedAsync(object sender, System.Windows.RoutedEventArgs e)
        {
            await BuildDataProviderAsync();
        }

        #endregion

        #region Helper Methods

        async Task BuildDataProviderAsync()
        {
            try
            {
                var dataProvider = new DataProvider();

                if (CPU == default)
                {
                    CPU = CPUProviderViewModel.Create(dataProvider.CpuTemp, Host);
                    NotifyPropertyChanged(nameof(CPU));
                }

                if (!GPUs.Any())
                {
                    GPUs = dataProvider.GpuTemp.Cast<GPUTempData>()
                                               .Select(gpu => GPUProviderViewModel.Create(gpu, Host))
                                               .ToList();
                    NotifyPropertyChanged(nameof(GPUs));
                }

                Host?.BuildGridLayout();
            }
            catch(Exception ex)
            {
                if (Host != default)
                {
                    await Host.ShowMessageBoxAsync((string)Host.ApplicationResources["ErrorTitle"],
                                                   $"{(string)Host.ApplicationResources["ProviderFailedLabel"]}\n{ex.Message}");
                }
            }
        }

        #endregion

        #region Constants

        const int c_maxCount = 120;
        const double c_maxTemp = 100;

        #endregion
    }
}
