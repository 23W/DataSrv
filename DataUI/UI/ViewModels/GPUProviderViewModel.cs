using DataSrvLib;
using DataUI.UI.Converters;
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;
using System.Diagnostics;
using System.Windows.Media;
using Wpf.Ui.Markup;

namespace DataUI.UI.ViewModels
{
    public class GPUProviderViewModel
    {
        #region Properties

        public IWindowViewModelHost? Host { get; private set; }

        public GPUTempData? Provider { get; private set; } = default;

        public PlotModel Model { get; init; } = new PlotModel();

        #endregion

        #region Construction

        internal static GPUProviderViewModel Create(GPUTempData provider, IWindowViewModelHost? host)
        {
            var res = new GPUProviderViewModel()
            {
                Provider = provider,
                Host = host
            };

            res.Init();

            return res;
        }

        internal void Init()
        {
            if (Host != default)
            {
                Host.ThemeChanged += OnThemeChanged;
            }

            if (Provider != default)
            {
                Provider.OnNextSample += OnNextSample;
            }

            BuildPlotModel();
            BindPlotColors();
        }

        internal void Clean()
        {
            if (Provider != default)
            {
                Provider.OnNextSample -= OnNextSample;
            }

            if (Host != default)
            {
                Host.ThemeChanged -= OnThemeChanged;
            }

            Provider = default;
        }

        #endregion

        #region Event Handlers

        void OnThemeChanged(Wpf.Ui.Appearance.ApplicationTheme currentApplicationTheme, Color systemAccent)
        {
            BindPlotColors();
        }

        void OnNextSample(float value)
        {
            Host?.Dispatcher.Invoke(() => AddSample(value));
        }

        #endregion

        #region Helper Methods

        void BuildPlotModel()
        {
            var series = new AreaSeries();
            series.StrokeThickness = 1;

            var axisTemp = new LinearAxis();
            axisTemp.Position = AxisPosition.Left;
            axisTemp.Minimum = 0;
            axisTemp.Maximum = c_maxTemp;
            axisTemp.MajorGridlineStyle = LineStyle.Solid;
            axisTemp.MinorGridlineStyle = LineStyle.Solid;
            axisTemp.IsPanEnabled = false;
            axisTemp.IsZoomEnabled = false;

            var axisSample = new LinearAxis();
            axisSample.Position = AxisPosition.Bottom;
            axisSample.Minimum = 0;
            axisSample.Maximum = c_maxCount - 1;
            axisSample.TickStyle = TickStyle.None;
            axisSample.IsPanEnabled = false;
            axisSample.IsZoomEnabled = false;
            axisSample.IsAxisVisible = false;

            Model.IsLegendVisible = false;
            Model.Axes.Add(axisTemp);
            Model.Axes.Add(axisSample);
            Model.Series.Add(series);

            BindPlotColors();
            BindTextTitels();

            Model.InvalidatePlot(true);
        }

        void BindPlotColors()
        {
            if (Host == default)
            {
                return;
            }

            var converter = new ColorToOxyPlotColorConverter();
            var background = converter.Convert((Color)Host.ApplicationResources[ThemeResource.ApplicationBackgroundColor.ToString()]);
            var text = converter.Convert((Color)Host.ApplicationResources[ThemeResource.TextFillColorPrimary.ToString()]);
            var title = converter.Convert((Color)Host.ApplicationResources[ThemeResource.TextFillColorSecondary.ToString()]);
            var subTitle = converter.Convert((Color)Host.ApplicationResources[ThemeResource.TextFillColorTertiary.ToString()]);
            var majorGrid = converter.Convert((Color)Host.ApplicationResources[ThemeResource.TextFillColorTertiary.ToString()]);
            var minorGrid = OxyColor.FromAColor(0x30, majorGrid);
            var seriesStroke = converter.Convert((Color)Host.ApplicationResources[ThemeResource.SystemAccentColorTertiary.ToString()]);
            var seriesFill = OxyColor.FromAColor(0x30, seriesStroke);

            Model.Background = background;
            Model.PlotAreaBackground = background;
            Model.PlotAreaBorderColor = OxyColors.Undefined;
            Model.TextColor = text;
            Model.TitleColor = title;
            Model.SubtitleColor = subTitle;

            var axisTemp = Model.Axes.Cast<LinearAxis>()
                                         .FirstOrDefault(a => a.Position == AxisPosition.Left);
            if (axisTemp != default)
            {
                axisTemp.TitleColor = title;
                axisTemp.MajorGridlineColor = majorGrid;
                axisTemp.MinorGridlineColor = minorGrid;
            }

            var series = Model.Series.ElementAtOrDefault(0) as AreaSeries;
            if (series != default)
            {
                series.Color = seriesStroke;
                series.Fill = seriesFill;
            }
        }

        void BindTextTitels()
        {
            if (Host == default)
            {
                return;
            }

            var axisTemp = Model.Axes.Cast<LinearAxis>()
                                         .FirstOrDefault(a => a.Position == AxisPosition.Left);
            if (axisTemp != default)
            {
                var providerName = Provider?.Name ?? string.Empty;

                axisTemp.Title = providerName;
                axisTemp.Unit = (string)Host.ApplicationResources["CelsiusUnitLabel"];
            }
        }

        void AddSample(float value)
        {
            var series = Model.Series.FirstOrDefault() as AreaSeries;
            if (series != default)
            {
                var axisTemp = (LinearAxis)Model.Axes.ElementAt(0);
                var axisSample = (LinearAxis)Model.Axes.ElementAt(1);
                Debug.Assert(axisTemp.Position == AxisPosition.Left);
                Debug.Assert(axisSample.Position == AxisPosition.Bottom);

                var shiftData = series.Points.Count >= c_maxCount;

                // new sample
                var sample = new DataPoint(shiftData ? axisSample.Maximum + 1 : series.Points.Count, value);
                series.Points.Add(sample);

                // scroll graph and remove oldest sample
                if (shiftData)
                {
                    axisSample.Minimum += 1;
                    axisSample.Maximum += 1;

                    series.Points.RemoveRange(0, series.Points.Count - c_maxCount);
                }

                // tune low temp scale
                var minValue = series.Points.Select(dp => dp.Y).Min();
                axisTemp.Minimum = Math.Floor(Math.Max(minValue - 30, 0) / 10) * 10;
            }

            Model.InvalidatePlot(true);
        }

        #endregion

        #region Constants

        const int c_maxCount = 120;
        const double c_maxTemp = 100;

        #endregion
    }
}
