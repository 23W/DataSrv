using DataSrvLib;
using System.Diagnostics;
using System.Windows;

namespace DataUI.UI.ViewModels
{
    public class SourceViewModel : ObservableModel
    {
        public SourceType Source
        {
            get => m_sourceType;
            set
            {
                if (value != m_sourceType)
                {
                    m_sourceType = value;
                    NotifyPropertyChanged();
                }
            }
        }

        public string Name => GetSourceName(Source);

        static string GetSourceName(SourceType source)
        {
            var res = string.Empty;

            switch (source)
            {
                case SourceType.PDH:
                    res = (string)Application.Current.Resources["SourcePDHLabel"];
                    break;
                case SourceType.WMI:
                    res = (string)Application.Current.Resources["SourceWMILabel"];
                    break;
                default:
                    Debug.Assert(false, "Unknow SourceType");
                    break;
            }

            return res;
        }

        SourceType m_sourceType = SourceType.PDH;
    }
}
