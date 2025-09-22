using System.Globalization;
using System.Windows;
using System.Windows.Data;
using System.Windows.Markup;

namespace DataUI.UI.Converters
{
    [ValueConversion(typeof(CornerRadius), typeof(Thickness))]
    internal class CornerRadiusToThicknessConverter : MarkupExtension, IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            var res = default(Thickness);

            if (value is CornerRadius radius)
            {
                res = new Thickness(Math.Max(radius.TopLeft, radius.BottomLeft),
                                    Math.Max(radius.TopLeft, radius.TopRight),
                                    Math.Max(radius.TopRight, radius.BottomRight),
                                    Math.Max(radius.BottomLeft, radius.BottomRight));
            }

            return res;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return Binding.DoNothing;
        }

        public override object ProvideValue(IServiceProvider serviceProvider) => this;

    }
}
