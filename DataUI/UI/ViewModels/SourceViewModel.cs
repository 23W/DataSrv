using DataSrvLib;
using System.Diagnostics;

namespace DataUI.UI.ViewModels
{
    public class SourceViewModel : ObservableModel
    {
        public IWindowViewModelHost? Host { get; init; }

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

        string GetSourceName(SourceType source)
        {
            var res = string.Empty;

            if (Host != default)
            {
                switch (source)
                {
                    case SourceType.PDH:
                        res = (string)Host.ApplicationResources["SourcePDHLabel"];
                        break;
                    case SourceType.WMI:
                        res = (string)Host.ApplicationResources["SourceWMILabel"];
                        break;
                    default:
                        Debug.Assert(false, "Unknow SourceType");
                        break;
                }
            }

            return res;
        }

        SourceType m_sourceType = SourceType.PDH;
    }
}
