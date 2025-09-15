using DataSrvLib;
using System.Collections.ObjectModel;
using System.Windows;

namespace DataUI.UI.ViewModels
{
    public class MainWindowViewModel : ObservableModel
    {
        #region Properties

        public ObservableCollection<string> Samples { get; set; } = new ObservableCollection<string>();

        CPUTempData? CPUProvider { get; set; } = default;

        #endregion

        #region Construction

        public void Initialize()
        {
            var obj = new DataProvider();

            CPUProvider = obj.CpuTemp;
            CPUProvider.OnNextSample += OnNextSample;
        }

        public void Dispose()
        {
            if (CPUProvider != null)
            {
                CPUProvider.OnNextSample -= OnNextSample;
                CPUProvider = null;
            }
        }

        #endregion

        #region Event Handlers

        void OnNextSample(float value)
        {
            Application.Current.Dispatcher.Invoke(() =>
            {
                Samples.Add($"{value:F2}");

                if (Samples.Count > 7)
                {
                    Samples.RemoveAt(0);
                }
            });
        }

        #endregion
    }
}
