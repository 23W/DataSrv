using System.Globalization;
using System.Windows.Data;
using System.Windows.Markup;

namespace DataUI.UI.Converters
{
    [ValueConversion(typeof(System.Windows.Media.Color), typeof(OxyPlot.OxyColor))]
    public class ColorToOxyPlotColorConverter : MarkupExtension, IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var res = default(OxyPlot.OxyColor);

            if (value is System.Windows.Media.Color color)
            {
                res = OxyPlot.OxyColor.FromArgb(color.A, color.R, color.G, color.B);
            }

            return res;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var res = default(System.Windows.Media.Color);

            if (value is OxyPlot.OxyColor color)
            {
                res = System.Windows.Media.Color.FromArgb(color.A, color.R, color.G, color.B);
            }

            return res;
        }

        public OxyPlot.OxyColor Convert(System.Windows.Media.Color color) => (OxyPlot.OxyColor)Convert(color, typeof(OxyPlot.OxyColor),
                                                                                                       default!, CultureInfo.CurrentCulture);

        public System.Windows.Media.Color ConvertBack(OxyPlot.OxyColor color) => (System.Windows.Media.Color)ConvertBack(color, typeof(System.Windows.Media.Color),
                                                                                                                         default!, CultureInfo.CurrentCulture);

        public override object ProvideValue(IServiceProvider serviceProvider) => this;
    }
}
