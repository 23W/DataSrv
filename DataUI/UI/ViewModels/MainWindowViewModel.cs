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
    public class MainWindowViewModel : ObservableModel
    {
        #region Properties

        public PlotModel PlotModel { get; init; } = new PlotModel();

        public IEnumerable<SourceViewModel> Sources => GetSourceViewModels();

        public SourceType Source
        {
            get => CPUProvider?.Source ?? SourceType.PDH;
            set
            {
                if (CPUProvider == default)
                {
                    return;
                }

                if (CPUProvider.Source != value)
                {
                    CPUProvider.Source = value;
                    NotifyPropertyChanged();
                }
            }
        }

        IWindowViewModelHost? Host { get; set; } = default;

        CPUTempData? CPUProvider { get; set; } = default;

        #endregion

        #region Construction

        public void Initialize(IWindowViewModelHost host)
        {
            Debug.Assert(host != default);

            Host = host;

            if (Host != default)
            {
                Host.Loaded += OnLoadedAsync;
                Host.ThemeChanged += OnThemeChanged;
            }

            BuildPlotModel();

            NotifyPropertyChanged(nameof(Sources),
                                  nameof(Source));
        }

        public void Dispose()
        {
            if (CPUProvider != default)
            {
                CPUProvider.OnNextSample -= OnNextSample;
                CPUProvider = default;
            }

            if (Host != default)
            {
                Host.Loaded -= OnLoadedAsync;
                Host.ThemeChanged -= OnThemeChanged;
                Host = default;
            }
        }

        #endregion

        #region Event Handlers

        async void OnLoadedAsync(object sender, System.Windows.RoutedEventArgs e)
        {
            await BuildDataProviderAsync();
        }

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

        IEnumerable<SourceViewModel> GetSourceViewModels()
        {
            var res = new[] { SourceType.PDH, SourceType.WMI }
                      .Select(s => new SourceViewModel() { Source = s, Host = Host })
                      .ToList();
            return res;
        }

        async Task BuildDataProviderAsync()
        {
            try
            {
                var dataProvider = new DataProvider();

                CPUProvider = dataProvider.CpuTemp;
                CPUProvider.Source = SourceType.PDH;
                CPUProvider.OnNextSample += OnNextSample;

                NotifyPropertyChanged(nameof(Sources),
                                      nameof(Source));
            }
            catch
            {
                if (Host != default)
                {
                    await Host.ShowMessageBoxAsync((string)Host.ApplicationResources["Error"],
                                                   (string)Host.ApplicationResources["ProviderFailedLabel"]);
                }
            }
        }

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

            PlotModel.IsLegendVisible = false;
            PlotModel.Axes.Add(axisTemp);
            PlotModel.Axes.Add(axisSample);
            PlotModel.Series.Add(series);

            BindPlotColors();
            BindTextTitels();

            PlotModel.InvalidatePlot(true);
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
            var seriesStroke = converter.Convert((Color)Host.ApplicationResources[ThemeResource.SystemAccentColorPrimary.ToString()]);
            var seriesFill = OxyColor.FromAColor(0x30, seriesStroke);

            PlotModel.Background = background;
            PlotModel.PlotAreaBackground = background;
            PlotModel.PlotAreaBorderColor = OxyColors.Undefined;
            PlotModel.TextColor = text;
            PlotModel.TitleColor = title;
            PlotModel.SubtitleColor = subTitle;

            var axisTemp = PlotModel.Axes.Cast<LinearAxis>()
                                         .FirstOrDefault(a => a.Position == AxisPosition.Left);
            if (axisTemp != default)
            {
                axisTemp.TitleColor = title;
                axisTemp.MajorGridlineColor = majorGrid;
                axisTemp.MinorGridlineColor = minorGrid;
            }

            var series = PlotModel.Series.ElementAtOrDefault(0) as AreaSeries;
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

            var axisTemp = PlotModel.Axes.Cast<LinearAxis>()
                                         .FirstOrDefault(a => a.Position == AxisPosition.Left);
            if (axisTemp != default)
            {
                axisTemp.Title = (string)Host.ApplicationResources["TemperatureLabel"];
                axisTemp.Unit = (string)Host.ApplicationResources["CelsiusUnitLabel"];
            }
        }

        void AddSample(float value)
        {
            var series = PlotModel.Series.FirstOrDefault() as AreaSeries;
            if (series != default)
            {
                var axisTemp = (LinearAxis)PlotModel.Axes.ElementAt(0);
                var axisSample = (LinearAxis)PlotModel.Axes.ElementAt(1);
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

            PlotModel.InvalidatePlot(true);
        }

        #endregion

        #region Constants

        const int c_maxCount = 120;
        const double c_maxTemp = 100;

        #endregion
    }
}
