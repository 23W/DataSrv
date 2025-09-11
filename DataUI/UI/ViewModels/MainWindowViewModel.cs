using DataSrvLib;
using System.Diagnostics;

namespace DataUI.UI.ViewModels
{
    public class MainWindowViewModel : ObservableModel
    {
        #region Properties

        CPUTempData? CPUProvider { get; set; } = default;

        #endregion

        #region Construction

        public void Initialize()
        {
            var obj = new DataProvider();

            CPUProvider = obj.CpuTemp;
            CPUProvider.OnNextSample += OnNextSample;
        }

        #endregion

        #region Event Handlers

        void OnNextSample(float value)
        {
            Debug.WriteLine(value);
        }

        #endregion
    }
}
